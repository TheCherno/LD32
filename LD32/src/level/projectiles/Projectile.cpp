#include "Projectile.h"
#include "../Level.h"

void Projectile::render()
{
	const sparky::maths::vec2& offset = m_Level->getOffset();
	m_Sprite->position = m_Position - sparky::maths::vec3(offset);
}

void Projectile::resetLifeSpan()
{
	m_Time = 0;
}
