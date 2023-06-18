#include "Precompiled.h"
#include "PhysicsWorld.h"
#include "PhysicsDebugDrawer.h"
#include "RigidBody.h"

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

    mDebugDrawer = new PhysicsDebugDrawer();
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
    for (auto& rb : mRigidBodies)
    {
        rb->UpdateTransform();
    }
}

void PhysicsWorld::DebugUI()
{
    ImGui::Checkbox("RenderPhysics##", &mRenderDebugUI);
    if (mRenderDebugUI)
    {
        int debugMode = mDebugDrawer->getDebugMode();
        bool isEnabled = (debugMode & btIDebugDraw::DBG_DrawWireframe) > 0;
        //if (ImGui::Checkbox("[DBG]DrawWireframe##", &isEnabled))
        //{
        //    debugMode =(isEnabled)?debugMode|btIDebugDraw
        //}
    }
}

void PhysicsWorld::Register(RigidBody* rigidBody)
{
    if (rigidBody != nullptr)
    {
        mRigidBodies.push_back(rigidBody);
        if (rigidBody->GetRigidBody() != nullptr)
        {
            mDynamicWorld->addRigidBody(rigidBody->GetRigidBody());
        }
    }
}

void PhysicsWorld::Unregister(RigidBody* rigidBody)
{
    if (rigidBody != nullptr)
    {
        auto iter = std::find(mRigidBodies.begin(), mRigidBodies.end(), rigidBody);
        if (iter != mRigidBodies.end())
        {
            if (rigidBody->GetRigidBody() != nullptr)
            {
                mDynamicWorld->removeRigidBody(rigidBody->GetRigidBody());
            }
        }
        mRigidBodies.erase(iter);
    }
}