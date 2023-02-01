#pragma once
#include "Colours.h"

namespace AndrewEngine::Graphics
{
    struct DirectionalLight
    {
        AEMath::Vector3 direction = AEMath::Vector3::Zero;
        float padding = 0.0f;
        Color ambient = Colors::White;
        Color diffuse = Colors::White;
        Color specular = Colors::White;


    };
}