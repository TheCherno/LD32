#pragma once

#include <sparky.h>
#include "Item.h"

class Player;

class Shield : public Item
{
private:
	float m_Angle;
	sparky::maths::mat4* m_Transformation;
	Player* m_Player;
public:
	Shield(Player* player);
	void use() override;
	void update() override;
	void render() override;

	bool collision();
	void setAngle(float angle);
};