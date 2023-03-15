#include "Precompiled.h"
#include "GrainEffect.h"

#include "Camera.h"
#include "GraphicsSystem.h"
#include "RenderObject.h"
#include "VertexTypes.h"

using namespace AndrewEngine;
using namespace AndrewEngine::Graphics;

namespace{

    float minPar1;
    float minPar2;
    float maxPar1 = 30;
    float maxPar2 = 30;

}


void GrainEffect::Initialize(const std::filesystem::path& filePath)
{
    mVertexShader.Initialize<VertexPX>(filePath);
    mPixelShader.Initialize(filePath);

    mGrainEffectBuffer.Initialize();
    mSampler.Initialize(Sampler::Filter::Liner, Sampler::AddressMode::Wrap);
    mTextures[0] = TextureManager::Get()->LoadTexture(L"Textures/Grain1.png");
    mTextures[1] = TextureManager::Get()->LoadTexture(L"Textures/Grain2.png");
    mTextures[2] = TextureManager::Get()->LoadTexture(L"Textures/Grain3.png");
    mTextures[3] = TextureManager::Get()->LoadTexture(L"Textures/Grain4.png");
    mTextures[4] = TextureManager::Get()->LoadTexture(L"Textures/Grain5.png");
    mTextures[5] = TextureManager::Get()->LoadTexture(L"Textures/Grain6.png");
    mTextures[6] = TextureManager::Get()->LoadTexture(L"Textures/Grain7.png");
    mTextures[7] = TextureManager::Get()->LoadTexture(L"Textures/Grain8.png");
    mTextures[8] = TextureManager::Get()->LoadTexture(L"Textures/Grain9.png");
    mTextures[9] = TextureManager::Get()->LoadTexture(L"Textures/Grain10.png");
    mTextures[10] = TextureManager::Get()->LoadTexture(L"Textures/Grain11.png");
    mTextures[11] = TextureManager::Get()->LoadTexture(L"Textures/Grain12.png");
}

void GrainEffect::Terminate()
{
    mSampler.Terminate();
    mGrainEffectBuffer.Terminate();
    mPixelShader.Terminate();
    mVertexShader.Terminate();
}

void GrainEffect::Update(float deltaTime)
{
    float dur = 1.0f / updateRate;
    
    time += deltaTime;
    if (time >= dur)
    {
        while (time >= dur)
        {
            time -= dur;
        }
        imageIndex = rand() % mTextures.size();
        
        var = 70 + rand() % 20;
        var = var / 100.0f;
        var2 = 50 + rand() % 20;
        var2 = var2 / 100.0f;
        
        data.param0 = var;
        data.param1 = var2;
    }
}

void GrainEffect::Begin()
{
    mVertexShader.Bind();
    mPixelShader.Bind();
    
    mGrainEffectBuffer.Update(data);
    mGrainEffectBuffer.BindPS(0);
    mSampler.BindPS(0);

    auto tm = TextureManager::Get();

    if (mTextures[imageIndex] != 0)
    {
        tm->BindPS(mTextures[imageIndex], 0);
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
        ImGui::DragFloat("Minimum opacity, layer 1", &minPar1, 10.0f, 70.0f);
        ImGui::DragFloat("Minimum opacity, layer 2", &minPar2, 10.0f, 70.0f);

    }
}