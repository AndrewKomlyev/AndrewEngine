#pragma once
#include <AndrewEngine/Inc/Component.h>
#include "TypeIds.h"

namespace AndrewEngine
{
    class RigidBodyComponent;
}


class CharacterControllerComponent final : public AndrewEngine::Component
{

public:
    SET_TYPE_ID(CustomComponentId::CharacterControllerComponentId);

    void Initialize() override;
    void Terminate() override;
    void Update(float deltaTime) override;

    void SetMoveSpeed(float speed) { mMoveSpeed = speed; }
    void SetTurnSpeed(float speed) { mTurnSpeed = speed; }

private:
    AndrewEngine::RigidBodyComponent* mRigidBodyComponent = nullptr;
    float mMoveSpeed = 100.0f;
    float mTurnSpeed = 0.9f;
    float mDodgeDistance = 50.0f;

    float mTimeOut = 0.2f;
    bool mReadyToDodge = true;
    bool isDodging = false;
};
