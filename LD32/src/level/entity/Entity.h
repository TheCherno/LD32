#pragma once

#include <sparky.h>
#include "../objects/LevelObject.h"

class Level;
class Projectile;

enum Direction
{
	NONE = 0x0000, TOP = 0x000F, BOTTOM = 0x00F0, LEFT = 0x0F00, RIGHT = 0xF000
};

enum EntityType
{
	NIL, PLAYER, ENEMY
};

class Entity
{
protected:
	sparky::maths::vec3 m_Position;
	bool m_Removed;
	Level* m_Level;
	sparky::graphics::Sprite* m_Sprite;
	sparky::graphics::Renderable2D* m_Renderable;
	float m_Health;
	EntityType m_Type;
protected:
	Entity(float x, float y);
	Direction m_CollisionDirection;
public:
	virtual ~Entity() {}
	virtual void init(Level* level);

	void move(float xa, float ya);

	virtual void update() = 0;
	virtual void render() = 0;

	void remove() { m_Removed = true; }
	void damage(unsigned int d) { m_Health -= d; }

	inline const sparky::maths::vec3& getPosition() const { return m_Position; }
	inline sparky::maths::vec2 getCenter() const { return sparky::maths::vec2(m_Position.x + m_Sprite->getSize().x / 2.0f, m_Position.y + m_Sprite->getSize().y / 2.0f); }
	inline sparky::graphics::Sprite* getSprite() const { return m_Sprite; }
	inline sparky::graphics::Renderable2D* getRenderable() const { return m_Renderable; }
	inline const bool isRemoved() const { return m_Removed; }
protected:
	Projectile* projectileCollision() const;
private:
	bool hasCollided(float xa, float ya) const;
	int collision(float& xa, float& ya) const;

	std::string directionToString(Direction dir)
	{
		switch (dir)
		{
		case NONE:
			return "None";
		case TOP:
			return "Top";
		case BOTTOM:
			return "Bottom";
		case LEFT:
			return "Left";
		case RIGHT:
			return "Right";
		}

		return "Unknown";
	}
};