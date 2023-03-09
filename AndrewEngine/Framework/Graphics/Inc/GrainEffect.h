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


        Sampler mSampler;

        VertexShader mVertexShader;
        PixelShader mPixelShader;

        GrainEffectBuffer mGrainEffectBuffer;
        const Texture* mTextureImage =nullptr;

        std::array<TextureId, 12> mTextures;
    };
}