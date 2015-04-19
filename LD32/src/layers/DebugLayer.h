#pragma once

#include <sparky.h>

class DebugLayer : public sparky::graphics::Layer
{
private:
	sparky::graphics::Label** m_Labels;
	sparky::graphics::Sprite** m_Points;
public:
	DebugLayer();
	~DebugLayer();

	std::string& text(int line) { return m_Labels[line]->text; }
	sparky::maths::vec3& point(int index) { return m_Points[index]->position; }
};