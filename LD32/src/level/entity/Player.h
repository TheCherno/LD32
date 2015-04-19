#pragma once

#include <sparky.h>
#include "Entity.h"
#include "../Nuke.h"
#include "../projectiles/TimeProjectile.h"
#include "../items/Item.h"
#include "../items/Shield.h"

class Player : public Entity
{
friend class Shield;
private:
	sparky::graphics::Window* m_Window;
	sparky::graphics::Group* m_Group;
	float m_Speed, m_Gravity, m_MaxVerticalVelocity, m_JumpTimer;
	bool m_CanDoubleJump;
	sparky::maths::vec2 m_Delta;
	std::vector<Item*> m_Items;
	sparky::maths::mat4& m_Transformation;
	sparky::maths::vec3 m_ScreenPos;
	unsigned int m_SelectedItem;
	unsigned int m_Score;
	bool m_ShieldFall;
public:
	Player(float x, float y, sparky::graphics::Window* window);
	void shoot();
	void update() override;
	void render() override;

	void addScore(unsigned int score);
	void setPosition(float x, float y);
	const float getHealth() const { return m_Health; }
	void setHealth(float health) { m_Health = health; }
	const float getScore() const { return m_Score; }
	void setScore(unsigned int score) { m_Score= score; }
};