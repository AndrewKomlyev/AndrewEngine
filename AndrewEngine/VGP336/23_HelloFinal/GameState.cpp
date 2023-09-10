#include "GameState.h"
#include "Input/Inc/InputSystem.h"
#include "AnimationChangeComponent.h"
#include "AnimationChangeInputService.h"

using namespace AndrewEngine::AEMath;
using namespace AndrewEngine::Input;
using namespace AndrewEngine::Physics;

namespace
{
    bool CustomGameMake(const char* componentName, const rapidjson::Value& value, GameObject& gameObject)
    {
        if (strcmp(componentName, "AnimationChangeComponent") == 0)
        {
            AnimationChangeComponent* animationChangeComponent = gameObject.AddComponent<AnimationChangeComponent>();
            return true;
        }
        return false;
    }

    bool CustomServiceMake(const char* serviceName, const rapidjson::Value& value, GameWorld& gameWorld)
    {
        if (strcmp(serviceName, "AnimationChangeInputService") == 0)
        {
            AnimationChangeInputService* animationChangeInputService = gameWorld.AddService<AnimationChangeInputService>();
            return true;
        }
        return false;
    }
}

void GameState::Initialize()
{
    GameObjectFactory::SetCustomMake(CustomGameMake);
    GameWorld::SetCustomServiceMake(CustomServiceMake);
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


void GameState::EditorUI()
{
    mGameWorld.EditorUI();
}