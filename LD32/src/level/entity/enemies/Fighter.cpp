#include "Fighter.h"
#include "../Player.h"
#include "../../Level.h"
#include "../../../LD32Application.h"
#include "../../projectiles/TimeProjectile.h"

using namespace sparky;
using namespace graphics;
using namespace maths;

Fighter::Fighter(float x, float y)
	: Entity(x, y)
{
	m_AverageAltitude = 500 + rand() % 250;
	m_AltitudeRange = 200.0f;
	m_HorizontalRange = 200.0f;
	m_Sprite = new Sprite(0, 0, 128, 128, TextureManager::get("Fighter"));
	m_Speed = 3.0f + rand() % 6;
	xa = 0;
	ya = 0;
	m_Time = 0;
	m_Range = 400;
	
	m_Type = ENEMY;
}

void Fighter::update()
{
	m_Time++;
	const vec3& player = m_Level->getPlayer()->getPosition();

	// Movement
	if (m_Time % (rand() % 60 + 30) == 0)
	{
		xa = (rand() % 3 - 1) * m_Speed;
		ya = (rand() % 3 - 1) * m_Speed;
	}

	if (m_Time % (rand() % 60 + 30) == 0)
	{
		float distance = player.distance(m_Position);
		if (distance < m_Range)
		{
			float angle = atan2(m_Position.y - player.y, m_Position.x - player.x) + M_PI;
			m_Level->addProjectile(new TimeProjectile(m_Position.x + 64, m_Position.y + 64, angle, this));
		}
	}

	// Overrides
	if (abs(m_Position.x - player.x) > m_HorizontalRange)
	{
		xa = sign(player.x - m_Position.x) * m_Speed;
	}

	if (m_Position.y > m_AverageAltitude + m_AltitudeRange)
		ya = -m_Speed;
	else if (m_Position.y < m_AverageAltitude - m_AltitudeRange)
		ya = m_Speed;
	move(xa, ya);

	Projectile* p = projectileCollision();
	if (p != nullptr)
	{
		m_Level->getPlayer()->addScore(p->getScore());
		damage(rand() % 80);
	}

	if (m_Health < 0)
		remove();
}

void Fighter::render()
{
}
