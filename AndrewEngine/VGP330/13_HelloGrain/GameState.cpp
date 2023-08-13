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

    Mesh ground = MeshBuilder::CreatePlane(20, 20, 1.0f);
    mGround.meshBuffer.Initialize(ground);
    mGround.diffuseMapId = TextureManager::Get()->LoadTexture(L"Textures/earth.jpg");
    mGround.material.ambient = { 0.8f, 0.8f, 0.8f, 1.0f };
    mGround.material.diffuse = { 0.8f, 0.8f, 0.8f, 1.0f };
    mGround.material.specular = { 0.8f, 0.8f, 0.8f, 1.0f };
    mGround.material.power =  10.0f;
    mGround.transform.position = { 0.0f, -1.0f, 0.0f };

    Model character;
    ModelIO::LoadModel("../../Assets/Models/Vanguard/VanguardByTChoonyung.model", character);
    ModelIO::LoadMaterial("../../Assets/Models/Vanguard/VanguardByTChoonyung.model", character);
    mCharacter = CreateRenderGroup(character);

    mScreenQuad.meshBuffer.Initialize(MeshBuilder::CreateScreenQuad());

    mStandartEffect.Initialize(L"../../Assets/Shaders/Standard.fx");
    mStandartEffect.SetCamera(mCamera);
    mStandartEffect.SetDireectionalLight(mDirectionalLight);

    mGrainEffect.Initialize(L"../../Assets/Shaders/GrainShader.fx");
    mGrainEffect.SetTexture(&mRenderTarget);
   


    mShadowEffect.Initialize();
    mShadowEffect.SetDirectionalLight(mDirectionalLight);

    auto gs = GraphicsSystem::Get();
    const auto screenWidth = gs->GetBackBufferWidth();
    const auto screenHeight = gs->GetBackBufferHeight();
    mRenderTarget.Initialize(screenWidth, screenHeight, RenderTarget::Format::RGBA_U8);
}

void GameState::Terminate()
{
    mRenderTarget.Terminate();
    mShadowEffect.Terminate();
    mGrainEffect.Terminate();
    mStandartEffect.Terminate();
    mGround.Terminate();
    mScreenQuad.Terminate();
    CleanupRenderGroup(mCharacter);
}

void GameState::Update(float deltaTime) 
{
    //movement
    mGrainEffect.Update(deltaTime);


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
    //mShadowEffect.Begin();
    //Graphics::DrawRenderGroup(mShadowEffect, mCharacter);
    //mShadowEffect.End();

    mRenderTarget.BeginRender();
    {
        mStandartEffect.Begin();
        Graphics::DrawRenderGroup(mStandartEffect, mCharacter);
        mStandartEffect.Render(mGround);
        mStandartEffect.End();
    }

    mRenderTarget.EndRender();

    mGrainEffect.Begin();
    mGrainEffect.Render(mScreenQuad);
    mGrainEffect.End();

    //ShowNormals();
}

void GameState::DebugUI()
{
    //mGrainEffect.DebugUI();

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
        for (const auto& v : mSphere.vertices)
        {
            SimpleDraw::AddLine(v.position, v.position + (v.normal * 0.25f), Colors::Pink);
        }
        SimpleDraw::Render(mCamera);
    }
}







