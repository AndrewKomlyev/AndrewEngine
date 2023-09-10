#pragma once
#include <AndrewEngine/Inc/Component.h>
#include "TypeIds.h"

namespace AndrewEngine
{
    class AnimationComponent;
}

class AnimationChangeComponent final: public AndrewEngine::Component
{

public:
    SET_TYPE_ID(CustomComponentId::AnimationChangeComponentId);

    void Initialize() override;
    void Terminate() override;

    void Update(float deltaTime) override;

    void SetAnimation(int index);

private:

    AndrewEngine::AnimationComponent* mAnimationComponent = nullptr;
};
