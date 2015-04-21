#include "Entity.h"
#include "../level.h"
#include "../../LD32Application.h"

Entity::Entity(float x, float y)
	: m_Position(sparky::maths::vec3(x, y, 0.0f)), m_Removed(false), m_CollisionDirection(NONE), m_Health(100.0f), m_Type(NIL)
{

}

void Entity::init(Level* level)
{
	m_Level = level;
}

bool Entity::hasCollided(float xa, float ya) const
{
	using namespace sparky;
	using namespace maths;

	std::vector<LevelObject*> objects = m_Level->getObjects(this, 640);

	for (LevelObject* object : objects)
	{
		if (!object->isCollidable())
			continue;

		const vec3& pos = object->getPosition();
		const vec2& size = object->getSize();

		if (m_Position.x + xa <= pos.x + size.x && m_Position.x + xa + m_Sprite->getSize().x >= pos.x)
			if (m_Position.y + ya <= pos.y + size.y && m_Position.y + ya + m_Sprite->getSize().y >= pos.y)
				return true;
	}
	return false;
}

int Entity::collision(float& xa, float& ya) const
{
	using namespace sparky;
	using namespace maths;

	if (xa == 0 && ya == 0)
		return NONE;

	float xao = xa;
	float yao = ya;

	bool x = false;
	bool y = false;

	float xx = sign(xao);
	float xb = abs(xa);
	while (xb >= 1.0f)
	{
		x = hasCollided(xx, 0);
		if (x)
		{
			xa = xx - sign(xao) - 0.5f * sign(xao);
			break;
		}
		xx += sign(xao);
		xb--;
	}

	if (xb < 1.0f)
		x = hasCollided(xx + xb * sign(xao), 0);

	float yy = sign(yao);
	float yb = abs(ya);
	while (yb >= 1.0f)
	{
		y = hasCollided(0, yy);
		if (y)
		{
			ya = yy - sign(yao) - 0.5f * sign(yao);
			break;
		}
		yy += sign(yao);
		yb--;
	}

	if (yb < 1.0f)
		y = hasCollided(0, yy + yb * sign(yao));

	int result = 0x0;
	if (x)
		result |= xao < 0 ? 0x0F00 : 0xF000;
	if (y)
		result |= yao < 0 ? 0x00F0 : 0x000F;

	return result;
}

void Entity::move(float xa, float ya)
{
	// TODO: Collision!
	float xo = xa;
	float yo = ya;
	int cDir = collision(xa, ya);
	std::cout << std::hex << cDir << std::endl;
	if ((cDir & 0x00F0) > 0x0)
		m_CollisionDirection = BOTTOM;
	else
		m_CollisionDirection = NONE;
#if 0
	LD32Application::debugLayer->text(10) = "Direction: " + directionToString(m_CollisionDirection);
	LD32Application::debugLayer->text(11) = std::to_string(xa) + "(" + std::to_string(xo) + "), " + std::to_string(ya) + "(" + std::to_string(yo) + ")";
#endif

	if ((cDir & 0xFF00) == 0x0 || xo != xa)
		m_Position.x += xa;

	if ((cDir & 0x00FF) == 0x0 || yo != ya)
		m_Position.y += ya;

}

Projectile* Entity::projectileCollision() const
{
	using namespace maths;

	std::vector<Projectile*> projectiles = m_Level->getProjectiles(this, 128);
	for (Projectile* p : projectiles)
	{
		if (p->getOwner() == this || p->getOwner()->m_Type == ENEMY)
			continue;

		const vec2& a = p->getPosition();
		const vec2 sa = p->getSprite()->getSize();
		const vec2& b = getPosition();
		const vec2 sb = getSprite()->getSize() + 16;

		if (a.x + sa.x > b.x && a.x < b.x + sb.x)
		{
			if (a.y + sa.y > b.y && a.y < b.y + sb.y)
			{
				p->remove();
				return p;
			}
		}

	}
	return nullptr;
}
	