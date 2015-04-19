#pragma once

#include <sparky.h>
#include "../Entity.h"

class Fighter : public Entity
{
private:
	float m_AverageAltitude, m_AltitudeRange, m_HorizontalRange, m_Speed, m_Range;
	float xa, ya;
	unsigned int m_Time;
public:
	Fighter(float x, float y);
	void update() override;
	void render() override;
};