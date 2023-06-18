#include "Precompiled.h"
#include "CollisionShape.h"
using namespace AndrewEngine;
using namespace AndrewEngine::Physics;

CollisionShape::~CollisionShape()
{
    ASSERT(mCollisionShape == nullptr, "CollisionShape: terminate must be called first");
}

void CollisionShape::Terminate()
{
    SafeDelete(mCollisionShape);
}

void CollisionShapeSphere::Initialize(float radius)
{
    ASSERT(mCollisionShape == nullptr, "CollisionShapeSphere: collision shape not initialized");
    mCollisionShape = new btSphereShape(radius);
}

void CollisionShapeBox::Initialize(const AndrewEngine::AEMath::Vector3& halfExtend)
{
    ASSERT(mCollisionShape == nullptr, "CollisionShapeBox: collision shape not initialized");
    mCollisionShape = new btBoxShape(ConvertTobtVector3(halfExtend));
}