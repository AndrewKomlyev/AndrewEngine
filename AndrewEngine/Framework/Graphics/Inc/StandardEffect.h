#pragma once
#include "ConstantBuffer.h"
#include "LightTypes.h"
#include "PixelShader.h"
#include "Sampler.h"
#include "VertexShader.h"
#include "Material.h"

namespace AndrewEngine::Graphics
{
    class Camera;
    class RenderObject;
    class Texture;

    class StandardEffect
    {
    public:
        void Initialize(const std::filesystem::path& filePath);
        void Terminate();

        void Begin();
        void End();

        void Render(const RenderObject& renderObject);

        void SetCamera(const Camera& camera);
        void SetDireectionalLight(const DirectionalLight& directionalLight);
        void SetLightCamera(const Camera& camera);
        void SetShadowMap(const Texture* shadowMap);

        void DebugUI();

    private:

        struct TransformData
        {
            AEMath::Matrix4 world;
            AEMath::Matrix4 wvp[2];
            AEMath::Vector3 viewPosition;
            float displacementWeight;
        };

        struct BoneTransformData
        {
            static constexpr size_t MaxBoneCount = 256;
            AEMath::Matrix4 boneTransforms[MaxBoneCount];

        };

        struct SettingsData
        {
            int useDiffuseMap = 1;
            int useSpecularMap = 1;
            int useDisplacementMap = 1;
            int useNormalMap = 1;
            int useShadowMap = 1;
            int useSkinning = 1;
            float depthBias = 0.0f;
            float padding[1] = { 0.0f };
        };

        using TransformBuffer = TypeConstantBuffer<TransformData>;
        using BoneTransformBuffer = ConstantBuffer;
        using LightBuffer = TypeConstantBuffer<DirectionalLight>;
        using MaterialBuffer = TypeConstantBuffer<Material>;
        using SettingsBuffer = TypeConstantBuffer<SettingsData>;

        TransformBuffer mTransformBuffer;
        BoneTransformBuffer mBoneTransformBuffer;
        LightBuffer mLightBuffer;
        MaterialBuffer mMaterialBuffer;
        SettingsBuffer mSettingsBuffer;
        Sampler mSampler;

        VertexShader mVertexShader;
        PixelShader mPixelShader;

        //BoneTransformData mBoneTransformData;

        SettingsData mSettingsData;
        float mDisplacementWeight = 0.0f;
        float mDepthBias = 0.0f;
        const Camera* mCamera = nullptr;
        const Camera* mLightCamera = nullptr;
        const DirectionalLight* mDirectionalLight = nullptr;
        const Texture* mShadowMap = nullptr;
    };
}
