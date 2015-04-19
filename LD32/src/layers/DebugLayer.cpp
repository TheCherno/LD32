#include "DebugLayer.h"

using namespace sparky;
using namespace graphics;

DebugLayer::DebugLayer()
	: Layer(new BatchRenderer2D(),
#ifdef SPARKY_EMSCRIPTEN
	new Shader("shaders/es3/ui.es3.vert", "shaders/es3/ui.es3.frag")
#else
	new Shader("shaders/ui.vert", "shaders/ui.frag")
#endif
	, maths::mat4::orthographic(0, 1280, 0, 720, -1, 1))
{
	m_Labels = new Label*[20];
	m_Points = new Sprite*[20];
	for (int i = 0; i < 20; i++)
	{
		m_Labels[i] = new graphics::Label("", 10, 680 - i * 34, 0xffffffff);
		add(m_Labels[i]);

		m_Points[i] = new graphics::Sprite(-5, -5, 5, 5, 0xffff00ff);
		add(m_Points[i]);
	}
}

DebugLayer::~DebugLayer()
{
	delete[] m_Labels;
	delete[] m_Points;
}
