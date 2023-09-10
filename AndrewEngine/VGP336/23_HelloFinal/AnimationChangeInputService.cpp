#include "AnimationChangeInputService.h"
#include "AnimationChangeComponent.h"
#include <Input/Inc/InputSystem.h>

using namespace AndrewEngine;
using namespace AndrewEngine::Input;

void AnimationChangeInputService::Initialize()
{
}

void AnimationChangeInputService::Terminate()
{
    mAnimationChangeComponents.clear();
}

void AnimationChangeInputService::Update(float deltaTime)
{
    auto input = InputSystem::Get();
    if (input->IsKeyPressed(KeyCode::UP) && input->IsKeyDown(KeyCode::SPACE))
    {
        SetAllAnimationIndex(1);
    }
    else if (input->IsKeyPressed(KeyCode::DOWN) && input->IsKeyDown(KeyCode::SPACE))
    {
        SetAllAnimationIndex(2);
    }
    else if (input->IsKeyPressed(KeyCode::RIGHT) && input->IsKeyDown(KeyCode::SPACE))
    {
        SetAllAnimationIndex(4);
    }
    else if (input->IsKeyPressed(KeyCode::LEFT) && input->IsKeyDown(KeyCode::SPACE))
    {
        SetAllAnimationIndex(3);
    }
}

void AnimationChangeInputService::SetAllAnimationIndex(int index)
{
    for (auto& animChangeComponent : mAnimationChangeComponents)
    {
        animChangeComponent->SetAnimation(index);
    }
}

void AnimationChangeInputService::Register(AnimationChangeComponent* animationChangeComponent)
{
    if (std::find(mAnimationChangeComponents.begin(), mAnimationChangeComponents.end(), animationChangeComponent) == mAnimationChangeComponents.end())
    {
        mAnimationChangeComponents.push_back(animationChangeComponent);
    }
}

void AnimationChangeInputService::Unregister(const AnimationChangeComponent* animationChangeComponent)
{
    auto iter = std::find(mAnimationChangeComponents.begin(), mAnimationChangeComponents.end(), animationChangeComponent);
    if (iter != mAnimationChangeComponents.end())
    {
        mAnimationChangeComponents.erase(iter);
    }
}