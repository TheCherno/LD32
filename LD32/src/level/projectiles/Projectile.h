#pragma once

#include <sparky.h>
#include "../entity/Entity.h"

class Projectile : public Entity
{
protected:
	sparky::maths::vec3 m_Direction;
	sparky::maths::vec2 m_DirectionVec2;
	sparky::maths::vec2 m_Size;
	float m_Speed;
	Entity* m_Owner;
	unsigned int m_LifeSpan;
	unsigned int m_Time;
	unsigned int m_Score;
public:
	Projectile(float x, float y, sparky::graphics::Sprite* sprite, Entity* owner)
		: Entity(x, y), m_Score(0)
	{
		m_Time = 0;
		m_LifeSpan = 60;
		m_Sprite = sprite;
		m_Owner = owner;
	}

	virtual void update() override
	{
		m_Time++;
		if (m_Time > m_LifeSpan)
			remove();
	}

	virtual void render() override;

	void resetLifeSpan();
	const Entity* getOwner() const { return m_Owner; }
	void setOwner(Entity* owner) { m_Owner = owner; }
	const float getSpeed() const { return m_Speed; }
	void setDirection(const sparky::maths::vec2& direction) { m_Direction = sparky::maths::vec3(direction.x, direction.y, 0.0f); }
	inline const sparky::maths::vec2& getDirection() const { return m_DirectionVec2; }

	void setScore(unsigned int score) { m_Score = score; }
	const unsigned int getScore() const { return m_Score; }
};