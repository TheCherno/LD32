#pragma once

#include <sparky.h>

#include "layers/UILayer.h"
#include "layers/DebugLayer.h"
#include "level/Level.h"
#include "level/entity/Player.h"

#include "menu/Menu.h"
#include "menu/MainMenu.h"
#include "menu/GameOverMenu.h"
#include "menu/HelpMenu.h"
#include "menu/AboutMenu.h"

#include "State.h"

#define APPLICATION LD32Application

using namespace sparky;

class LD32Application : public Sparky
{
public:
	static DebugLayer* debugLayer;
	static LD32Application* INSTANCE;
private:
	graphics::Window* m_Window;
	graphics::Label* m_FPS;
	UILayer* m_UILayer;
	Level* m_Level;
	Menu* m_Menu;
	Menu *m_MenuMain, *m_MenuGameOver, *m_MenuHelp, *m_MenuAbout;
	unsigned int m_Difficulty;
public:
	LD32Application();
	~LD32Application();

	void init() override;
	void tick() override;
	void update() override;
	void render() override;

	void begin();
	void nextLevel();
	void end();

	void setMainMenu();
	void setHelpMenu();
	void setAboutMenu();
private:
	void loadAssets();
};