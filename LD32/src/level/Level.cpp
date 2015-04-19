#include "Level.h"
#include "entity/Entity.h"
#include "../LD32Application.h"

using namespace sparky;
using namespace graphics;
using namespace maths;

Level::Level(unsigned int difficulty)
	: m_Difficulty(difficulty)
{
	m_PlatformOffsetX = 500.0f;
	m_LevelLayer = new LevelLayer();
	m_Ships = 0;
	m_GameOver = false;
	srand(time(NULL));
	Sprite* bg = new Sprite(0, 0, 1280, 720, TextureManager::get("Level_Background"));
#ifdef SPARKY_EMSCRIPTEN
	std::vector<vec2> uv0(4);
	uv0[0] = vec2(0, 0);
	uv0[1] = vec2(0, 0.3515625f);
	uv0[2] = vec2(0.625f, 0.3515625f);
	uv0[3] = vec2(0.625f, 0);
	bg->setUV(uv0);
#endif
	m_LevelLayer->add(bg);

	LevelObject* platform = new LevelObject(0, 0, new Sprite(0, 0, 605, 442, TextureManager::get("Platform")));
#ifdef SPARKY_EMSCRIPTEN
	std::vector<vec2> uv1(4);
	uv1[0] = vec2(0, 0);
	uv1[1] = vec2(0, 0.431640625f);
	uv1[2] = vec2(0.5908203125f, 0.431640625f);
	uv1[3] = vec2(0.5908203125f, 0);
	platform->getSprite()->setUV(uv1);
#endif
	addObject(platform);

	m_Portal = new Portal(vec2(4500 + m_Difficulty * 5000, 250));
	m_LevelLayer->add(m_Portal->getSprite());

// 	addObject(new LevelObject(700, 550, new Sprite(0, 0, 400, 20, 0xffaa0000)));
// 	addObject(new LevelObject(900, 0, new Sprite(0, 0, 300, 200, 0xffaa0000)));


// 	for (int x = 0; x < 20; x++)
// 		addObject(new LevelObject(x * 256, -200, new Sprite(TextureManager::get("Ground"))));
	m_LevelLayer->getShader()->enable();
	m_LevelLayer->getShader()->setUniform1f("fade_out", 1.0f);
}

Level::~Level()
{
	for (int i = 0; i < m_Entities.size(); i++)
		delete m_Entities[i];

	delete m_LevelLayer;
	delete m_Portal;
}


void Level::generatePlatforms(int count)
{
	float wm = m_Difficulty * 10;
	if (wm > 50)
		wm = 50;

	float gm = m_Difficulty * 20;
	if (gm > 150)
		gm = 150;

	unsigned int ym = 300 + m_Difficulty * 50;
	if (ym > 800)
		ym = 800;

	float sx = m_Player->getPosition().x + 100;
	for (int i = 0; i < count; i++)
	{
		float w = (float)(rand() % 1000) / 2.0f + 100.0f - wm;
		float h = (float)(rand() % 500) / 2.0f + 100;
		float y = (float)(rand() % ym) / 2.0f - h / 2;
		vec4 col = vec4(rand() % 1000 / 1000.0f, 0.2f, 0.2f, 1.0f);
		addObject(new LevelObject(sx, y, new Sprite(0, 0, w, h, col)));
		sx += w + 50 + gm;
	}
	m_PlatformOffsetX = sx + 100;

	for (int i = 0; i < 1 + rand() % 8 + m_Difficulty * 4; i++)
	{
		m_Ships++;
		add(new Fighter(sx, 2550));
	}

}

void Level::add(Entity* entity)
{
	entity->init(this);
	m_Entities.push_back(entity);
	m_LevelLayer->add(entity->getSprite());
}

void Level::addObject(LevelObject* object)
{
	m_Objects.push_back(object);
	m_LevelLayer->add(object->getSprite());
}

void Level::addProjectile(Projectile* projectile)
{
	projectile->init(this);
	m_Projectiles.push_back(projectile);
	m_LevelLayer->add(projectile->getSprite());
}

void Level::addPlayer(Player* player)
{
	player->init(this);
	m_Player = player;
	m_LevelLayer->add(player->getRenderable());
}

void Level::update()
{
	if (m_GameOver)
	{
		m_Nuke->update();
		if (State::isMenu())
			return;
	}

	for (int i = 0; i < m_Entities.size(); i++)
	{
		if (m_GameOver)
			break;

		m_Entities[i]->update();
		if (m_Entities[i]->isRemoved())
		{
			m_LevelLayer->remove(m_Entities[i]->getSprite());
			delete m_Entities[i];
			m_Entities.erase(m_Entities.begin() + i--);
		}
	}

	for (int i = 0; i < m_Projectiles.size(); i++)
	{
		m_Projectiles[i]->update();
		if (m_Projectiles[i]->isRemoved())
		{
			m_LevelLayer->remove(m_Projectiles[i]->getSprite());
			delete m_Projectiles[i];
			m_Projectiles.erase(m_Projectiles.begin() + i--);
		}
	}

	m_Portal->getSprite()->position = vec3(m_Portal->getPosition().x - m_Offset.x, m_Portal->getPosition().y - m_Offset.y, 0.0f);

	m_Player->update();
	if (m_Player->getPosition().distance(m_Portal->getPosition() + 128) < 128)
	{
		LD32Application::INSTANCE->nextLevel();
		return;
	}

	
	if (m_Player->getPosition().x > m_PlatformOffsetX && m_PlatformOffsetX < 5000 + m_Difficulty * 5000)
	{
		generatePlatforms(10);
	}
}

void Level::render()
{
	LD32Application::debugLayer->text(19) = "Stage " + std::to_string(m_Difficulty + 1);
	if (m_GameOver)
		m_Nuke->render();

	for (int i = 0; i < m_Objects.size(); i++)
	{
		LevelObject* object = m_Objects[i];
		const vec2& pos = object->getPosition(); 
		object->getSprite()->position = vec3(pos.x - m_Offset.x, pos.y - m_Offset.y, 0);
	}

	for (int i = 0; i < m_Entities.size(); i++)
	{
		const vec2& pos = m_Entities[i]->getPosition();
		m_Entities[i]->getSprite()->position = vec3(pos.x - m_Offset.x, pos.y - m_Offset.y, 0);
		m_Entities[i]->render();
	}

	for (int i = 0; i < m_Projectiles.size(); i++)
		m_Projectiles[i]->render();

	m_Player->render();
	m_LevelLayer->render();
}

std::vector<LevelObject*> Level::getObjects(const Entity* entity, float radius)
{
	std::vector<LevelObject*> result;
	for (LevelObject* o : m_Objects)
	{
		if (entity->getCenter().distance(o->getCenter()) < radius)
			result.push_back(o);
	}
	return result;
}

std::vector<Projectile*> Level::getProjectiles(const Entity* entity, float radius)
{
	std::vector<Projectile*> result;
	for (Projectile* p : m_Projectiles)
	{
		if (entity->getCenter().distance(p->getCenter()) < radius)
			result.push_back(p);
	}
	return result;
}

void Level::start()
{
}

void Level::endGame()
{
	if (m_GameOver)
		return;

	m_GameOver = true;
	m_Nuke = new Nuke(640);
	m_Nuke->init(this);
}
