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
    void ShowNormals();
  
    Camera mCamera;
    DirectionalLight mDirectionalLight;

    float mYaw, mPitch, mRoll;
    RenderObject mSphere;
    RenderObject mGround;
    StandardEffect mStandartEffect;

    float mYawTurnspeed = 0.01f;
    float mPitchTurnspeed = 0.01f;
    float mRollTurnspeed = 0.01f;
    float scale[5] = {0.05, 0.1, 0.25, 0.5, 1};
    int scaleIndex = 0;
};

