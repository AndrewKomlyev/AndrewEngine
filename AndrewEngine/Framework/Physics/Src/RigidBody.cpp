#include "Precompiled.h"
#include "RigidBody.h"
#include "CollisionShape.h"
#include "PhysicsWorld.h"

#include "Graphics/Inc/Transform.h"
using namespace AndrewEngine;
using namespace AndrewEngine::Physics;

void CollisionTest(void* dataA, void* dataB)
{

}

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
    mRigidBody->setUserPointer(CollisionTest);
    
    PhysicsWorld::Get()->Register(this);
}

void RigidBody::Terminate()
{
    PhysicsWorld::Get()->Unregister(this);
    SafeDelete(mRigidBody);
    SafeDelete(mMotionState);
}

void RigidBody::SetCollisionFilter(int filter)
{
    mRigidBody->setCollisionFlags(btCollisionObject::CF_NO_CONTACT_RESPONSE);
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

void RigidBody::SetTurnVelocity(const AndrewEngine::AEMath::Vector3& turnVelocity)
{
    mRigidBody->setTurnVelocity(ConvertTobtVector3(turnVelocity));
}

void RigidBody::Walk(float distance)
{
    mRigidBody->activate(true);
    auto& m = mRigidBody->getWorldTransform().getBasis();
    auto& forward = m.getRow(2);
    //AEMath::Vector3 forward = ConvertToVector3(m.getRow(1));
    mRigidBody->setLinearVelocity(forward * distance);
}

void RigidBody::Strafe(float distance)
{
    mRigidBody->activate(true);
    auto& m = mRigidBody->getWorldTransform().getBasis();
    auto& forward = m.getRow(0);
    //AEMath::Vector3 forward = ConvertToVector3(m.getRow(1));
    mRigidBody->setLinearVelocity(forward * distance);
}


bool RigidBody::IsDynamic() const
{
    return mMass > 0.0f;
}

void RigidBody::OnCollision(void* otherObject)
{
    //mRigidBody->setTurnVelocity

}

void RigidBody::UpdateTransform()
{
    ApplybtTransformToTransform(mRigidBody->getWorldTransform(), *mGraphicsTransform);
}
