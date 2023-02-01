#pragma once

#include <AndrewEngine/Inc/AndrewEngine.h>

using namespace AndrewEngine;
using namespace AndrewEngine::Graphics;


class GameState : public  AndrewEngine::AppState
{
public:
    virtual ~GameState() = default;
    virtual void Initialize() override;

    virtual void Update(float deltaTime) override;
};