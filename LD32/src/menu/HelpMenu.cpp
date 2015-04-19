#include "HelpMenu.h"
#include "../State.h"
#include "../LD32Application.h"

using namespace sparky;
using namespace graphics;

static void HelpMenu_okay()
{
	LD32Application::INSTANCE->setMainMenu();
}

HelpMenu::HelpMenu(Window* window)
	: Menu(window, new Sprite(0, 0, TextureManager::get("Menu_Help")))
{
	m_Layer->add(new Label("Back", 1180, 40, 0xffffffff));
	m_SelectedMapping[0] = maths::vec2(1160, 45);
	create();

	m_ActionMapping[0] = HelpMenu_okay;
}

void HelpMenu::update()
{
	Menu::update();
}

void HelpMenu::render()
{
	Menu::render();
}