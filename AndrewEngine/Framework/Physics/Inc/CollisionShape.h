#pragma once

namespace AndrewEngine::Physics
{
    class CollisionShape
    {
    public:
        CollisionShape() = default;
        virtual ~CollisionShape();
        virtual void Terminate();
    protected:
        btCollisionShape* mCollisionShape = nullptr;
    private:
        friend class RigidBody;
        btCollisionShape* GetCollisionShape() const { return mCollisionShape; }
    };

    class CollisionShapeSphere : public CollisionShape
    {
    public:
        CollisionShapeSphere() = default;
        void Initialize(float radius);
    };

    class CollisionShapeBox : public CollisionShape
    {
    public:
        CollisionShapeBox() = default;
        void Initialize(const AndrewEngine::AEMath::Vector3& extend);
    };
}