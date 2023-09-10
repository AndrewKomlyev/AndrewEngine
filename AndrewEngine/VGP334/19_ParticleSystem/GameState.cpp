#include "GameState.h"
#include "AndrewEngine/Inc/AndrewEngine.h"

using namespace AndrewEngine::AEMath;
using namespace AndrewEngine::Input;

ParticleSystemInfo info;
void GameState::Initialize()
{
    mCamera.SetPosition({ 0.0f, 1.0f, -4.0f });
    mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });

    mDirectionalLight.direction = AEMath::Normalize({ 1.0f, -1.0f, 1.0f });
    mDirectionalLight.ambient = { 0.8f, 0.8f, 0.8f, 1.0f };
    mDirectionalLight.diffuse = { 0.7f, 0.7f, 0.7f, 1.0f };
    mDirectionalLight.specular = { 0.7f, 0.7f, 0.7f, 1.0f };

    Mesh ground = MeshBuilder::CreatePlane(20, 20, 1.0f);
    mGround.meshBuffer.Initialize(ground);
    mGround.diffuseMapId = TextureManager::Get()->LoadTexture(L"Textures/space.jpg");
    mGround.material.ambient = { 0.8f, 0.8f, 0.8f, 1.0f };
    mGround.material.diffuse = { 0.8f, 0.8f, 0.8f, 1.0f };
    mGround.material.specular = { 0.8f, 0.8f, 0.8f, 1.0f };
    mGround.material.power = 10.0f;

    mBoxCollisionShape.Initialize({ 10.0f, 0.01f, 10.0f });
    mGroundRigidBody.Initialize(mGround.transform, mBoxCollisionShape, 0.0f);

    mStandartEffect.Initialize(L"../../Assets/Shaders/Standard.fx");
    mStandartEffect.SetCamera(mCamera);
    mStandartEffect.SetDireectionalLight(mDirectionalLight);

    mParticleEffect.Initialize();
    mParticleEffect.SetCamera(mCamera);

    info.lifetime = 999999.0f;
    info.maxParticles = 50;
    info.minParticleSpeed = 5.0f;
    info.maxParticleSpeed = 15.0f;
    info.minParticlePerEmit = 1;
    info.maxParticlePerEmit = 5;
    info.minSpawnAngle = AEMath::Constants::HalfPi * -0.5f;
    info.maxSpawnAngle = AEMath::Constants::HalfPi * 0.5f;
    info.minTimeBetweenParticles = 0.001f;
    info.maxTimeBetweenParticles = 0.02f;

    info.particleInfo.lifetime = 2.0f;
    info.particleInfo.startScale = { 1.0f,1.0f,1.0f };
    info.particleInfo.endScale = { 0.2f,0.2f,0.2f };
    info.particleInfo.startColour = Colors::BlueViolet;
    info.particleInfo.endColour = Colors::Gold;
    mParticleSystem.Initialize(info, Vector3::Zero, Vector3::YAxis);
}

void GameState::Terminate()
{
    mParticleSystem.Terminate();
    mParticleEffect.Terminate();
    mGroundRigidBody.Terminate();
    mBoxCollisionShape.Terminate();
    mGround.Terminate();
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
        mCamera.Rise(-moveSpeed * deltaTime);
    }

    if (input->IsMouseDown(MouseButton::RBUTTON))
    {
        mCamera.Yaw(input->GetMouseMoveX() * turnspeed * deltaTime);
        mCamera.Pitch(input->GetMouseMoveY() * turnspeed * deltaTime);
    }

    mParticleSystem.Update(deltaTime);
}

void GameState::Render()
{
    mStandartEffect.Begin();
    mStandartEffect.Render(mGround);
    mStandartEffect.End();

    mParticleEffect.Begin();
    mParticleSystem.Render(mParticleEffect);
    mParticleEffect.End();

    SimpleDraw::AddGroundPlane(20.0f, Colors::White);
    SimpleDraw::Render(mCamera);
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

    mParticleSystem.DebugUI();

    PhysicsWorld::Get()->DebugUI();

    ImGui::Separator();
    ImGui::End();
}