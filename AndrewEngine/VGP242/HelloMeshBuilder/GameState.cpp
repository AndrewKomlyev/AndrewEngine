#include "GameState.h"
#include "Input/Inc/InputSystem.h"



using namespace AndrewEngine::AEMath;
float rotationX = 0.0f;
float rotationY = 0.0f;


void GameState::OnCreateMesh()
{
    mCube = MeshBuilder::CreateCubePC(2.0f, Colors::AliceBlue);
}


void GameState::Initialize() 
{
    mCamera.SetPosition({0.0f, 1.0f, -4.0f});
    mCamera.SetLookAt({0.0f, 0.0f, 0.0f});

    //OnCreateMesh();
    //mCube = MeshBuilder::CreateRectanglePC(2.0f, 1.0f, 2.0f);
    //mCube = MeshBuilder::CreatePlanePC(4.0f, 2.0f, 1.0f);
    //mCube = MeshBuilder::CreateCylinderPC(5.0f, 3.0f);
    mCube = MeshBuilder::CreateSpherePC(10.0f, 10.0f, 1.0f);

    mConstantBuffer.Initialize(sizeof(Matrix4));
    mMeshBuffer.Initialize(mCube);
    mVertexShader.Initialize(L"../../Assets/Shaders/DoTransform.fx", VE_Position | VE_Color);
    mPixelShader.Initialize(L"../../Assets/Shaders/DoTransform.fx");
    
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
    mMeshBuffer.Render();


}

void GameState::DebugUI()
{

}







