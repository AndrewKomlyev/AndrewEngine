#pragma once
#include <AndrewEngine/Inc/AndrewEngine.h>

struct ParticleInfo
{
    float lifetime;

    AndrewEngine::Color startColour = AndrewEngine::Colors::White;
    AndrewEngine::Color endColour = AndrewEngine::Colors::Blue;
    AndrewEngine::AEMath::Vector3 startPosition = AndrewEngine::AEMath::Vector3::Zero;
    AndrewEngine::AEMath::Vector3 startVelocity = AndrewEngine::AEMath::Vector3::Zero;
    AndrewEngine::AEMath::Vector3 startScale = AndrewEngine::AEMath::Vector3::One;
    AndrewEngine::AEMath::Vector3 endScale = AndrewEngine::AEMath::Vector3::One;
};


class Particle
{
public:
    Particle() = default;
    ~Particle();

    void Initialize(const ParticleInfo& info);
    void Terminate();

    void Activate(const ParticleInfo& info, const AndrewEngine::AEMath::Vector3& pos, const AndrewEngine::AEMath::Vector3& dir, float speed);
    void Update(float deltaTime);
    void Render(AndrewEngine::Graphics::SimpleEffect& effect);
private:

    AndrewEngine::Graphics::MeshPC mMesh;
    AndrewEngine::Graphics::RenderObject mParticle;
    AndrewEngine::Physics::RigidBody mRigidBody;
    AndrewEngine::Physics::CollisionShapeSphere mCollision;

    bool mIsAcive = false;
    ParticleInfo mInfo;
    float mLifeTime = 0.0f;
    float mlifeTimeDuration = 0.0f;
    AndrewEngine::Color mCurrentColour = AndrewEngine::Colors::White;
    AndrewEngine::AEMath::Vector3 mCurrentScale = AndrewEngine::AEMath::Vector3::One;
};