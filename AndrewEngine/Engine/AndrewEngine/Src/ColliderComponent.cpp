#include "Precompiled.h"
#include "ColliderComponent.h"

using namespace AndrewEngine;
using namespace AndrewEngine::Physics;

void ColliderComponent::Initialize()
{
    ASSERT(mCollisionShape != nullptr, "CollisionShape: shape was not set");

}

void ColliderComponent::Terminate()
{
    mCollisionShape->Terminate();
    delete mCollisionShape;
}

void ColliderComponent::SetSphereCollision(float radius)
{
    ASSERT(mCollisionShape == nullptr, "ColliderComponent: is Already set");
    CollisionShapeSphere* sphere= new CollisionShapeSphere();
    sphere->Initialize(radius);
    mCollisionShape = sphere;

}

void ColliderComponent::SetBoxCollider(const AEMath::Vector3& halfExtend)
{
    ASSERT(mCollisionShape == nullptr, "ColliderComponent: is Already set");
    CollisionShapeBox* box = new CollisionShapeBox();
    box->Initialize(halfExtend);
    mCollisionShape = box;
}

void ColliderComponent::SetHullCollision(const AEMath::Vector3& halfExtend, const AEMath::Vector3& origin)
{
    ASSERT(mCollisionShape == nullptr, "ColliderComponent: is Already set");
    CollisionShapeHull* hull = new CollisionShapeHull();
    hull->Initialize(halfExtend, origin);
    mCollisionShape = hull;
}
