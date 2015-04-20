#include "Shield.h"
#include "../Level.h"
#include "../entity/Player.h"
#include "../../LD32Application.h"

using namespace sparky;
using namespace graphics;
using namespace maths;

Shield::Shield(Player* player)
	: Item(1, "Shield"), m_Player(player)
{
	m_Sprite = new Group(mat4::identity());
	m_Sprite->add(new Sprite(0, 0, TextureManager::get("Shield")));
	m_Type = SHIELD;
	m_Angle = 0.0f;
	m_Transformation = &m_Sprite->getTransformRef();
}

void Shield::use()
{
	
}

void Shield::update()
{
	collision();
}

void Shield::render()
{

}

bool Shield::collision()
{
	std::vector<Projectile*> projectiles = m_Player->m_Level->getProjectiles(m_Player, 200);
	bool result = false;
	float angle = m_Angle - M_PI / 2;
	vec2 shieldNormal = vec2(cos(angle), sin(angle)).normalise();
	for (Projectile* p : projectiles)
	{
		const vec2& dir = p->getDirection();

		float dot = shieldNormal.dot(dir.normalise());		
		const vec2& a = p->getPosition();
		const vec2 sa = p->getSprite()->getSize();
		const vec2& b = m_Player->getPosition();
		const vec2 sb = m_Player->getSprite()->getSize() + 16;

		if (a.x + sa.x > b.x && a.x < b.x + sb.x)
		{
			if (a.y + sa.y > b.y && a.y < b.y + sb.y)
			{
				if (dot > 0.0f)
				{
					vec2 nd = dir.normalise() - vec2(shieldNormal.x * 2, shieldNormal.y * 2) * dot;
					p->setDirection(vec3(nd * p->getSpeed())/*vec3(-dir.x, -dir.y, 0.0f)*/);
					p->setOwner(m_Player);
					p->resetLifeSpan();
					m_Player->m_Score += 20;
					p->setScore(100 + (m_Player->m_JumpTimer < 6.0f) * 100);
					audio::SoundManager::get("Ricochet")->play();
					audio::SoundManager::get("Ricochet")->setGain(0.15f);
				}
				else
				{
					audio::SoundManager::get("Hurt")->play();
					audio::SoundManager::get("Hurt")->setGain(0.40f);
					m_Player->damage(rand() % 40);
					p->remove();
				}
				result = true;
			}
		}
		
	}
	
	return result;
}

void Shield::setAngle(float angle)
{
	m_Angle = angle;
	*m_Transformation = mat4::translation(vec3(-16, -16, 0)) * mat4::translation(vec3(48, 48, 0)) * mat4::rotation(toDegrees(angle), vec3(0, 0, 1)) * mat4::translation(vec3(-48, -48, 0));
}
