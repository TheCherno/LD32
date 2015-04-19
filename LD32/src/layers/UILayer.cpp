#include "UILayer.h"

using namespace sparky;
using namespace graphics;

UILayer::UILayer()
	: Layer(new BatchRenderer2D(),
#ifdef SPARKY_EMSCRIPTEN
	new Shader("shaders/es3/ui.es3.vert", "shaders/es3/ui.es3.frag")
#else
	new Shader("shaders/ui.vert", "shaders/ui.frag")
#endif
	, maths::mat4::orthographic(0, 1280, 0, 720, -1, 1))
{

}

UILayer::~UILayer()
{

}
