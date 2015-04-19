#pragma once

#include <sparky.h>
#include <map>
#include "../layers/UILayer.h"

class Menu
{
protected:
	sparky::graphics::Sprite* m_Selector;
	sparky::graphics::Label** m_Options;
	unsigned int m_Selected;
	UILayer* m_Layer;
	std::map<unsigned int, sparky::maths::vec2> m_SelectedMapping;
	std::map<unsigned int, void(*)()> m_ActionMapping;
	sparky::graphics::Window* m_Window;
public:
	Menu(sparky::graphics::Window* window, sparky::graphics::Sprite* sprite = nullptr)
	{
		m_Layer = new UILayer();
		if (sprite != nullptr)
			m_Layer->add(sprite);
		m_Selector = new sparky::graphics::Sprite(0, 0, 8, 8, 0xffffffff);
		m_Selected = 0;
		m_Layer->add(m_Selector);
		m_Window = window;
	}

	void create()
	{

	}

	virtual void update()
	{
		m_Selector->position = m_SelectedMapping[m_Selected];
		if (m_Window->isKeyTyped(GLFW_KEY_DOWN) || m_Window->isKeyTyped(GLFW_KEY_S))
		{
			m_Selected++;
			if (m_Selected > m_SelectedMapping.size() - 1)
				m_Selected = m_SelectedMapping.size() - 1;
		}
		else if (m_Window->isKeyTyped(GLFW_KEY_UP) || m_Window->isKeyTyped(GLFW_KEY_W))
		{
			if (m_Selected > 0)
				m_Selected--;
		}
		else if (m_Window->isKeyTyped(GLFW_KEY_SPACE) || m_Window->isKeyTyped(GLFW_KEY_ENTER))
		{
			m_ActionMapping[m_Selected]();
		}
	}

	virtual void render()
	{
		m_Layer->render();
	}
};