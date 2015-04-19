#pragma once

#include <sparky.h>
#include "Projectile.h"

class TimeProjectile : public Projectile
{
public:
	TimeProjectile(float x, float y, float angle, Entity* owner);
	void update() override;
};