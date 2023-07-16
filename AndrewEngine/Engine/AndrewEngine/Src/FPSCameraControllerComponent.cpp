#include "Precompiled.h"
#include "FPSCameraControllerComponent.h"

#include "GameObject.h"
#include "CameraComponent.h"

using namespace AndrewEngine;
using namespace AndrewEngine::Input;

void FPSCameraControllerComponent::Initialize()
{
    mCameraComponent = GetOwner().GetComponent<CameraComponent>();
    ASSERT(mCameraComponent != nullptr, "FPSCameraControllerComponent: GameObject does not have Camera Component.");
}

void FPSCameraControllerComponent::Terminate()
{
}

void FPSCameraControllerComponent::Update(float deltaTime)
{

    auto input = InputSystem::Get();
    const float moveSpeed = input->IsKeyDown(KeyCode::LSHIFT) ? 10.0f * mMoveSpeed: mMoveSpeed;
    const float turnspeed = mTurnSpeed;

    auto& camera = mCameraComponent->GetCamera();
    if (input->IsKeyDown(KeyCode::W))
    {
        camera.Walk(moveSpeed * deltaTime);
    }
    else if (input->IsKeyDown(KeyCode::S))
    {
        camera.Walk(-moveSpeed * deltaTime);
    }
    else if (input->IsKeyDown(KeyCode::A))
    {
        camera.Strafe(-moveSpeed * deltaTime);
    }
    if (input->IsKeyDown(KeyCode::D))
    {
        camera.Strafe(moveSpeed * deltaTime);
    }

    if (input->IsKeyDown(KeyCode::E))
    {
        camera.Rise(moveSpeed * deltaTime);
    }
    else if (input->IsKeyDown(KeyCode::Q))
    {
        camera.Rise(-moveSpeed * deltaTime);
    }

    if (input->IsMouseDown(MouseButton::RBUTTON))
    {
        camera.Yaw(input->GetMouseMoveX() * turnspeed * deltaTime);
        camera.Pitch(input->GetMouseMoveY() * turnspeed * deltaTime);
    }
}
