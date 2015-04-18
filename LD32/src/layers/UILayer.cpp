#include "UILayer.h"

using namespace sparky;
using namespace graphics;

UILayer::UILayer()
	: Layer(new BatchRenderer2D(), new Shader("shaders/ui.vert", "shaders/ui.frag"), maths::mat4::orthographic(0, 960, 0, 540, -1, 1))
{

}

UILayer::~UILayer()
{

}
