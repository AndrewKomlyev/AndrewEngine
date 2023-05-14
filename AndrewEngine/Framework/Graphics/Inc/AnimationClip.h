#pragma once

#include "Animation.h"


namespace AndrewEngine::Graphics
{
    class AnimationClip
    {
    public:
        std::string name;
        float tickDuration = 0.0f;
        float tickPerSecond = 0.0f;

        std::vector < std::unique_ptr<Animation>> boneAnimations;


    };
}