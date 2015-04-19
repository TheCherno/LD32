#pragma once

#include "Menu.h"

class MainMenu : public Menu
{
private:
	
public:
	MainMenu(sparky::graphics::Window* window);
	void update() override;
	void render() override;
};