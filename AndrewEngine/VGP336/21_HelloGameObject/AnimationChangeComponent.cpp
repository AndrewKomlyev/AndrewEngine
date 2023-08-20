#include "AnimationChangeComponent.h"
#include <AndrewEngine/Inc/GameObject.h>
#include <AndrewEngine/Inc/GameWorld.h>
#include <AndrewEngine/Inc/AnimationComponent.h>
#include "AnimationChangeInputService.h"

void AnimationChangeComponent::Initialize()
{
    mAnimationComponent = GetOwner().GetComponent<AndrewEngine::AnimationComponent>();

    auto animChangeInputService = GetOwner().GetWorld().GetService<AnimationChangeInputService>();
    animChangeInputService->Register(this);


}

void AnimationChangeComponent::Terminate()
{
    auto animChangeInputService = GetOwner().GetWorld().GetService<AnimationChangeInputService>();
    animChangeInputService->Unregister(this);
    
    mAnimationComponent = nullptr;

}

void AnimationChangeComponent::Update(float deltaTime)
{
}

void AnimationChangeComponent::SetAnimation(int index)
{
    mAnimationComponent->GetAnimator().PlayAnimation(index, true);
}
