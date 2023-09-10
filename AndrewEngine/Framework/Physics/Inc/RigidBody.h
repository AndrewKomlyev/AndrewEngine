#pragma once
#include "Graphics/Inc/Transform.h"

namespace AndrewEngine::Graphics
{
    struct Transform;
}

namespace AndrewEngine::Physics
{
    class CollisionShape;
    using CollisionCallback = std::function<void(void*, void*)>;

    class RigidBody final
    {
    public:
        RigidBody() = default;
        ~RigidBody();

        void Initialize(Graphics::Transform& graphicsTransform, const CollisionShape& shape, float mass = 0.0f);
        void Terminate();

        void SetCollisionFilter(int filter);
        void SetPosition(const AndrewEngine::AEMath::Vector3& position);
        void SetVelocity(const AndrewEngine::AEMath::Vector3& velocity);

        bool IsDynamic() const;

        void OnCollision(void* otherObject);

        void UpdateTransform();
    private:
        friend class PhysicsWorld;
        btRigidBody* GetRigidBody() { return mRigidBody; }

        btRigidBody* mRigidBody = nullptr;
        btDefaultMotionState* mMotionState = nullptr;
        float mMass = 0.0f;
        bool mIsDynamic;
        Graphics::Transform* mGraphicsTransform = nullptr;

    };
}