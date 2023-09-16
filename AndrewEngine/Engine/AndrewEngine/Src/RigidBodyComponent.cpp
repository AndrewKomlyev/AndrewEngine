#include "Precompiled.h"
#include "RigidBodyComponent.h"

#include "GameObject.h"
#include "ColliderComponent.h"
#include "TransformComponent.h"


using namespace AndrewEngine;

void RigidBodyComponent::Initialize()
{
    TransformComponent* transform = GetOwner().GetComponent<TransformComponent>();
    ColliderComponent* collider = GetOwner().GetComponent<ColliderComponent>();
    mRigidBody.Initialize(*transform, *collider->mCollisionShape, mMass);
    //mRigidBody.GetRigidBody();
}

void RigidBodyComponent::Terminate()
{
    mRigidBody.Terminate();
}

void RigidBodyComponent::SetMass(float mass)
{
    mMass = mass;
}

void AndrewEngine::RigidBodyComponent::SetPosition(const AEMath::Vector3& position)
{
    mRigidBody.SetPosition(position);
}

void RigidBodyComponent::SetVelocity(const AEMath::Vector3& velocity)
{
    mRigidBody.SetVelocity(velocity);

}

void RigidBodyComponent::SetTurnVelocity(const AEMath::Vector3& velocity)
{
    mRigidBody.SetTurnVelocity(velocity);
}

void AndrewEngine::RigidBodyComponent::Walk(float distance)
{
    mRigidBody.Walk(distance);
}

void AndrewEngine::RigidBodyComponent::Strafe(float distance)
{
    mRigidBody.Strafe(distance);
}


