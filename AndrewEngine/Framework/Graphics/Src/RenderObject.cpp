#include "Precompiled.h"
#include "RenderObject.h"
#include "Model.h"

using namespace AndrewEngine;
using namespace AndrewEngine::Graphics;
void RenderObject::Terminate()
{
    diffuseMapId = 0;
    specularMapId = 0;
    displacementMapId = 0;
    normalMapId = 0;
    meshBuffer.Terminate();
}


RenderGroup Graphics::CreateRenderGroup(const Model& model)
{
    RenderGroup renderGroup;
    renderGroup.reserve(model.meshData.size());

    auto TryLoadTexture = [](const auto& textureName) -> TextureId
    {
        if (textureName.empty())
        {
            return 0;
        }

        return TextureManager::Get()->LoadTexture(textureName, false);
    };


    for (auto& meshData : model.meshData)
    {
        auto& renderObject = renderGroup.emplace_back();
        auto& materialData = model.materialData[meshData.materialIndex];
        renderObject.material = materialData.material;
        renderObject.diffuseMapId = TryLoadTexture(materialData.diffuseMapName);
        renderObject.specularMapId = TryLoadTexture(materialData.specularMapName);
        renderObject.displacementMapId = TryLoadTexture(materialData.displacementMapName);
        renderObject.normalMapId = TryLoadTexture(materialData.normalMapName);

        renderObject.meshBuffer.Initialize(meshData.mesh);
    }
    return renderGroup;
}

void Graphics::CleanupRenderGroup(RenderGroup& renderGroup)
{
    for (auto& renderObject : renderGroup)
    {
        renderObject.Terminate();
    }
}