#include "LD32Application.h"

using namespace audio;
using namespace graphics;
using namespace maths;

LD32Application::LD32Application()
{

}

LD32Application::~LD32Application()
{
	delete m_UILayer;
}

void LD32Application::init()
{
	m_Window = createWindow("LD32", 960, 540);
	
	m_UILayer = new UILayer();
	m_FPS = new Label("", m_Window->getWidth() - 120, m_Window->getHeight() - 35, 0xffffffff);
	m_UILayer->add(m_FPS);
}

void LD32Application::tick()
{
	m_FPS->text = std::to_string(getFPS()) + " fps";
}

void LD32Application::update()
{

}

void LD32Application::render()
{
	m_UILayer->render();
}
