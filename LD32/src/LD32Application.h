#pragma once

#include <sparky.h>

#include "layers/UILayer.h"

#define APPLICATION LD32Application

using namespace sparky;

class LD32Application : public Sparky
{
private:
	graphics::Window* m_Window;
	graphics::Label* m_FPS;
	UILayer* m_UILayer;
public:
	LD32Application();
	~LD32Application();

	void init() override;
	void tick() override;
	void update() override;
	void render() override;
};