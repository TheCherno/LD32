#pragma once

#include "Menu.h"

class GameOverMenu : public Menu
{
private:
	sparky::graphics::Label* m_Score, *m_Stage;
public:
	GameOverMenu(sparky::graphics::Window* window);
	void update() override;
	void render() override;

	void setScore(unsigned int score, unsigned int stage);
};