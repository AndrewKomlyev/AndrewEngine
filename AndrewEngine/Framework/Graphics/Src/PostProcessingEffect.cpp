#include "Precompiled.h"
#include "PostProcessingEffect.h"

#include "Camera.h"
#include "GraphicsSystem.h"
#include "RenderObject.h"
#include "VertexTypes.h"

using namespace AndrewEngine;
using namespace AndrewEngine::Graphics;

void PostProcessingEffect::Initialize(const std::filesystem::path& filePath)
{
    mVertexShader.Initialize<VertexPX>(filePath);
    mPixelShader.Initialize(filePath);

    mPostProcessingBuffer.Initialize();
    mSampler.Initialize(Sampler::Filter::Liner, Sampler::AddressMode::Wrap);
}

void PostProcessingEffect::Terminate()
{
    mSampler.Terminate();
    mPixelShader.Terminate();
    mVertexShader.Terminate();

}

void PostProcessingEffect::Begin()
{
    mVertexShader.Bind();
    mPixelShader.Bind();

    PostProcessingData data;
    data.mode = mMode;

    switch (mMode)
    {
        case AndrewEngine::Graphics::PostProcessingEffect::Mode::None:
        {
            data.param0 = mMirrorScale;
            break;
        }
        case AndrewEngine::Graphics::PostProcessingEffect::Mode::Monochrome:
        {
            data.param0 = mMirrorScale;
            break;
        }
        case AndrewEngine::Graphics::PostProcessingEffect::Mode::Invert:
        {
            data.param0 = mMirrorScale;
            break;
        }
        case AndrewEngine::Graphics::PostProcessingEffect::Mode::Mirror:
        {
            data.param0 = mMirrorScale;
            break;
        }
        case AndrewEngine::Graphics::PostProcessingEffect::Mode::Blur:
        {
            auto gs = GraphicsSystem::Get();
            const auto screenWidth = gs->GetBackBufferWidth();
            const auto screenHeight = gs->GetBackBufferHeight();
            data.param0 = 5.0f / screenWidth;
            data.param1 = 5.0f / screenHeight;
            break;
        }
    }
    mPostProcessingBuffer.Update(data);
    mPostProcessingBuffer.BindPS(0);
    mSampler.BindPS(0);

    for (int i = 0; i < mTextures.size(); ++i)
    {
        if (mTextures[i] != nullptr)
        {
            mTextures[i]->BindPS(i);
        }
    }
}

void PostProcessingEffect::End()
{
    for (int i = 0; i < mTextures.size(); ++i)
    {
        Texture::UnbindPS(i);
    }
}

void PostProcessingEffect::Render(const RenderObject& renderObject)
{
    renderObject.meshBuffer.Render();
}

void PostProcessingEffect::SetTexture(const Texture* texture, uint32_t slot)
{
    ASSERT(slot < mTextures.size(), "PostProcessingEffect -- invalid slot index");
    mTextures[slot] = texture;
}

void PostProcessingEffect::SetMode(Mode mode)
{
    mMode = mode;
}

void PostProcessingEffect::SetMirrorScale(float mirrorScale)
{
    mMirrorScale = mirrorScale;
}

void PostProcessingEffect::DebugUI()
{
    if (ImGui::CollapsingHeader("Post Processing Effect", ImGuiTreeNodeFlags_DefaultOpen))
    {
        int currentMode = static_cast<int>(mMode);
        const char* modeNames[] =
        {
            "None",
            "Monochrome",
            "Invert",
            "Mirror",
            "Blur",
            "Combine2"
        };

        if (ImGui::Combo("Mode", &currentMode, modeNames, static_cast<int>(std::size(modeNames))))
        {
            mMode = static_cast<Mode>(currentMode);
        }

        if (mMode == Mode::Mirror)
        {
            ImGui::DragFloat("Scale", &mMirrorScale, 0.01f, -5.0f, 5.0f);
        }
    }
}