#include "Precompiled.h"
#include "RenderObject.h"

using namespace AndrewEngine;
using namespace AndrewEngine::Graphics;
void AndrewEngine::Graphics::RenderObject::Terminate()
{
    diffuseMapId = 0;
    meshBuffer.Terminate();
}
