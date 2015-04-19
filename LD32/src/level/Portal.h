#pragma once

#include <sparky.h>

class Portal
{
private:
	sparky::maths::vec2 m_Position;
	sparky::graphics::Sprite* m_Sprite;
public:
	Portal(const sparky::maths::vec2& position)
		: m_Position(position)
	{
		m_Sprite = new sparky::graphics::Sprite(0, 0, sparky::graphics::TextureManager::get("Portal"));
	}

	sparky::graphics::Sprite* getSprite() const { return m_Sprite; }
	const sparky::maths::vec2& getPosition() const { return m_Position; }
};