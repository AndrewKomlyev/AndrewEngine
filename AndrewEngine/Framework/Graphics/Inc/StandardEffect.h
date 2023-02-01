#pragma once

#include "ConstantBuffer.h"
#include "LightTypes.h"
#include "PixelShader.h"
#include "Sampler.h"
#include "VertexShader.h"

namespace AndrewEngine::Graphics
{
    class Camera;
    class RenderObject;

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

        void DebugUI();

    private:

        struct TransformData
        {
            AEMath::Matrix4 world;
            AEMath::Matrix4 wvp;
            AEMath::Vector3 viewPosition;
            float displacementWeight;
        };

        struct SettingsData
        {
            int useDiffuseMap = 1;
            int useSpecularMap = 1;
            int useDisplacementMap = 1;
            int useNormalMap = 1;
        };

        using TransformBuffer = TypeConstantBuffer<TransformData>;
        using LightBuffer = TypeConstantBuffer<DirectionalLight>;
        using SettingsBuffer = TypeConstantBuffer<SettingsData>;

        TransformBuffer mTransformBuffer;
        LightBuffer mLightBuffer;
        SettingsBuffer mSettingsBuffer;
        Sampler mSampler;

        VertexShader mVertexShader;
        PixelShader mPixelShader;


        SettingsData mSettingsData;
        float mDisplacementWeight = 0.0f;
        const Camera* mCamera = nullptr;
        const DirectionalLight* mDirectionalLight = nullptr;
    };
}
