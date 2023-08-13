#pragma once

#include "Component.h"

namespace AndrewEngine
{
    class TransformComponent;

    class ColliderComponent final : public Component
    {
    public:
        SET_TYPE_ID(ComponentId::ColliderComponent);

        void Initialize() override;
        void Terminate() override;

        void SetSphereCollision(float radius);
        void SetBoxCollider(const AEMath::Vector3& halfExtend);
        void SetHullCollision(const AEMath::Vector3& halfExtend, const AEMath::Vector3& origin);

    private:
        friend class RigidBodyComponent;
        Physics::CollisionShape* mCollisionShape = nullptr;
    };
}