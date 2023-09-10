#pragma once

#include "Component.h"

namespace AndrewEngine
{
    class CameraComponent;

    class FPSCameraControllerComponent final : public Component
    {
    public:
        SET_TYPE_ID(ComponentId::FPSCameraControllerComponent);


        void Initialize() override;
        void Terminate() override;
        void Update(float deltaTime) override;

        void SetMoveSpeed(float speed) { mMoveSpeed = speed; }
        void SetTurnSpeed(float speed) { mTurnSpeed = speed; }

    private:
        CameraComponent* mCameraComponent = nullptr;
        float mMoveSpeed = 5.0f;
        float mTurnSpeed = 0.9f;
    };
}
