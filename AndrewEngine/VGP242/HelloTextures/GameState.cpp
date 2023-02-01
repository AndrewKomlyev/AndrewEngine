#include "GameState.h"
#include "Input/Inc/InputSystem.h"



using namespace AndrewEngine::AEMath;
float rotationX = 0.0f;
float rotationY = 0.0f;

void GameState::Initialize() 
{
    mCamera.SetPosition({0.0f, 1.0f, -4.0f});
    mCamera.SetLookAt({0.0f, 0.0f, 0.0f});


    mSphere = MeshBuilder::CreateSpherePX(10.0f, 10.0f, 1.0f);

    mConstantBuffer.Initialize(sizeof(Matrix4));
    mMeshBuffer.Initialize(mSphere);
    mEarthTexture = TextureManager::Get()->LoadTexture(L"Textures/earth.jpg");
    mVertexShader.Initialize(L"../../Assets/Shaders/DoTexturing.fx", VE_Position | VE_TexCoord);
    mPixelShader.Initialize(L"../../Assets/Shaders/DoTexturing.fx");
    
}

void GameState::Terminate()
{
    mConstantBuffer.Terminate();
    mMeshBuffer.Terminate();
    mVertexShader.Terminate();
    mPixelShader.Terminate();
}

void GameState::Update(float deltaTime) 
{
    if (Input::InputSystem::Get()->IsKeyDown(Input::KeyCode::UP))
    {
        rotationY += Constants::HalfPi * 1 / 60;
    }
    else if (Input::InputSystem::Get()->IsKeyDown(Input::KeyCode::DOWN))
    {
        rotationY -= Constants::HalfPi * 1 / 60;
    }
    else if (Input::InputSystem::Get()->IsKeyDown(Input::KeyCode::LEFT))
    {
        rotationX -= Constants::HalfPi * 1 / 60;
    }
    else if (Input::InputSystem::Get()->IsKeyDown(Input::KeyCode::RIGHT))
    {
        rotationX += Constants::HalfPi * 1 / 60;
    }
}

void GameState::Render()
{
    auto context = GraphicsSystem::Get()->GetContext();

    mVertexShader.Bind();
    mPixelShader.Bind();

    Matrix4 cuberWorldRotX = Matrix4::RotationX(rotationX);
    Matrix4 cuberWorldRotY = Matrix4::RotationY(rotationY);
    Matrix4 view = mCamera.GetViewMatrix();
    Matrix4 proj = mCamera.GetProjectionMatrix();
    Matrix4 wvp = Transpose(cuberWorldRotX* cuberWorldRotY * view * proj);
    mConstantBuffer.Update(&wvp);
    mConstantBuffer.BindVS(0);
    TextureManager::Get()->BindVS(mEarthTexture, 0);
    TextureManager::Get()->BindPS(mEarthTexture, 0);
    mMeshBuffer.Render();


}

void GameState::DebugUI()
{

}







