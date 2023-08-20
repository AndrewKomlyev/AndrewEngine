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
}

void RigidBodyComponent::Terminate()
{
    
}

void RigidBodyComponent::SetMass(float mass)
{
    mMass = mass;
}

void AndrewEngine::RigidBodyComponent::SetPosition(const AEMath::Vector3& position)
{
    mRigidBody.SetPosition(position);
}