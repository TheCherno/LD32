#pragma once

#include "Menu.h"

class HelpMenu : public Menu
{
private:
	
public:
	HelpMenu(sparky::graphics::Window* window);
	void update() override;
	void render() override;
};