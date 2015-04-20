#pragma once

#include <sparky.h>

class LevelObject
{
protected:
	sparky::maths::vec3 m_Position;
	sparky::maths::vec2 m_Size;
	sparky::graphics::Sprite* m_Sprite;
	bool m_Collision;
public:
	LevelObject(float x, float y, sparky::graphics::Sprite* sprite, bool collision = true)
		: m_Position(sparky::maths::vec3(x, y, 0)), m_Size(sprite->getSize()), m_Sprite(sprite), m_Collision(collision)
	{
	}

	LevelObject(float x, float y, float width, float height, sparky::graphics::Sprite* sprite, bool collision = true)
		: m_Position(sparky::maths::vec3(x, y, 0)), m_Size(width, height), m_Sprite(sprite), m_Collision(collision)
	{
	}

	inline const sparky::maths::vec3& getPosition() const { return m_Position; }
	inline const sparky::maths::vec2& getSize() const { return m_Size; }
	inline sparky::maths::vec2 getCenter() const { return sparky::maths::vec2(m_Position.x + m_Size.x / 2.0f, m_Position.y + m_Size.y / 2.0f); }
	inline sparky::graphics::Sprite* getSprite() const { return m_Sprite; }

	inline const bool isCollidable() const { return m_Collision; }
};