#pragma once
#include "Particle.h"

struct ParticleSystemInfo
{
    ParticleInfo particleInfo;
    int minParticlePerEmit = 0;
    int maxParticlePerEmit = 0;
    float minTimeBetweenParticles = 0.0f;
    float maxTimeBetweenParticles = 0.0f;
    float minSpawnAngle = 0.0f;
    float maxSpawnAngle = 0.0f;
    float minParticleSpeed = 0.0f;
    float maxParticleSpeed = 0.0f;
    float lifetime = 0.0f;
    int maxParticles = 100;
};


class ParticleSystem
{
public:
    ParticleSystem();
    ~ParticleSystem();

    void Initialize(const ParticleSystemInfo& info, const AndrewEngine::AEMath::Vector3& spawnPos, const AndrewEngine::AEMath::Vector3& spawnDir, float delay = 0.0f);
    void Terminate();
    void Update(float deltaTime);
    void Render(AndrewEngine::Graphics::SimpleEffect& effect);

    void DebugUI();

private:

    void SpawnParticles();
    void SpawnParticle();

    using Particles = std::vector<Particle>;
    Particles mParticles;

    int mNextAvailableParticleIndex;
    float mLifeTime;
    float mNextSpawn;

    ParticleSystemInfo mInfo;

    AndrewEngine::AEMath::Vector3 mSpawnPosition;
    AndrewEngine::AEMath::Vector3 mSpawnDirection;
};
