#include "CharacterControllerComponent.h"
#include <AndrewEngine/Inc/GameObject.h>
#include <AndrewEngine/Inc/GameWorld.h>
#include <AndrewEngine/Inc/RigidBodyComponent.h>

using namespace AndrewEngine;
using namespace AndrewEngine::Input;



void CharacterControllerComponent::Initialize()
{
    mRigidBodyComponent = GetOwner().GetComponent<RigidBodyComponent>();
    ASSERT(mRigidBodyComponent != nullptr, "FPSCameraControllerComponent: GameObject does not have Camera Component.");

}

void CharacterControllerComponent::Terminate()
{
}

void CharacterControllerComponent::Update(float deltaTime)
{
    bool isAnyKeyPressed = false;

    auto input = InputSystem::Get();
    const float moveSpeed = input->IsKeyDown(KeyCode::LSHIFT) ? 10.0f * mMoveSpeed : mMoveSpeed;
    const float turnspeed = mTurnSpeed;

    auto& transform = mRigidBodyComponent;
    if (input->IsKeyDown(KeyCode::UP))
    {
        transform->Walk(moveSpeed * deltaTime);
        isAnyKeyPressed = true;
    }
    else if (input->IsKeyDown(KeyCode::DOWN))
    {
        transform->Walk(-moveSpeed * deltaTime);
        isAnyKeyPressed = true;
    }
    else if (input->IsKeyDown(KeyCode::LEFT))
    {
        transform->Strafe(-mMoveSpeed * deltaTime);
        isAnyKeyPressed = true;
    }
    if (input->IsKeyDown(KeyCode::RIGHT))
    {
        transform->Strafe(mMoveSpeed * deltaTime);
        isAnyKeyPressed = true;
    }

    if (input->IsKeyDown(KeyCode::RIGHT) && input->IsKeyPressed(KeyCode::SPACE))
    {
        if (mReadyToDodge)
        {
            isDodging = true;
            transform->Strafe((moveSpeed)*deltaTime);
            mReadyToDodge = false;
        }
        else
        {
            transform->Strafe(moveSpeed * deltaTime);
            isAnyKeyPressed = true;
        }
    }
    else if (input->IsKeyDown(KeyCode::LEFT) && input->IsKeyPressed(KeyCode::SPACE))
    {
        if (mReadyToDodge)
        {
            isDodging = true;
            transform->Strafe((-moveSpeed) * deltaTime);
            mReadyToDodge = false;
        }
        else
        {
            transform->Strafe(-moveSpeed * deltaTime);
            isAnyKeyPressed = true;
        }
    }

    if (input->IsKeyUp(KeyCode::SPACE))
    {
        mReadyToDodge = true;
    }

    if (isDodging)
    {
        mMoveSpeed = 1000;
        mTimeOut -= deltaTime;
    }
    else
    {
        mMoveSpeed = 100.0f;
    }

    if (mTimeOut < 0.0f)
    {
        isDodging = false;
        mTimeOut = 0.2f;
    }


    if (!isAnyKeyPressed && !isDodging)
    {
        transform->SetVelocity(AEMath::Vector3::Zero);
    }
}
