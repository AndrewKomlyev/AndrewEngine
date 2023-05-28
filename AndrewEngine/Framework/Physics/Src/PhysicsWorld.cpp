#include "Precompiled.h"
#include "PhysicsWorld.h"
#include "PhysicsDebugDrawer.h"

using namespace AndrewEngine;
using namespace AndrewEngine::Physics;

namespace
{
    std::unique_ptr<PhysicsWorld> sPhysicsWorld;
}

void PhysicsWorld::StaticInitalize(const Settings& settings)
{
    ASSERT(sPhysicsWorld == nullptr, "PhysicsWorld is already initialized");
    sPhysicsWorld = std::make_unique<PhysicsWorld>();
    sPhysicsWorld->Initizlize(settings);
}

void PhysicsWorld::StaticTerminate()
{
    if (sPhysicsWorld != nullptr)
    {
        sPhysicsWorld->Terminate();
        sPhysicsWorld.reset();
    }
}

PhysicsWorld* PhysicsWorld::Get()
{
    ASSERT(sPhysicsWorld != nullptr, "PhysicsWorld is not initialized");
    return sPhysicsWorld.get();
}

PhysicsWorld::~PhysicsWorld()
{
    ASSERT(mDynamicWorld == nullptr, "PhysicsWorld: terminaye must be called before deletion");
}

void PhysicsWorld::Initizlize(const Settings& settings)
{
    mSettings = settings;
    mCollisionConfiguration = new btDefaultCollisionConfiguration();
    mDispacher = new btCollisionDispatcher(mCollisionConfiguration);
    mInterface = new btDbvtBroadphase();
    mSolver = new btSequentialImpulseConstraintSolver();
    mDynamicWorld = new btDiscreteDynamicsWorld(mDispacher, mInterface, mSolver, mCollisionConfiguration);
    mDynamicWorld->setGravity(ConvertTobtVector3(settings.gravity));

    mDebugDrawer = new PhysicDebugDrawer();
    mDynamicWorld->setDebugDrawer(mDebugDrawer);
}

void PhysicsWorld::Terminate()
{
    SafeDelete(mDynamicWorld);
    SafeDelete(mSolver);
    SafeDelete(mInterface);
    SafeDelete(mDispacher);
    SafeDelete(mCollisionConfiguration);
}

void PhysicsWorld::Update(float deltaTime)
{
    mDynamicWorld->stepSimulation(deltaTime, mSettings.simulationSteps, mSettings.fixedTimeStep);
}

void PhysicsWorld::DebugUI()
{

}
