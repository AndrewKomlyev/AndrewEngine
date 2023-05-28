#include "Precompiled.h"
#include "App.h"
#include "AppState.h"

using namespace AndrewEngine;
using namespace AndrewEngine::Core;
using namespace AndrewEngine::Graphics;
using namespace AndrewEngine::Input;
using namespace AndrewEngine::Physics;

void App::ChangeState(size_t stateID)
{
    auto iter = mAppStates.find(stateID);
    if (iter != mAppStates.end())
    {
        mNextState = iter->second.get();
    }
}

void App::Run()
{
    ASSERT(false, "NO LONGER USED");
    AppConfig config;
    Run(config);
}

void App::Run(const AppConfig& config)
{
    Window mWindow;

    mWindow.Initialize(GetModuleHandle(nullptr), config.appName, config.winWidth, config.winHeigth);

    auto handle = mWindow.GetWindowHandle();
    InputSystem::StaticInitialize(handle);
    GraphicsSystem::StaticInitilize(handle, false);
    DebugUI::StaticInitialize(handle, false, true);
    SimpleDraw::StaticInitialize(config.debugDrawLimit);
    TextureManager::StaticInitialize("../../Assets/");
    ModelManager::StaticInitialize();
    PhysicsWorld::Settings settings =
    {
        config.gravity,
        config.simulationSteps,
        config.fixedTimeStep
    };

    ASSERT(mCurrentState, "App -- no app state found!");
    mCurrentState->Initialize();

    size_t currentState = 0;

    mRunning = true;
    while (mRunning)
    {
        mWindow.ProcessMessage();

        auto inputSystem = InputSystem::Get();
        inputSystem->Update();
        if (!mWindow.IsActive() || inputSystem->IsKeyPressed(Input::KeyCode::ESCAPE))
        {
            Quit();
            continue;
        }
        if (inputSystem->IsKeyPressed(Input::KeyCode::ENTER))
        {
            currentState = (currentState + 1) % (size_t)mAppStates.size();
            ChangeState(currentState);
        }

        if (mNextState != nullptr)
        {
            mCurrentState->Terminate();
            mCurrentState = std::exchange(mNextState, nullptr);
            mCurrentState->Initialize();
        }

        auto deltaTime = TimeUtil::GetDeltaTime();
        if (deltaTime < 0.5f)
        {
            PhysicsWorld::Get()->Update(deltaTime);
            mCurrentState->Update(deltaTime);
        }
        auto graphicsSystem = GraphicsSystem::Get();
        graphicsSystem->BeginRender();
        mCurrentState->Render();
        DebugUI::BeginRender();
        mCurrentState->DebugUI();
        PhysicsWorld::Get()->DebugUI();
        DebugUI::EndRender();
        graphicsSystem->EndRender();
    }
    mCurrentState->Terminate();

    PhysicsWorld::StaticTerminate();
    ModelManager::StaticTerminate();
    TextureManager::StaticTerminate();
    SimpleDraw::StaticTerminate();
    DebugUI::StaticTerminate();
    GraphicsSystem::StaticTerminate();
    InputSystem::StaticTerminate();
    mWindow.Terminate();
}

void App::Quit()
{
    mRunning = false;
}