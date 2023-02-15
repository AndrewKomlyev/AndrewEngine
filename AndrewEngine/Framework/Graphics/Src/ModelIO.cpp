#include "Precompiled.h"
#include "ModelIO.h"
#include "Model.h"

using namespace AndrewEngine;
using namespace AndrewEngine::Graphics;


void ModelIO::SaveModel(std::filesystem::path filePath, const Model& model)
{
    if (model.meshData.empty())
    {
        return;
    }

    FILE* file = nullptr;
    fopen_s(&file, filePath.u8string().c_str(), "w");
    if (file == nullptr)
    {
        return;
    }


    const uint32_t meshCount = static_cast<uint32_t>(model.meshData.size());
    fprintf_s(file, "MeshCount: %d\n", meshCount);
    for (uint32_t i = 0; i < meshCount; ++i)
    {
        const auto& meshData = model.meshData[i];
        fprintf_s(file, "MaterialIndex: %d\n", meshData.materialIndex);

        const auto& mesh = meshData.mesh;
        const uint32_t vertexCount = static_cast<uint32_t>(mesh.verticies.size());
        fprintf_s(file, "VertecCount: %d\n", vertexCount);

        for (auto& v: mesh.verticies)
        {
            fprintf_s(file, "%f %f %f %f %f %f %f %f %f %f %f\n", v.position.x, v.position.y, v.position.z, v.normal.x, v.normal.y, v.normal.z, v.tangent.x, v.tangent.y, v.tangent.z, v.uvCoord.x, v.uvCoord.y);
        }

        const uint32_t indexCount = static_cast<uint32_t>(mesh.indicies.size());
        fprintf_s(file, "IndexCount: %d\n", indexCount);
        for (size_t n = 2; n < indexCount; n+=3)
        {
            fprintf_s(file, "%d %d %d\n", mesh.indicies[n - 2], mesh.indicies[n - 1], mesh.indicies[n]);
        }
    }
    
    fclose(file);
}
void ModelIO::LoadModel(std::filesystem::path filePath, Model& model)
{
    FILE* file = nullptr;
    fopen_s(&file, filePath.u8string().c_str(), "r");
    if (file == nullptr)
    {
        return;
    }

    uint32_t meshCount = 0;
    fscanf_s(file, "MeshCount: %d\n", &meshCount);

    model.meshData.resize(meshCount);
    for (uint32_t i = 0; i < meshCount; ++i)
    {
        auto& meshData = model.meshData[i];
        fscanf_s(file, "MaterialIndex: %d\n", &meshData.materialIndex);

        auto& mesh = meshData.mesh;
        uint32_t vertexCount = 0;
        fscanf_s(file, "VertecCount: %d\n", &vertexCount);
        mesh.verticies.resize(vertexCount);
        for (auto& v : mesh.verticies)
        {
            fscanf_s(file, "%f %f %f %f %f %f %f %f %f %f %f\n", &v.position.x, &v.position.y, &v.position.z, &v.normal.x, &v.normal.y, &v.normal.z, &v.tangent.x, &v.tangent.y, &v.tangent.z, &v.uvCoord.x, &v.uvCoord.y);
        }

        uint32_t indexCount = 0;
        fscanf_s(file, "IndexCount: %d\n", &indexCount);
        mesh.indicies.resize(indexCount);
        for (size_t n = 2; n < indexCount; n += 3)
        {
            fscanf_s(file, "%d %d %d\n", &mesh.indicies[n - 2], &mesh.indicies[n - 1], &mesh.indicies[n]);
        }
    }

    fclose(file);
}

void ModelIO::SaveMaterial(std::filesystem::path filePath, const Model& model)
{
    if (model.materialData.empty())
    {
        return;
    }
    filePath.replace_extension("material");
    FILE* file = nullptr;
    fopen_s(&file, filePath.u8string().c_str(), "w");
    if (file == nullptr)
    {
        return;
    }


    uint32_t materialCount = static_cast<uint32_t>(model.materialData.size());
    fprintf_s(file, "MaterialCount: %d\n", materialCount);
    for (auto& materialData: model.materialData)
    {
        auto& m = materialData.material;

        fprintf_s(file, "%f %f %f %f \n", m.ambient.r, m.ambient.g, m.ambient.b, m.ambient.a);
        fprintf_s(file, "%f %f %f %f \n", m.diffuse.r, m.diffuse.g, m.diffuse.b, m.diffuse.a);
        fprintf_s(file, "%f %f %f %f \n", m.specular.r, m.specular.g, m.specular.b, m.specular.a);
        fprintf_s(file, "%f %f %f %f \n", m.emissive.r, m.emissive.g, m.emissive.b, m.emissive.a);



        fprintf_s(file, "%s\n", materialData.diffuseMapName.empty() ? "none" : materialData.diffuseMapName.c_str());
        fprintf_s(file, "%s\n", materialData.specularMapName.empty() ? "none" : materialData.specularMapName.c_str());
        fprintf_s(file, "%s\n", materialData.displacementMapName.empty() ? "none" : materialData.displacementMapName.c_str());
        fprintf_s(file, "%s\n", materialData.normalMapName.empty() ? "none" : materialData.normalMapName.c_str());
    }

    fclose(file);
}
void ModelIO::LoadMaterial(std::filesystem::path filePath, Model& model)
{
    filePath.replace_extension("material");
    FILE* file = nullptr;
    fopen_s(&file, filePath.u8string().c_str(), "r");
    if (file == nullptr)
    {
        return;
    }

    auto TryReadTextureName = [&](auto& fileName)
    {
        char buffer[MAX_PATH]{};
        fscanf_s(file, "%s\n", buffer, (uint32_t)sizeof(buffer));
        if (strcmp(buffer, "none") != 0)
        {
            fileName = filePath.replace_filename(buffer).string();
        }
    };

    uint32_t materialCount = 0;
    fscanf_s(file, "MaterialCount: %d\n", &materialCount);
    model.materialData.resize(materialCount);
    for (auto& materialData : model.materialData)
    {
        auto& m = materialData.material;

        fscanf_s(file, "%f %f %f %f \n", &m.ambient.r, &m.ambient.g, &m.ambient.b, &m.ambient.a);
        fscanf_s(file, "%f %f %f %f \n", &m.diffuse.r, &m.diffuse.g, &m.diffuse.b, &m.diffuse.a);
        fscanf_s(file, "%f %f %f %f \n", &m.specular.r, &m.specular.g, &m.specular.b, &m.specular.a);
        fscanf_s(file, "%f %f %f %f \n", &m.emissive.r, &m.emissive.g, &m.emissive.b, &m.emissive.a);



        TryReadTextureName(materialData.diffuseMapName);
        TryReadTextureName(materialData.specularMapName);
        TryReadTextureName(materialData.displacementMapName);
        TryReadTextureName(materialData.normalMapName);
    }

    fclose(file);
}