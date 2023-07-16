#include "Precompiled.h"
#include "TransformComponent.h"

using namespace AndrewEngine;

void TransformComponent::DebugUI()
{
    Graphics::SimpleDraw::AddTransform(GetMatrix4());
}
