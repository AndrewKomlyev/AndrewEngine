#pragma once
#include <AndrewEngine/Inc/AndrewEngine.h>

using namespace AndrewEngine;
using namespace AndrewEngine::Graphics;


class GameState : public  AndrewEngine::AppState
{
public:
    virtual ~GameState() = default;
    virtual void Initialize() override;
    virtual void Terminate() override;

    virtual void Update(float deltaTime) override;
    virtual void Render() override;
    virtual void DebugUI() override;
protected:
    Camera mCamera;
    DirectionalLight mDirectionalLight;
    Animator mCharacterAnimator;
    RenderObject mGround;
    StandardEffect mStandartEffect;
    RenderGroup mCharacter;
    ModelId mCharacterModelId;
    bool mDrawSkeleton;
};

