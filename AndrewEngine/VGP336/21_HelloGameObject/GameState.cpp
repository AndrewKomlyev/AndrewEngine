#include "GameState.h"
#include "Input/Inc/InputSystem.h"

using namespace AndrewEngine::AEMath;
using namespace AndrewEngine::Input;

void GameState::Initialize()
{
    CameraComponent* cameraComponent = mCameraGameObject.AddComponent<CameraComponent>();
    cameraComponent->GetCamera().SetPosition({ 0.0f, 1.0f, -4.0f });
    cameraComponent->GetCamera().SetLookAt({ 0.0f, 0.0f, 0.0f });

    FPSCameraControllerComponent* fpsCamera = mCameraGameObject.AddComponent<FPSCameraControllerComponent>();
    fpsCamera->SetMoveSpeed(2.0f);
    fpsCamera->SetTurnSpeed(0.2f);
    mCameraGameObject.Initialize();

    mDirectionalLight.direction = AEMath::Normalize({ 1.0f, -1.0f, 1.0f });
    mDirectionalLight.ambient = { 0.8f, 0.8f, 0.8f, 1.0f };
    mDirectionalLight.diffuse = { 0.7f, 0.7f, 0.7f, 1.0f };
    mDirectionalLight.specular = { 0.7f, 0.7f, 0.7f, 1.0f };

    mStandartEffect.Initialize(L"../../Assets/Shaders/Standard.fx");
    mStandartEffect.SetCamera(cameraComponent->GetCamera());
    mStandartEffect.SetDireectionalLight(mDirectionalLight);
    TransformComponent* transform = mGameObject.AddComponent<TransformComponent>();

    mGameObject.Initialize();
}

void GameState::Terminate()
{
    mCameraGameObject.Terminate();
    mGameObject.Terminate();
    mStandartEffect.Terminate();
}

void GameState::Update(float deltaTime)
{
    mGameObject.Update(deltaTime);
    mCameraGameObject.Update(deltaTime);
}

void GameState::Render()
{
    mStandartEffect.Begin();

    mStandartEffect.End();
}

void GameState::DebugUI()
{
    ImGui::Begin("Debug Control", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    ImGui::Separator();

    if (ImGui::CollapsingHeader("Light", ImGuiTreeNodeFlags_DefaultOpen))
    {
        if (ImGui::DragFloat3("Direction##Light", &mDirectionalLight.direction.x, 0.01f, -1.0f, 1.0f))
        {
            mDirectionalLight.direction = Normalize(mDirectionalLight.direction);
        }
        ImGui::ColorEdit4("Ambient##Light", &mDirectionalLight.ambient.r);
        ImGui::ColorEdit4("Diffuse##Light", &mDirectionalLight.diffuse.r);
        ImGui::ColorEdit4("Specular##Light", &mDirectionalLight.specular.r);
    }

    mGameObject.DebugUI();

    PhysicsWorld::Get()->DebugUI();

    ImGui::Separator();
    ImGui::End();

    CameraComponent* cameraComponent = mCameraGameObject.GetComponent<CameraComponent>();
    SimpleDraw::Render(cameraComponent->GetCamera());
}