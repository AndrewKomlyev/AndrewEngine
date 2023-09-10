#include "Precompiled.h"
#include "AnimationComponent.h"

#include "ModelComponent.h"
#include "GameObject.h"

using namespace AndrewEngine;


void AnimationComponent::Initialize()
{
    auto modelComponent = GetOwner().GetComponent<ModelComponent>();
    mAnimator.Initialize(modelComponent->GetModelId());
    mAnimator.PlayAnimation(0, true);
}

void AnimationComponent::Update(float deltaTime)
{
    mAnimator.Update(deltaTime);
}

void AnimationComponent::DebugUI()
{

}

bool AnimationComponent::PlayAnimation(int index, bool looping)
{
    mAnimator.PlayAnimation(index, looping);
    return true;
}
