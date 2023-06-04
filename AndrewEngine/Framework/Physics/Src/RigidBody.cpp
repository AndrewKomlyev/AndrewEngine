#include "Precompiled.h"
#include "RigidBody.h"
#include "CollisionShape.h"
#include "PhysicsWorld.h"

#include "Graphics/Inc/Transform.h"
using namespace AndrewEngine;
using namespace AndrewEngine::Physics;

RigidBody::~RigidBody()
{
    ASSERT(mRigidBody == nullptr && mMotionState == nullptr, "RigidBody: terminate must be called first");
}

void RigidBody::Initialize(Graphics::Transform& graphicsTransform, const CollisionShape& shape, float mass)
{
    mGraphicsTransform = &graphicsTransform;
    mMass = mass;

    mMotionState = new btDefaultMotionState(ConvertTobtTransform(graphicsTransform));
    mRigidBody = new btRigidBody(mMass, mMotionState, shape.GetCollisionShape());

    PhysicsWorld::Get()->Register(this);
}

void RigidBody::Terminate()
{
    SafeDelete(mMotionState);
    SafeDelete(mRigidBody);
}

void RigidBody::SetCollisionFilter(int filter)
{
    mRigidBody->setCollisionFlags(filter);
}

void RigidBody::SetPosition(const AndrewEngine::AEMath::Vector3& position)
{
    mGraphicsTransform->position = position;
    mRigidBody->setWorldTransform(ConvertTobtTransform(*mGraphicsTransform));
}

void RigidBody::SetVelocity(const AndrewEngine::AEMath::Vector3& velocity)
{
    mRigidBody->setLinearVelocity(ConvertTobtVector3(velocity));
}

bool RigidBody::IsDynamic() const
{
    return mMass > 0.0f;
}

void RigidBody::UpdateTransform()
{
    ApplybtTransformToTransform(mRigidBody->getWorldTransform(), *mGraphicsTransform);
}
