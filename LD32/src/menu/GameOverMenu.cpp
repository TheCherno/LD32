#include "GameOverMenu.h"
#include "../State.h"
#include "../LD32Application.h"

using namespace sparky;
using namespace graphics;

static void GameOverMenu_okay()
{
 	LD32Application::INSTANCE->setMainMenu();
}

GameOverMenu::GameOverMenu(sparky::graphics::Window* window)
	: Menu(window, new Sprite(0, 0, TextureManager::get("Menu_Gameover")))
{
	m_Score = new Label("", 300, 150, "Handwritten", 0xaaaaaaaa);
	m_Stage = new Label("", 600, 60, "Handwritten", 0x88888888);
	m_Layer->add(m_Score);
	m_Layer->add(m_Stage);
	m_Layer->add(new Label("End", 1200, 40, 0xffffffff));
	m_SelectedMapping[0] = maths::vec2(1180, 45);
	create();

	m_ActionMapping[0] = GameOverMenu_okay;
}

void GameOverMenu::update()
{
	Menu::update();
}

void GameOverMenu::render()
{
	Menu::render();
}

void GameOverMenu::setScore(unsigned int score, unsigned int stage)
{
	m_Score->text = "Score: " + std::to_string(score);
	m_Stage->text = "Stage: " + std::to_string(stage + 1);

}
