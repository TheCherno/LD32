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
	m_BackgroundLayer = new LevelLayer();
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
	m_BackgroundLayer->add(bg);

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

	m_Red = rand() % 1000 / 1000.0f;
	m_Green = rand() % 1000 / 1000.0f;
	m_Blue = rand() % 1000 / 1000.0f;
	m_ColorChannel = rand() % 3;

	m_Portal = new Portal(vec2(4500 + m_Difficulty * 5000, 250));
	m_LevelLayer->add(m_Portal->getSprite());

	m_LevelLayer->getShader()->enable();
	m_LevelLayer->getShader()->setUniform1f("fade_out", 1.0f);

	m_BackgroundLayer->getShader()->enable();
	m_BackgroundLayer->getShader()->setUniform1f("fade_out", 1.0f);

	m_Progress = 0;
	m_LevelEnd = 4500 + m_Difficulty * 5000;

	m_ProgressBarBackground = new Sprite(300, 25, 680, 40, 0x2faaaaaa);
	m_ProgressBar = new Sprite(305, 30, 0, 30, 0x2fffffff);
}

Level::~Level()
{
	for (int i = 0; i < m_Entities.size(); i++)
		delete m_Entities[i];

	delete m_LevelLayer;
	delete m_BackgroundLayer;
	delete m_Portal;
	delete m_ProgressBar;
	delete m_ProgressBarBackground;
}


void Level::generatePlatforms(int count)
{
	float wm = m_Difficulty * 10;
	if (wm > 80)
		wm = 80;

	float gm = m_Difficulty * 20;
	if (gm > 250)
		gm = 250;

	unsigned int ym = 300 + m_Difficulty * 50;
	if (ym > 800)
		ym = 800;

	float sx = m_Player->getPosition().x + 100;
	for (int i = 0; i < count; i++)
	{
		float w = (float)(rand() % 1000) / 2.0f + 100.0f - wm;
		float h = (float)(rand() % 500) / 2.0f + 100;
		float y = (float)(rand() % ym) / 2.0f - h / 2;

		vec4 col = vec4(1, 1, 1, 1);
		if (m_ColorChannel == 0)
			col = vec4(rand() % 1000 / 1000.0f, m_Green, m_Blue, 1.0f);
		else if (m_ColorChannel == 1)
			col = vec4(m_Red, rand() % 1000 / 1000.0f, m_Blue, 1.0f);
		else if (m_ColorChannel == 2)
			col = vec4(m_Red, m_Green, rand() % 1000 / 1000.0f, 1.0f);

		addObject(new LevelObject(sx, y, new Sprite(0, 0, w, h, col)));
		sx += w + 50 + gm;
	}
	float sx2 = m_Player->getPosition().x + 100;
	for (int i = 0; i < count; i++)
	{
		float w = (float)(rand() % 300 + 100);
		float h = (float)(rand() % 500 + 200);
		addBackgroundObject(new LevelObject(sx2 + 20, 0, new Sprite(0, 0, w, h, 0x77777777), false));
		sx2 += 100 + rand() % 100 + w;
	}
	m_PlatformOffsetX = sx + 100;

	for (int i = 0; i < 1 + rand() % 8 + (m_Difficulty < 20 ? m_Difficulty : 20) * 4; i++)
	{
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

void Level::addBackgroundObject(LevelObject* object)
{
	m_Objects.push_back(object);
	m_BackgroundLayer->add(object->getSprite());
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
	m_Progress = (int) m_Player->getPosition().x;
	if (m_Progress < 0)
		m_Progress = 0;
	m_ProgressBar->size.x = (int)(((float)m_Progress / (float)m_LevelEnd) * 680.0f);
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
		if (object->isCollidable())
			object->getSprite()->position = vec3(pos.x - m_Offset.x, pos.y - m_Offset.y, 0);
		else
			object->getSprite()->position = vec3(pos.x - m_Offset.x * 0.3f, pos.y - m_Offset.y * 0.3f, 0);
	}

	for (int i = 0; i < m_Entities.size(); i++)
	{
		const vec2& pos = m_Entities[i]->getPosition();
		m_Entities[i]->getSprite()->position = vec3(pos.x - m_Offset.x, pos.y - m_Offset.y, 0);
		m_Entities[i]->render();
	}

	for (int i = 0; i < m_Projectiles.size(); i++)
		m_Projectiles[i]->render();

	LD32Application::debugLayer->addTemp(m_ProgressBarBackground);
	LD32Application::debugLayer->addTemp(m_ProgressBar);

	m_BackgroundLayer->render();
	m_LevelLayer->render();
	m_Player->render();
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
