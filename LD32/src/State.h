#pragma once

#define STATE_NULL 0
#define STATE_MENU 1
#define STATE_GAME 2
#define GAME_OVER 3

class State
{
private:
	static unsigned int m_Current;
	static bool m_GameOver;
public:
	inline static void setState(unsigned int state) { m_Current = state; }
	inline static unsigned int getState() { return m_Current; }

	inline static bool isGame() { return m_Current == STATE_GAME; }
	inline static bool isMenu() { return m_Current == STATE_MENU; }

	inline static void setGameOver(bool gameover) { m_GameOver = gameover; }
	inline static bool isGameOver() { return m_GameOver; }
};