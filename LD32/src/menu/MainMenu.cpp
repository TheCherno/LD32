#include "MainMenu.h"
#include "../State.h"
#include "../LD32Application.h"

using namespace sparky;
using namespace graphics;

static void MainMenu_play()
{
	State::setState(STATE_GAME);
	LD32Application::INSTANCE->begin();
}

static void MainMenu_help()
{
	LD32Application::INSTANCE->setHelpMenu();
}

static void MainMenu_about()
{
	LD32Application::INSTANCE->setAboutMenu();
}

static void MainMenu_quit()
{
	std::exit(0);
}

MainMenu::MainMenu(Window* window)
	: Menu(window, new Sprite(0, 0, TextureManager::get("Menu_Main")))
{
	m_Layer->add(new Label("Play", 40, 190, 0xffffffff));
	m_Layer->add(new Label("Help", 40, 140, 0xffffffff));
	m_Layer->add(new Label("About", 40, 90, 0xffffffff));
	m_Layer->add(new Label("Quit", 40, 40, 0xffffffff));
	create();

	m_SelectedMapping[0] = maths::vec2(20, 195);
	m_SelectedMapping[1] = maths::vec2(20, 145);
	m_SelectedMapping[2] = maths::vec2(20, 95);
	m_SelectedMapping[3] = maths::vec2(20, 45);

	m_ActionMapping[0] = MainMenu_play;
	m_ActionMapping[1] = MainMenu_help;
	m_ActionMapping[2] = MainMenu_about;
	m_ActionMapping[3] = MainMenu_quit;
}

void MainMenu::update()
{
	Menu::update();
}

void MainMenu::render()
{
	Menu::render();
}