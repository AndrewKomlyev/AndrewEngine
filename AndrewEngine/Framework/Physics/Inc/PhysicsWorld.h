#pragma once

namespace AndrewEngine::Physics
{
    class PhysicDebugDrawer;
    class PhysicsWorld final
    {
    public:
        struct Settings
        {
            AndrewEngine::AEMath::Vector3 gravity{ 0.0f, -9.81f, 0.0f };
            uint32_t simulationSteps = 1;
            float fixedTimeStep = 1.0f / 60.0f;
        };

        static void StaticInitalize(const Settings& settings);
        static void StaticTerminate();
        static PhysicsWorld* Get();

        PhysicsWorld() = default;
        ~PhysicsWorld();

        void Initizlize(const Settings& settings);
        void Terminate();

        void Update(float deltaTime);
        void DebugUI();
    private:
        Settings mSettings;

        btBroadphaseInterface* mInterface = nullptr;
        btCollisionDispatcher* mDispacher = nullptr;
        btDefaultCollisionConfiguration* mCollisionConfiguration = nullptr;
        btDiscreteDynamicsWorld* mDynamicWorld = nullptr;
        btSequentialImpulseConstraintSolver* mSolver = nullptr;
        PhysicsDebugDrawer* mDebugDrawer = nullptr;

        bool mRenderDebugUI = false;
    };
}
