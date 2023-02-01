#include "GameState.h"
#include "Input/Inc/InputSystem.h"
#include <WinUser.h>


void GameState::Initialize() 
{
    AndrewEngine::Graphics::GraphicsSystem::Get()->SetClearColour(AndrewEngine::Colors::Black);
}

void GameState::Update(float deltaTime) 
{
    auto inputSystem = Input::InputSystem::Get();

    if (inputSystem->IsKeyPressed(Input::KeyCode::UP))
    {
        AndrewEngine::Graphics::GraphicsSystem::Get()->SetClearColour(AndrewEngine::Colors::Red);
    }
    else if (inputSystem->IsKeyPressed(Input::KeyCode::DOWN))
    {
        AndrewEngine::Graphics::GraphicsSystem::Get()->SetClearColour(AndrewEngine::Colors::Green);
    }
}