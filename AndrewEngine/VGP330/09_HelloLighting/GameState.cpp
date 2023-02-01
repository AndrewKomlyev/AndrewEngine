#include "GameState.h"
#include "Input/Inc/InputSystem.h"



using namespace AndrewEngine::AEMath;
using namespace AndrewEngine::Input;


void GameState::Initialize() 
{
    mCamera.SetPosition({0.0f, 1.0f, -4.0f});
    mCamera.SetLookAt({0.0f, 0.0f, 0.0f});

    mDirectionalLight.direction = AEMath::Normalize({ 1.0f, -1.0f, 1.0f });
    mDirectionalLight.ambient = { 0.8f, 0.8f, 0.8f, 1.0f };
    mDirectionalLight.diffuse = { 0.7f, 0.7f, 0.7f, 1.0f };
    mDirectionalLight.specular = { 0.7f, 0.7f, 0.7f, 1.0f };

    mSphere = MeshBuilder::CreateSphere(60.0f, 60.0f, 1.0f);

    mEarthObject.meshBuffer.Initialize(mSphere);
    mEarthObject.diffuseMapId = TextureManager::Get()->LoadTexture(L"Textures/earth.jpg");
    mEarthObject.normalMapId = TextureManager::Get()->LoadTexture(L"Textures/earth_normal.jpg");
    mEarthObject.displacementMapId = TextureManager::Get()->LoadTexture(L"Textures/earth_bump.jpg");
    mEarthObject.specularMapId = TextureManager::Get()->LoadTexture(L"Textures/earth_spec.jpg");

    mStandartEffect.Initialize(L"../../Assets/Shaders/Standard.fx");
    mStandartEffect.SetCamera(mCamera);
    mStandartEffect.SetDireectionalLight(mDirectionalLight);
}

void GameState::Terminate()
{
    mStandartEffect.Terminate();
    mEarthObject.Terminate();
}

void GameState::Update(float deltaTime) 
{
    auto input = InputSystem::Get();
    const float moveSpeed = input->IsKeyDown(KeyCode::LSHIFT) ? 10.0f : 1.0f;
    const float turnspeed = 0.01f;

    if (input->IsKeyDown(KeyCode::W))
    {
        mCamera.Walk(moveSpeed * deltaTime);
    }
    else if (input->IsKeyDown(KeyCode::S))
    {
        mCamera.Walk(-moveSpeed * deltaTime);
    }
    else if (input->IsKeyDown(KeyCode::A))
    {
        mCamera.Strafe(-moveSpeed * deltaTime);
    }
    if (input->IsKeyDown(KeyCode::D))
    {
        mCamera.Strafe(moveSpeed * deltaTime);
    }

    if (input->IsKeyDown(KeyCode::E))
    {
        mCamera.Rise(moveSpeed * deltaTime);
    }
    else if (input->IsKeyDown(KeyCode::Q))
    {
        mCamera.Strafe(-moveSpeed * deltaTime);
    }

    if (input->IsMouseDown(MouseButton::RBUTTON))
    {
        mCamera.Yaw(input->GetMouseMoveX() * turnspeed * deltaTime);
        mCamera.Pitch(input->GetMouseMoveY() * turnspeed * deltaTime);
    }
}

void GameState::Render()
{
    mStandartEffect.Begin();
    mStandartEffect.Render(mEarthObject);
    mStandartEffect.End();

    ShowNormals();

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
    ImGui::Separator();
    ImGui::End();
}

void GameState::ShowNormals()
{
    if (mShowNormals)
    {
        for (const auto& v : mSphere.verticies)
        {
            SimpleDraw::AddLine(v.position, v.position + (v.normal * 0.25f), Colors::Pink);
        }
        SimpleDraw::Render(mCamera);
    }
}







