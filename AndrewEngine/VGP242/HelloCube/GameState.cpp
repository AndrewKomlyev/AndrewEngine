#include "GameState.h"
#include "Input/Inc/InputSystem.h"
#include <WinUser.h>

using namespace AndrewEngine::AEMath;

void GameState::OnCreateShape() 
{
    /*mVerticies.push_back({ AEMath::Vector3(0.0f, 0.5f, 0.0f), Colors::Yellow });
    mVerticies.push_back({ AEMath::Vector3(0.5f, -0.5f, 0.0f), Colors::Yellow });
    mVerticies.push_back({ AEMath::Vector3(-0.5f, -0.5f, 0.0f), Colors::Yellow });*/

    mVerticies.push_back({ AEMath::Vector3(-0.5f,-0.5f,-0.5f), Colors::Yellow });
    mVerticies.push_back({ AEMath::Vector3(-0.5f,-0.5f, 0.5f), Colors::Red });
    mVerticies.push_back({ AEMath::Vector3(-0.5f, 0.5f, 0.5f), Colors::Green });
    mVerticies.push_back({ AEMath::Vector3(0.5f, 0.5f, -0.5f), Colors::Yellow });
    mVerticies.push_back({ AEMath::Vector3(-0.5f, -0.5f, -0.5f), Colors::Red });
    mVerticies.push_back({ AEMath::Vector3(-0.5f, 0.5f, -0.5f), Colors::Green });
    mVerticies.push_back({ AEMath::Vector3(0.5f, -0.5f, 0.5f), Colors::Yellow });
    mVerticies.push_back({ AEMath::Vector3(-0.5f, -0.5f, -0.5f), Colors::Red });
    mVerticies.push_back({ AEMath::Vector3(0.5f, -0.5f, -0.5f), Colors::Green });
    mVerticies.push_back({ AEMath::Vector3(0.5f, 0.5f, -0.5f), Colors::Yellow });
    mVerticies.push_back({ AEMath::Vector3(0.5f, -0.5f, -0.5f), Colors::Red });
    mVerticies.push_back({ AEMath::Vector3(-0.5f, -0.5f, -0.5f), Colors::Green });
    mVerticies.push_back({ AEMath::Vector3(-0.5f, -0.5f, -0.5f), Colors::Yellow });
    mVerticies.push_back({ AEMath::Vector3(-0.5f, 0.5f, 0.5f), Colors::Red });
    mVerticies.push_back({ AEMath::Vector3(-0.5f, 0.5f, -0.5f), Colors::Green });
    mVerticies.push_back({ AEMath::Vector3(0.5f, -0.5f, 0.5f), Colors::Yellow });
    mVerticies.push_back({ AEMath::Vector3(-0.5f, -0.5f, 0.5f), Colors::Red });
    mVerticies.push_back({ AEMath::Vector3(-0.5f, -0.5f, -0.5f), Colors::Green });
    mVerticies.push_back({ AEMath::Vector3(-0.5f, 0.5f, 0.5f), Colors::Yellow });
    mVerticies.push_back({ AEMath::Vector3(-0.5f, -0.5f, 0.5f), Colors::Red });
    mVerticies.push_back({ AEMath::Vector3(0.5f, -0.5f, 0.5f), Colors::Green });
    mVerticies.push_back({ AEMath::Vector3(0.5f, 0.5f, 0.5f), Colors::Yellow });
    mVerticies.push_back({ AEMath::Vector3(0.5f, -0.5f, -0.5f), Colors::Red });
    mVerticies.push_back({ AEMath::Vector3(0.5f, 0.5f, -0.5f), Colors::Green });
    mVerticies.push_back({ AEMath::Vector3(0.5f, -0.5f, -0.5f), Colors::Yellow });
    mVerticies.push_back({ AEMath::Vector3(0.5f, 0.5f, 0.5f), Colors::Red });
    mVerticies.push_back({ AEMath::Vector3(0.5f, -0.5f, 0.5f), Colors::Green });
    mVerticies.push_back({ AEMath::Vector3(0.5f, 0.5f, 0.5f), Colors::Yellow });
    mVerticies.push_back({ AEMath::Vector3(0.5f, 0.5f, -0.5f), Colors::Red });
    mVerticies.push_back({ AEMath::Vector3(-0.5f, 0.5f, -0.5f), Colors::Green });
    mVerticies.push_back({ AEMath::Vector3(0.5f, 0.5f, 0.5f), Colors::Green });
    mVerticies.push_back({ AEMath::Vector3(-0.5f, 0.5f, -0.5f), Colors::Yellow });
    mVerticies.push_back({ AEMath::Vector3(-0.5f, 0.5f, 0.5f), Colors::Red });
    mVerticies.push_back({ AEMath::Vector3(0.5f, 0.5f, 0.5f), Colors::Green });
    mVerticies.push_back({ AEMath::Vector3(-0.5f, 0.5f, 0.5f), Colors::Yellow });
    mVerticies.push_back({ AEMath::Vector3(0.5f, -0.5f, 0.5f), Colors::Red });
}


void GameState::Initialize() 
{
    mCamera.SetPosition({0.0f, 1.0f, -1.0f});
    mCamera.SetLookAt({0.0f, 0.0f, 0.0f});

    OnCreateShape();

    mConstantBuffer.Initialize(sizeof(Matrix4));
    mMeshBuffer.Initialize(mVerticies.data(), sizeof(Vertex), mVerticies.size());
    mVertexShader.Initialize(L"../../Assets/Shaders/DoTransform.fx", VE_Position | VE_Color);
    mPixelShader.Initialize(L"../../Assets/Shaders/DoTransform.fx");
    
}

void GameState::Terminate()
{
    mConstantBuffer.Terminate();
    mMeshBuffer.Terminate();
    mVertexShader.Terminate();
    mPixelShader.Terminate();;
}
float rotationX = 0.0f;
float rotationY = 0.0f;
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
    //float dt = AndrewEngine::Core::TimeUtil::GetDeltaTime();
    /*rotation += (0.001f);*/

    Matrix4 cuberWorldRotX = Matrix4::RotationX(rotationX);
    Matrix4 cuberWorldRotY = Matrix4::RotationY(rotationY);
    Matrix4 view = mCamera.GetViewMatrix();
    Matrix4 proj = mCamera.GetProjectionMatrix();
    Matrix4 wvp = Transpose(cuberWorldRotX* cuberWorldRotY * view * proj);
    mConstantBuffer.Update(&wvp);
    mConstantBuffer.BindVS(0);
    mMeshBuffer.Render();


}

void GameState::DebugUI()
{
     
}

