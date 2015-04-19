#pragma once

#include "Menu.h"

class AboutMenu : public Menu
{
private:
	
public:
	AboutMenu(sparky::graphics::Window* window);
	void update() override;
	void render() override;
};