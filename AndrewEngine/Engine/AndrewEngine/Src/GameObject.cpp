#include "Precompiled.h"
#include "GameObject.h"

using namespace AndrewEngine;

void GameObject::Initialize()
{
    ASSERT(!mInitialized, "GameObject: is already intialized!");
    mInitialized = true;
    for (auto& component : mComponents)
    {
        component->Initialize();
    }
}

void GameObject::Terminate()
{
    for (auto& component : mComponents)
    {
        component->Terminate();
    }
}

void GameObject::Update(float deltaTime)
{
    for (auto& component : mComponents)
    {
        component->Update(deltaTime);
    }
}

void GameObject::DebugUI()
{
    for (auto& component : mComponents)
    {
        component->DebugUI();
    }
}
