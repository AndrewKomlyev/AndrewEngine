#include "Precompiled.h"
#include "GrainEffect.h"

#include "Camera.h"
#include "GraphicsSystem.h"
#include "RenderObject.h"
#include "VertexTypes.h"

using namespace AndrewEngine;
using namespace AndrewEngine::Graphics;

void GrainEffect::Initialize(const std::filesystem::path& filePath)
{
    mVertexShader.Initialize<VertexPX>(filePath);
    mPixelShader.Initialize(filePath);

    mGrainEffectBuffer.Initialize();
    mSampler.Initialize(Sampler::Filter::Liner, Sampler::AddressMode::Wrap);
    mTextures[0] = TextureManager::Get()->LoadTexture(L"Textures/GrainTest.png");
    mTextures[1] = TextureManager::Get()->LoadTexture(L"Textures/GrainTest.png");
    mTextures[2] = TextureManager::Get()->LoadTexture(L"Textures/GrainTest.png");
    mTextures[3] = TextureManager::Get()->LoadTexture(L"Textures/GrainTest.png");
    
}

void GrainEffect::Terminate()
{
    mSampler.Terminate();
    mGrainEffectBuffer.Terminate();
    mPixelShader.Terminate();
    mVertexShader.Terminate();
}

void GrainEffect::Begin()
{
    mVertexShader.Bind();
    mPixelShader.Bind();

    GrainEffectData data;
    
    mGrainEffectBuffer.Update(data);
    mGrainEffectBuffer.BindPS(0);
    mSampler.BindPS(0);


    auto tm = TextureManager::Get();
    int i = rand() % mTextures.size();
    if (mTextures[i] != 0)
    {
        tm->BindPS(mTextures[i], 0);
    }
    
    if (mTextureImage != nullptr)
    {
        mTextureImage->BindPS(1);
    }

}

void GrainEffect::End()
{
    Texture::UnbindPS(0);
    
    if (mTextureImage != nullptr)
    {
        Texture::UnbindPS(1);
    }  
}

void GrainEffect::Render(const RenderObject& renderObject)
{
    renderObject.meshBuffer.Render();
}

void GrainEffect::SetTexture(const Texture* texture)
{
    mTextureImage = texture;
}





void GrainEffect::DebugUI()
{
    if (ImGui::CollapsingHeader("Post Processing Effect", ImGuiTreeNodeFlags_DefaultOpen))
    {
        
    }
}