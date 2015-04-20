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
	: Menu(window, new Sprite(0, 0, 1280, 720, TextureManager::get(
#ifdef SPARKY_EMSCRIPTEN
	"Menu_Help_About"
#else
	"Menu_About"
#endif
	)))
{
#ifdef SPARKY_EMSCRIPTEN
	std::vector<maths::vec2> uv(4);
	uv[0] = maths::vec2(0, 0.3515625f);
	uv[1] = maths::vec2(0, 0.3515625f * 2.0f);
	uv[2] = maths::vec2(0.625f, 0.3515625f * 2.0f);
	uv[3] = maths::vec2(0.625f, 0.3515625f);
	m_Sprite->setUV(uv);
#endif

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