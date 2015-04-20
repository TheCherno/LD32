#pragma once

#include <sparky.h>
#include "entity/Entity.h"

class Nuke : public Entity
{
private:
	sparky::graphics::Shader* m_Shader, *m_BGShader;
	sparky::maths::vec2 m_Light;
	float m_Intensity;
	float m_FadeOut;
public:
	Nuke(float x);
	void init(Level* level) override;
	void update() override;
	void render() override;
};