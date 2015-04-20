#include "LD32Application.h"

using namespace audio;
using namespace graphics;
using namespace maths;

LD32Application* LD32Application::INSTANCE = nullptr;
DebugLayer* LD32Application::debugLayer = nullptr;
unsigned int State::m_Current = 0;
bool State::m_GameOver = false;

LD32Application::LD32Application()
{
	INSTANCE = this;
	State::setState(STATE_MENU);
	m_Difficulty = 0;
	m_Level = nullptr;
}

LD32Application::~LD32Application()
{
	delete m_UILayer;
	if (m_Level != nullptr)
		delete m_Level;
	delete debugLayer;

	delete m_MenuMain;
	delete m_MenuGameOver;
	delete m_MenuHelp;
	delete m_MenuAbout;
}

void LD32Application::init()
{
	m_Window = createWindow("Shift", 1280, 720);
	loadAssets();
	
	debugLayer = new DebugLayer();
	m_UILayer = new UILayer();
	m_FPS = new Label("", m_Window->getWidth() - 120, m_Window->getHeight() - 35, 0xffffffff);
	debugLayer->add(m_FPS);

	m_MenuMain = new MainMenu(m_Window);
	m_MenuGameOver = new GameOverMenu(m_Window);
	m_MenuHelp = new HelpMenu(m_Window);
	m_MenuAbout = new AboutMenu(m_Window);

	m_Menu = m_MenuMain;
	
	SoundManager::get("Music")->loop();
}

void LD32Application::loadAssets()
{
	TextureManager::add(new Texture("Player", "res/player.png"));
	TextureManager::add(new Texture("Fighter", "res/ship_final.png"));
	TextureManager::add(new Texture("Shield", "res/shield.png"));
	TextureManager::add(new Texture("Portal", "res/portal.png"));
	TextureManager::add(new Texture("Projectile", "res/projectile.png"));
#ifdef SPARKY_EMSCRIPTEN
	TextureManager::add(new Texture("Level_Background", "res/level/web/background.png"));
	TextureManager::add(new Texture("Platform", "res/level/web/platform.png"));
#else
	TextureManager::add(new Texture("Level_Background", "res/level/background.png"));
	TextureManager::add(new Texture("Platform", "res/level/platform.png"));
#endif
	TextureManager::add(new Texture("Ground", "res/level/ground.png"));

	// Menu Images
	TextureManager::add(new Texture("Menu_Main", "res/menu/menu_main.png"));
	TextureManager::add(new Texture("Menu_Help", "res/menu/menu_help.png"));
	TextureManager::add(new Texture("Menu_About", "res/menu/menu_about.png"));
	TextureManager::add(new Texture("Menu_Gameover", "res/menu/menu_gameover.png"));

	FontManager::add(new Font("Handwritten", "res/CoertSchrift_Romaans.ttf", 64));

	SoundManager::add(new Sound("Music", "res/Shift.ogg"));
	SoundManager::add(new Sound("Shoot", "res/audio/shoot.ogg"));
	SoundManager::add(new Sound("Ricochet", "res/audio/ricochet.ogg"));
	SoundManager::add(new Sound("Hurt", "res/audio/hurt.ogg"));
}

void LD32Application::tick()
{
	// m_FPS->text = std::to_string(getFPS()) + " fps";
}

void LD32Application::update()
{
	switch (State::getState())
	{
	case STATE_MENU:
	{
		m_Menu->update();
		break;
	}
	case STATE_GAME:
	{
		if (State::isGameOver())
		{
			m_Level->endGame();
		}
		m_Level->update();
		break;
	}
	}
}

void LD32Application::nextLevel()
{
	const float health = m_Level->getPlayer()->getHealth();
	const unsigned int score = m_Level->getPlayer()->getScore();
	delete m_Level;
	m_Level = new Level(m_Difficulty++);
	m_Level->addPlayer(new Player(30, 800, m_Window));
	m_Level->getPlayer()->setHealth(health);
	m_Level->getPlayer()->setScore(score);
	m_Level->start();
}

void LD32Application::render()
{
	switch (State::getState())
	{
	case STATE_MENU:
	{
		m_Menu->render();
		break;
	}
	case STATE_GAME:
	{
		m_Level->render();
		debugLayer->render();
		break;
	}
	}
//	m_UILayer->render();
}

void LD32Application::begin()
{
	m_Level = new Level(m_Difficulty++);
	m_Level->addPlayer(new Player(30, 800, m_Window));
	m_Level->start();
}

void LD32Application::end()
{
	((GameOverMenu*)m_MenuGameOver)->setScore(m_Level->getPlayer()->getScore(), m_Level->getDifficulty());
	State::setState(STATE_MENU);
	m_Menu = m_MenuGameOver;
	delete m_Level;
	State::setGameOver(false);
	m_Difficulty = 0;
}

void LD32Application::setMainMenu()
{
	m_Menu = m_MenuMain;
}

void LD32Application::setHelpMenu()
{
	m_Menu = m_MenuHelp;
}

void LD32Application::setAboutMenu()
{
	m_Menu = m_MenuAbout;
}
