#include "GameState.h"
#include "Input/Inc/InputSystem.h"

using namespace AndrewEngine::AEMath;
using namespace AndrewEngine::Input;

void GameState::Initialize()
{
    mGameWorld.LoadLevel("../../Assets/Templates/Levels/test_level.json");
}

void GameState::Terminate()
{
    mGameWorld.Terminate();
}

void GameState::Update(float deltaTime)
{
    mGameWorld.Update(deltaTime);
}

void GameState::Render()
{
    mGameWorld.Render();
}

void GameState::DebugUI()
{
    mGameWorld.DebugUI();
}