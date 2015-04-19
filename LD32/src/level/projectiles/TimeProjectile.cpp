#include "TimeProjectile.h"

using namespace sparky;
using namespace maths;

TimeProjectile::TimeProjectile(float x, float y, float angle, Entity* owner)
	: Projectile(x, y, new graphics::Sprite(0, 0, graphics::TextureManager::get("Projectile")), owner)
{
	m_Speed = 20.0f;
	m_Direction = vec3(cos(angle) * m_Speed, sin(angle) * m_Speed, 0.0f);
	m_DirectionVec2 = vec2(m_Direction);
}

void TimeProjectile::update()
{
	Projectile::update();
	m_Position += m_Direction;
}