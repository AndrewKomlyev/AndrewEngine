#pragma once
#include "ConstantBuffer.h"
#include "PixelShader.h"
#include "Sampler.h"
#include "VertexShader.h"

namespace AndrewEngine::Graphics
{
    class RenderObject;
    class Texture;

    class PostProcessingEffect
    {
    public:
        enum class Mode
        {
            None,
            Monochrome,
            Invert,
            Mirror,
            Blur,
            Combine2
        };

        void Initialize(const std::filesystem::path& filePath);
        void Terminate();

        void Begin();
        void End();

        void Render(const RenderObject& renderObject);

        void SetTexture(const Texture* texture, uint32_t slot = 0);
        void SetMode(Mode mode);
        void SetMirrorScale(float mirrorScale);

        void DebugUI();

    private:
        struct PostProcessingData
        {
            Mode mode = Mode::None;
            float param0 = 0.0f;
            float param1 = 0.0f;
            float param2 = 0.0f;
        };

        using PostProcessingBuffer = TypeConstantBuffer<PostProcessingData>;

        VertexShader mVertexShader;
        PixelShader mPixelShader;

        PostProcessingBuffer mPostProcessingBuffer;

        Sampler mSampler;

        std::array<const Texture*, 4> mTextures; 
        Mode mMode = Mode::None;

        float mMirrorScale = -1.0f;

    };
}