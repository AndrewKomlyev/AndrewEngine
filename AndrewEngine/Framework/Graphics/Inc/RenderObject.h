#pragma once
#include "Material.h"
#include "MeshBuffer.h"
#include "ModelManager.h"
#include "TextureManager.h"
#include "Transform.h"
#include "Skeleton.h"

namespace AndrewEngine::Graphics
{
    struct Model;
    class RenderObject
    {
    public:
        void Terminate();

        Transform transform;

        Material material;

        TextureId diffuseMapId;
        TextureId normalMapId;
        TextureId displacementMapId;
        TextureId specularMapId;

        ModelId modelId = 0;
        MeshBuffer meshBuffer;
        const Skeleton* skeleton = nullptr;
    };

    using RenderGroup = std::vector<RenderObject>;
    [[nodiscard]] RenderGroup CreateRenderGroup(ModelId modelId);
    [[nodiscard]] RenderGroup CreateRenderGroup(const Model& model);
    void CleanupRenderGroup(RenderGroup& renderGroup);

    template<class Effect>
    void DrawRenderGroup(Effect& effect, const RenderGroup& renderGroup)
    {
        for (auto& renderObject : renderGroup)
        {
            effect.Render(renderObject);
        }
    }

}