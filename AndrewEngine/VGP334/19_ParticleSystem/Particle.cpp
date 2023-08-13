#include "Particle.h"
using namespace AndrewEngine;
using namespace AndrewEngine::Graphics;

Particle::~Particle()
{
}

void Particle::Initialize(const ParticleInfo& info)
{
    mIsAcive = false;
    mInfo = info;
    mLifeTime = 0.0f;
    mlifeTimeDuration = info.lifetime;

    mMesh = MeshBuilder::CreateSpherePC(10.0f, 10.0f, 0.1f);

    mParticle.meshBuffer.Initialize(nullptr, sizeof(VertexPC), mMesh.vertices.size(), mMesh.indicies.data(), mMesh.indicies.size());

    mCollision.Initialize(0.1f);
    mRigidBody.Initialize(mParticle.transform, mCollision, 0.1f);
    mRigidBody.SetCollisionFilter(0);
}

void Particle::Terminate()
{
    mRigidBody.Terminate();
    mCollision.Terminate();
    mParticle.Terminate();
}

void Particle::Activate(const ParticleInfo& info, const AndrewEngine::AEMath::Vector3& pos, const AndrewEngine::AEMath::Vector3& dir, float speed)
{
    mInfo = info;
    mLifeTime = 0.0f;
    mlifeTimeDuration = mInfo.lifetime;
    mIsAcive = true;
    mRigidBody.SetPosition(pos);
    mRigidBody.SetVelocity(dir * speed);
}

void Particle::Update(float deltaTime)
{
    if (mIsAcive)
    {
        mLifeTime += deltaTime;
        float t = AEMath::Clamp(mLifeTime / mlifeTimeDuration, 0.0f, 0.1f);
        mCurrentColour = AEMath::Lerp(mInfo.startColour, mInfo.endColour, t);
        mCurrentScale = AEMath::Lerp(mInfo.startScale, mInfo.endScale, t);

        mIsAcive = mLifeTime < mlifeTimeDuration;
    }
    else
    {
        mRigidBody.SetVelocity(Vector3::Zero);
    }
}

void Particle::Render(SimpleEffect& effect)
{
    if (mIsAcive)
    {
        for (auto& v : mMesh.vertices)
        {
            v.color = mCurrentColour;
        }
        mParticle.transform.scale = mCurrentScale;
        mParticle.meshBuffer.Update(mMesh.vertices.data(), mMesh.vertices.size());
        effect.Render(mParticle);
    }
}
