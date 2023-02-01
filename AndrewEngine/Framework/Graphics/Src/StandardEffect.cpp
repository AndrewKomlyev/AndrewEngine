#include "Precompiled.h"
#include "StandardEffect.h"
#include "Camera.h"
#include "RenderObject.h"
#include "VertexTypes.h"

using namespace AndrewEngine;
using namespace AndrewEngine::Graphics;

void StandardEffect::Initialize(const std::filesystem::path& filePath)
{
    mTransformBuffer.Initialize();
    mLightBuffer.Initialize();

    mVertexShader.Initialize<Vertex>(L"../../Assets/Shaders/Standard.fx");
    mPixelShader.Initialize(L"../../Assets/Shaders/Standard.fx");
    mSampler.Initialize(Sampler::Filter::Liner, Sampler::AddressMode::Wrap);
}

void StandardEffect::Terminate()
{
    mSampler.Terminate();
    mPixelShader.Terminate();
    mVertexShader.Terminate();
    mLightBuffer.Terminate();
    mTransformBuffer.Terminate();
}

void StandardEffect::Begin()
{
    ASSERT(mCamera != nullptr, "StandardEffect - no camera Set!");
    ASSERT(mDirectionalLight != nullptr, "StandardEffect - no light Set!");
    mVertexShader.Bind();
    mPixelShader.Bind();

    mTransformBuffer.BindVS(0);

    mLightBuffer.BindVS(1);
    mLightBuffer.BindPS(1);

    mSettingsBuffer.BindVS(2);
    mSettingsBuffer.BindPS(2);

    mSampler.BindVS(0);
    mSampler.BindPS(0);
}

void StandardEffect::End()
{
    //Cleanup
}

void StandardEffect::Render(const RenderObject& renderObject)
{
    const auto& matWorld = renderObject.transform.GetMatrix4();
    const auto& matView = mCamera->GetViewMatrix();
    const auto& matProj = mCamera->GetProjectionMatrix();


    TransformData transformData;
    transformData.world = Transpose(matWorld);
    transformData.wvp = Transpose(matWorld * matView * matProj);
    transformData.viewPosition = mCamera->GetPosition();
    transformData.displacementWeight = mDisplacementWeight;

    SettingsData settingData;
    settingData.useDiffuseMap = mSettingsData.useDiffuseMap > 0 && renderObject.diffuseMapId > 0;
    settingData.useSpecularMap = mSettingsData.useSpecularMap > 0 && renderObject.specularMapId > 0;
    settingData.useDisplacementMap = mSettingsData.useDisplacementMap > 0 && renderObject.displacementMapId > 0;
    settingData.useNormalMap = mSettingsData.useNormalMap > 0 && renderObject.normalMapId > 0;

    mTransformBuffer.Update(transformData);
    mLightBuffer.Update(*mDirectionalLight);
    mSettingsBuffer.Update(settingData);


    auto tm = TextureManager::Get();
    tm->BindPS(renderObject.diffuseMapId, 0);
    tm->BindPS(renderObject.normalMapId, 1);
    tm->BindVS(renderObject.displacementMapId, 2);
    tm->BindPS(renderObject.specularMapId, 3);

    renderObject.meshBuffer.Render();
}

void StandardEffect::SetCamera(const Camera& camera)
{
    mCamera = &camera;
}

void StandardEffect::SetDireectionalLight(const DirectionalLight& directionalLight)
{
    mDirectionalLight = &directionalLight;
}

void StandardEffect::DebugUI()
{
    ImGui::Begin("Standard effect", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    ImGui::Separator();

    ImGui::DragFloat("Displacement Weight", &mDisplacementWeight, 0.1f);
    ImGui::Separator();
    ImGui::End();
}