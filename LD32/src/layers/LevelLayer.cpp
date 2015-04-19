#include "LevelLayer.h"

using namespace sparky;
using namespace graphics;

LevelLayer::LevelLayer()
	: Layer(new BatchRenderer2D(),
#ifdef SPARKY_EMSCRIPTEN
	new Shader("shaders/es3/level.es3.vert", "shaders/es3/level.es3.frag")
#else
	new Shader("shaders/level.vert", "shaders/level.frag")
#endif
	, maths::mat4::orthographic(0, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f))
{

}

LevelLayer::~LevelLayer()
{

}

void LevelLayer::remove(void* pointer)
{
	for (int i = 0; i < m_Renderables.size(); i++)
	{
		if (m_Renderables[i] == pointer)
		{
			delete m_Renderables[i];
			m_Renderables.erase(m_Renderables.begin() + i);
			return;
		}
	}
}
