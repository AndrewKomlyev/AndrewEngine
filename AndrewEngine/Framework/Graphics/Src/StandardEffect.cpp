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
    mMaterialBuffer.Initialize();
    mSettingsBuffer.Initialize();
    mVertexShader.Initialize<Vertex>(L"../../Assets/Shaders/Standard.fx");
    mPixelShader.Initialize(L"../../Assets/Shaders/Standard.fx");
    mSampler.Initialize(Sampler::Filter::Liner, Sampler::AddressMode::Wrap);
}

void StandardEffect::Terminate()
{
    mSampler.Terminate();
    mPixelShader.Terminate();
    mVertexShader.Terminate();
    mSettingsBuffer.Terminate();
    mMaterialBuffer.Terminate();
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

    mMaterialBuffer.BindVS(2);
    mMaterialBuffer.BindPS(2);

    mSettingsBuffer.BindVS(3);
    mSettingsBuffer.BindPS(3);

    mSampler.BindVS(0);
    mSampler.BindPS(0);
}

void StandardEffect::End()
{
    if (mShadowMap != nullptr)
    {
        Texture::UnbindPS(4);
    }
}

void StandardEffect::Render(const RenderObject& renderObject)
{

    const auto& matWorld = renderObject.transform.GetMatrix4();
    const auto& matView = mCamera->GetViewMatrix();
    const auto& matProj = mCamera->GetProjectionMatrix();

    SettingsData settingData;
    settingData.useDiffuseMap = mSettingsData.useDiffuseMap > 0 && renderObject.diffuseMapId > 0;
    settingData.useSpecularMap = mSettingsData.useSpecularMap > 0 && renderObject.specularMapId > 0;
    settingData.useDisplacementMap = mSettingsData.useDisplacementMap > 0 && renderObject.displacementMapId > 0;
    settingData.useNormalMap = mSettingsData.useNormalMap > 0 && renderObject.normalMapId > 0;
    settingData.useShadowMap = mSettingsData.useShadowMap > 0 && mShadowMap != nullptr;
    settingData.depthBias = mDepthBias;

    TransformData transformData;
    transformData.world = Transpose(matWorld);
    transformData.wvp[0] = Transpose(matWorld * matView * matProj);
    transformData.viewPosition = mCamera->GetPosition();
    transformData.displacementWeight = mDisplacementWeight;

    if (settingData.useShadowMap)
    {
        const auto& matLightView = mLightCamera->GetViewMatrix();
        const auto& matLightProj = mLightCamera->GetProjectionMatrix();
        transformData.wvp[1] = Transpose(matWorld * matLightView * matLightProj);
        mShadowMap->BindPS(4);
    }

    mTransformBuffer.Update(transformData);
    mLightBuffer.Update(*mDirectionalLight);
    mMaterialBuffer.Update(renderObject.material);
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

void StandardEffect::SetLightCamera(const Camera& camera)
{

    mLightCamera = &camera;
}

void StandardEffect::SetShadowMap(const Texture* shadowMap)
{
    mShadowMap = shadowMap;
}


void StandardEffect::DebugUI()
{
    if (ImGui::CollapsingHeader("Standard Effect", ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::DragFloat("Displacement Weight", &mDisplacementWeight, 0.1f);

        bool useDiffuseMap = mSettingsData.useDiffuseMap > 0;
        ImGui::Checkbox("Use Diffuse Map", &useDiffuseMap);
        mSettingsData.useDiffuseMap = (useDiffuseMap) ? 1 : 0;

        bool useSpecularMap = mSettingsData.useSpecularMap > 0;
        ImGui::Checkbox("Use Specular Map", &useSpecularMap);
        mSettingsData.useSpecularMap = (useSpecularMap) ? 1 : 0;

        bool useDisplacementMap = mSettingsData.useDisplacementMap > 0;
        ImGui::Checkbox("Use Displacement Map", &useDisplacementMap);
        mSettingsData.useDisplacementMap = (useDisplacementMap) ? 1 : 0;

        bool useNormalMap = mSettingsData.useNormalMap > 0;
        ImGui::Checkbox("Use Normal Map", &useNormalMap);
        mSettingsData.useNormalMap = (useNormalMap) ? 1 : 0;

        bool useShadowMap = mSettingsData.useShadowMap > 0;
        ImGui::Checkbox("Use Shadow Map", &useShadowMap);
        mSettingsData.useShadowMap = (useShadowMap) ? 1 : 0;

        ImGui::DragFloat("Depth Bias", &mDepthBias, 0.00001f, 0.0f, 1.0f, "");
    }
}