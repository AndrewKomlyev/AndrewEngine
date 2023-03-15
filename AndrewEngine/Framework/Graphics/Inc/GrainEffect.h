#pragma once
#include "ConstantBuffer.h"
#include "PixelShader.h"
#include "Sampler.h"
#include "VertexShader.h"
#include "Material.h"
#include "TextureManager.h"

namespace AndrewEngine::Graphics
{
    class Camera;
    class RenderObject;

    class GrainEffect
    {
    public:
        void Initialize(const std::filesystem::path& filePath);
        void Terminate();

        void Update(float deltaTime);
        void Begin();
        void End();

        void Render(const RenderObject& renderObject);
        void SetTexture(const Texture* texture);
        Texture CreateTexture();

        void DebugUI();
    private:

        struct GrainEffectData
        {
            float param0 = 0.0f;
            float param1 = 0.0f;
            float param2 = 0.0f;
            float param3 = 0.0f;
        };

        using GrainEffectBuffer = TypeConstantBuffer<GrainEffectData>;

        float updateRate = 24.0f;
        float time = 0.0f;

        float var = 0;
        float var2 = 0;

        Sampler mSampler;

        int imageIndex;
        VertexShader mVertexShader;
        PixelShader mPixelShader;

        GrainEffectBuffer mGrainEffectBuffer;
        const Texture* mTextureImage =nullptr;
        GrainEffectData data;
        std::array<TextureId, 12> mTextures;
    };
}