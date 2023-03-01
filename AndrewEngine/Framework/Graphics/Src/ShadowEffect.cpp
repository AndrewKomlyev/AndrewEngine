#include "Precompiled.h"
#include "ShadowEffect.h"

#include "Camera.h"
#include "RenderObject.h"
#include "VertexTypes.h"

using namespace AndrewEngine;
using namespace AndrewEngine::Graphics;

void ShadowEffect::Initialize()
{
    mLightCamera.SetMode(Camera::ProjectionMode::Orthographic);

    std::filesystem::path shaderFile =L"../../Assets/Shaders/Shadow.fx";
    mVertexShader.Initialize<Vertex>(shaderFile);
    mPixelShader.Initialize(shaderFile);

    mTransformBuffer.Initialize();

    constexpr uint32_t depthMapResolution = 4096;
    mDepthRenderTarget.Initialize(depthMapResolution, depthMapResolution, Texture::Format::RGBA_U32);
}

void ShadowEffect::Terminate()
{
    mDepthRenderTarget.Terminate();

    mTransformBuffer.Terminate();
    mPixelShader.Terminate();
    mVertexShader.Terminate();
}

void ShadowEffect::Begin()
{
    UpdateLightCamera();

    mVertexShader.Bind();
    mPixelShader.Bind();
    mTransformBuffer.BindVS(0);
}

void ShadowEffect::End()
{
    mDepthRenderTarget.EndRender();
}

void ShadowEffect::Render(const RenderObject& renderObject)
{
    const auto& matWorld = renderObject.transform.GetMatrix4();
    const auto& matView = mLightCamera.GetViewMatrix();
    const auto& matProj = mLightCamera.GetProjectionMatrix();

    TransformData transformData;
    transformData.wvp = Transpose(matWorld * matView * matProj);
    mTransformBuffer.Update(transformData);

    renderObject.meshBuffer.Render();
}

void ShadowEffect::SetDirectionalLight(const DirectionalLight& directionalLight)
{
    mDirectionalLight = &directionalLight;
}

void ShadowEffect::DebugUI()
{
    if (ImGui::CollapsingHeader("Shadow Effect", ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::Text("Depth Map");
        ImGui::Image(mDepthRenderTarget.GetRawData(), { 144,144 }, { 0,0 }, { 1,1 }, { 1,1,1,1 }, { 1,1,1,1 });

        ImGui::DragFloat("size", &mSize, 1.0f, 1.0f, 1000.0f);
    }
}

void ShadowEffect::UpdateLightCamera()
{
    ASSERT(mDirectionalLight != nullptr, "Shadow Effect -- No light Set!");

    const AEMath::Vector3& direction = mDirectionalLight->direction;
    mLightCamera.SetDirection(direction);
    mLightCamera.SetPosition(mFocusPosition - (direction * 1000.0f));
    mLightCamera.SetNearPlane(1.0f);
    mLightCamera.SetFarPlane(1500.0f);
    mLightCamera.SetSize(mSize, mSize);

}