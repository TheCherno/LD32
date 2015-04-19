#include "AboutMenu.h"
#include "../State.h"
#include "../LD32Application.h"

using namespace sparky;
using namespace graphics;

static void AboutMenu_okay()
{
	LD32Application::INSTANCE->setMainMenu();
}

AboutMenu::AboutMenu(Window* window)
	: Menu(window, new Sprite(0, 0, TextureManager::get("Menu_About")))
{
	m_Layer->add(new Label("Back", 1180, 40, 0xffffffff));
	m_SelectedMapping[0] = maths::vec2(1160, 45);
	create();

	m_ActionMapping[0] = AboutMenu_okay;
}

void AboutMenu::update()
{
	Menu::update();
}

void AboutMenu::render()
{
	Menu::render();
}