#include "ParticleSystem.h"

using namespace AndrewEngine;
using namespace AndrewEngine::Graphics;
using namespace AndrewEngine::AEMath;

ParticleSystem::ParticleSystem()
    : mLifeTime(0.0f)
    , mNextSpawn(0.0f)
    , mSpawnPosition(Vector3::Zero)
    , mSpawnDirection(Vector3::YAxis)
    , mNextAvailableParticleIndex(0)
{

}

ParticleSystem::~ParticleSystem()
{
}

void ParticleSystem::Initialize(const ParticleSystemInfo& info, const Vector3& spawnPos, const Vector3& spawnDir, float delay)
{
    mNextAvailableParticleIndex = 0;
    mInfo = info;
    mSpawnPosition = spawnPos;
    mSpawnDirection = spawnDir;
    mNextSpawn = delay;
    mLifeTime = info.lifetime;
    mParticles.resize(info.maxParticles);

    for (auto& p : mParticles)
    {
        p.Initialize(info.particleInfo);
    }
}

void ParticleSystem::Terminate()
{
    for (auto& p : mParticles)
    {
        p.Terminate();
    }
}

void ParticleSystem::Update(float deltaTime)
{
    if (mLifeTime > 0.0f)
    {
        mLifeTime -= deltaTime;
        mNextSpawn -= deltaTime;
        if (mNextSpawn <= 0.0f)
        {
            SpawnParticles();
        }
        for (auto& p : mParticles)
        {
            p.Update(deltaTime);
        }
    }
}

void ParticleSystem::Render(SimpleEffect& effect)
{
    if (mLifeTime > 0.0f)
    {
        for (auto& p : mParticles)
        {
            p.Render(effect);
        }
    }
}

void ParticleSystem::DebugUI()
{
    if (ImGui::CollapsingHeader("Particles", ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::ColorEdit4("Start Colour##", &mInfo.particleInfo.startColour.r);
        ImGui::ColorEdit4("End Colour##", &mInfo.particleInfo.endColour.r);

        ImGui::DragFloat3("Start Scale##", &mInfo.particleInfo.startScale.x);
        ImGui::DragFloat3("End Scale##", &mInfo.particleInfo.endScale.x);
    }

    if (ImGui::CollapsingHeader("Particle System##", ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::DragFloat("Min Velocity##", &mInfo.minParticleSpeed);
        ImGui::DragFloat("Max Velocity##", &mInfo.maxParticleSpeed);
                             
        ImGui::DragFloat("Min Angle##", &mInfo.minSpawnAngle);
        ImGui::DragFloat("Max Angle##", &mInfo.maxSpawnAngle);
                             
        ImGui::DragFloat("Min Delay##", &mInfo.minTimeBetweenParticles);
        ImGui::DragFloat("Max Delay##", &mInfo.maxTimeBetweenParticles);
    }
}

void ParticleSystem::SpawnParticles()
{
    int numParticles = mInfo.minParticlePerEmit + (rand() % (mInfo.maxParticlePerEmit - mInfo.minParticlePerEmit));
    for (int i = 0; i < numParticles; ++i)
    {
        SpawnParticle();
    }
    float f = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    mNextSpawn = mInfo.minTimeBetweenParticles + ((mInfo.maxTimeBetweenParticles - mInfo.minTimeBetweenParticles) * f);
}

void ParticleSystem::SpawnParticle()
{
    Particle& p = mParticles[mNextAvailableParticleIndex];
    mNextAvailableParticleIndex = (mNextAvailableParticleIndex + 1) % mParticles.size();

    float f = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    float randomAngle =mInfo.minSpawnAngle +(( mInfo.maxSpawnAngle - mInfo.minSpawnAngle) * f);

    const Vector3 rotationAngle =(Dot(mSpawnDirection, Vector3::YAxis) >= 0.99f)? Normalize(Cross(Vector3::XAxis, mSpawnDirection)): Normalize(Cross(Vector3::YAxis, mSpawnDirection));
    const Matrix4 matRot = Matrix4::RotationAxis(rotationAngle, randomAngle);
    const Vector3 spawnAngle = TransformNormal(mSpawnDirection, matRot);

    f = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    float speed = mInfo.minParticleSpeed + ((mInfo.maxParticleSpeed -mInfo.minParticleSpeed) * f);
    p.Activate(mInfo.particleInfo, mSpawnPosition, spawnAngle, speed);
}
