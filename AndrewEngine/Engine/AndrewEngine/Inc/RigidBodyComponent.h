#pragma once


#include "Component.h"

namespace AndrewEngine
{
    class RigidBodyComponent final : public Component
    {
    public:
        SET_TYPE_ID(ComponentId::RigidBodyComponent);

        void Initialize() override;
        void Terminate() override;

        void SetMass(float mass);
        void SetPosition(const AEMath::Vector3& position);
    private:

        Physics::RigidBody mRigidBody;
        float mMass = 0.0f;
    };
}