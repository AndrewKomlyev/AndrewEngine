#include "GameState.h"
#include "Input/Inc/InputSystem.h"

using namespace AndrewEngine::AEMath;
using namespace AndrewEngine::Input;

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
    mGround.diffuseMapId = TextureManager::Get()->LoadTexture(L"Textures/Grain1.png");
    mGround.material.ambient = { 0.8f, 0.8f, 0.8f, 1.0f };
    mGround.material.diffuse = { 0.8f, 0.8f, 0.8f, 1.0f };
    mGround.material.specular = { 0.8f, 0.8f, 0.8f, 1.0f };
    mGround.material.power = 10.0f;

    Mesh sphere = MeshBuilder::CreateSphere(20, 20, 1.0f);
    mSphere.meshBuffer.Initialize(sphere);
    mSphere.diffuseMapId = TextureManager::Get()->LoadTexture(L"Textures/earth.jpg");
    mSphere.material.ambient = { 0.8f, 0.8f, 0.8f, 1.0f };
    mSphere.material.diffuse = { 0.8f, 0.8f, 0.8f, 1.0f };
    mSphere.material.specular = { 0.8f, 0.8f, 0.8f, 1.0f };
    mSphere.material.power = 20.0f;
    mSphere.transform.position.y = 1.0f;

    mStandartEffect.Initialize(L"../../Assets/Shaders/Standard.fx");
    mStandartEffect.SetCamera(mCamera);
    mStandartEffect.SetDireectionalLight(mDirectionalLight);

    mAnimationTime = 0.0f;
    mBallAnimation = AnimationBuilder()
        .AddPositionKey(Vector3(0.0f, 1.0f, 0.0f), 1.0f, EaseType::EaseInOut)
        //.AddRotationKey(Quaternion(0.0f, 1.0f, 2.0f, 3.0f), 1.0f, EaseType::EaseInQuad)
        //.AddScaleKey(Vector3(1.0f, 2.0f, 1.0f), 1.0f, EaseType::EaseInQuad)

        .AddPositionKey(Vector3(0.0f, 3.0f, 2.0f), 2.0f, EaseType::EaseInOut)
        //.AddScaleKey(Vector3(2.0f, 2.0f, 1.0f), 2.0f, EaseType::EaseInQuad)

        .AddPositionKey(Vector3(0.0f, 1.0f, 2.0f), 3.0f, EaseType::EaseInOut)
        //.AddScaleKey(Vector3(2.0f, 2.0f, 2.0f), 3.0f, EaseType::EaseInQuad)

        .AddPositionKey(Vector3(0.0f, 1.0f, 0.0f), 4.0f, EaseType::EaseInOut)
        .Build();
}

void GameState::Terminate()
{
    mStandartEffect.Terminate();
    mSphere.Terminate();
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

    mAnimationTime += deltaTime;
    const float animDuration = mBallAnimation.GetDuration();
    while (mAnimationTime > animDuration)
    {
        mAnimationTime -= animDuration;
    }
    mSphere.transform = mBallAnimation.GetTransform(mAnimationTime);
}

void GameState::Render()
{

    mStandartEffect.Begin();
    mStandartEffect.Render(mGround);
    mStandartEffect.Render(mSphere);
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

    ImGui::Separator();
    ImGui::End();
}

void GameState::ShowNormals()
{
}