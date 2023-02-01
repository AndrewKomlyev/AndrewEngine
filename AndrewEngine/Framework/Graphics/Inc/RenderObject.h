#pragma once
#include "MeshBuffer.h"
#include "TextureManager.h"
#include "Transform.h"

namespace AndrewEngine::Graphics
{
    class RenderObject
    {
    public:
        void Terminate();

        Transform transform;

        TextureId diffuseMapId;
        TextureId normalMapId;
        TextureId displacementMapId;
        TextureId specularMapId;


        MeshBuffer meshBuffer;
    };
}