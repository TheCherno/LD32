#include "Nuke.h"
#include "Level.h"
#include "../LD32Application.h"

Nuke::Nuke(float x)
	: Entity(x, 2000)
{
	m_Sprite = new sparky::graphics::Sprite(0, 0, 0, 0, 0xff);
	m_Light = m_Position;
	m_Intensity = 3000.0f;
	m_FadeOut = 1.0f;
}

void Nuke::init(Level* level)
{
	Entity::init(level);
	m_Shader = m_Level->m_LevelLayer->getShader();
	m_BGShader = m_Level->m_BackgroundLayer->getShader();
}

void Nuke::update()
{
	m_Position.y -= 10;
	if (m_Position.y < 300)
		m_Position.y = 300;
	sparky::maths::vec2 offset = m_Level->getOffset();
	// m_Light = sparky::maths::vec3(m_Position.x - offset.x, m_Position.y - offset.y, 0);
	if (m_Position.y < 320)
		m_Intensity += 1000;
	if (m_Intensity > 25000 && m_FadeOut > 0.0f)
		m_FadeOut -= 0.005f;

	if (m_FadeOut < 0.1f)
		LD32Application::INSTANCE->end();
}

void Nuke::render()
{
	m_Shader->enable();
	m_Shader->setUniform2f("nuke_pos", m_Position);
	m_Shader->setUniform1f("nuke_intensity", m_Intensity);
	m_Shader->setUniform1f("fade_out", m_FadeOut);

	m_BGShader->enable();
	m_BGShader->setUniform2f("nuke_pos", m_Position);
	m_BGShader->setUniform1f("nuke_intensity", m_Intensity);
	m_BGShader->setUniform1f("fade_out", m_FadeOut);

}

