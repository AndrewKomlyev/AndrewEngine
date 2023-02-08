#include <AndrewEngine/Inc/AndrewEngine.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <cstdio>

using namespace AndrewEngine;
using namespace AndrewEngine::Graphics;
using namespace AndrewEngine::AEMath;

struct Arguments
{
    std::filesystem::path inputFileName;
    std::filesystem::path outputFileName;
    float scale = 1.0f;
    bool useBinary = false;
};

std::optional<Arguments> ParseArgs(int argc, char* argv[])
{
    if (argc < 3)
    {
        return std::nullopt;
    }

    Arguments arguments;
    arguments.inputFileName = argv[argc - 2];
    arguments.outputFileName = argv[argc - 1];

    for (int i = 1; i + 2 < argc; ++i)
    {
        if (strcmp(argv[i], "-scale") == 0)
        {
            arguments.scale = atof(argv[i + 1]);
            ++i;
        }
        else if (strcmp(argv[i], "-useBinary") == 0)
        {
            arguments.useBinary = atoi(argv[i + 1]) == 1;
            ++i;
        }
    }
    return arguments;
}

Vector3 ToVector3(const aiVector3D& v)
{
    return
    {
        static_cast<float>(v.x),
        static_cast<float>(v.y),
        static_cast<float>(v.z)
    };
}

int main(int argc, char* argv[])
{
    const auto argOpt = ParseArgs(argc, argv);

    if (argOpt.has_value() == false)
    {
        printf("No arguments present to import model.");
        return -1;
    }

    const auto& arguments = argOpt.value();

    Assimp::Importer importer;

    const uint32_t flags = aiProcessPreset_TargetRealtime_Quality | aiProcess_ConvertToLeftHanded;

    const aiScene* scene = importer.ReadFile(arguments.inputFileName.u8string().c_str(), flags);
    if (scene == nullptr)
    {
        printf("Error: %s\n", importer.GetErrorString());
        return -1;
    }

    printf("Importing %s...", arguments.inputFileName.u8string().c_str());

    Model model;

    if (scene->HasMeshes())
    {
        printf("Reading Mesh Data...\n");
        const uint32_t numMeshes = scene->mNumMeshes;
        model.meshData.reserve(numMeshes);
        for (uint32_t meshIndex = 0; meshIndex < numMeshes; ++meshIndex)
        {
            const auto& aiMesh = scene->mMeshes[meshIndex];
            if (aiMesh->mPrimitiveTypes != aiPrimitiveType_TRIANGLE)
            {
                continue;
            }

            const uint32_t numVertices = aiMesh->mNumVertices;
            const uint32_t numFaces = aiMesh->mNumFaces;
            const uint32_t numIndices = aiMesh->mNumFaces*3;

            auto& meshData = model.meshData.emplace_back();

            printf("Reading material index...\n");

            meshData.materialIndex = aiMesh->mMaterialIndex;

            printf("Reading verticies...\n");

            auto& mesh = meshData.mesh;
            mesh.verticies.reserve(numVertices);

            const aiVector3D* positions = aiMesh->mVertices;
            const aiVector3D* normals = aiMesh->mNormals;
            const aiVector3D* tangents = aiMesh->HasTangentsAndBitangents() ? aiMesh->mTangents : nullptr;
            const aiVector3D* texCoords = aiMesh->HasTextureCoords(0) ? aiMesh->mTextureCoords[0] : nullptr;
            for (uint32_t v = 0; v < numVertices; ++v)
            {
                auto& vertex = mesh.verticies.emplace_back();
                vertex.position = ToVector3(positions[v] * arguments.scale);
                vertex.normal = ToVector3(normals[v]);
                vertex.tangent = tangents ? ToVector3(tangents[v]) : Vector3::Zero;
                if (texCoords)
                {
                    vertex.uvCoord = { texCoords[v].x, texCoords[v].y };
                }
            }

            printf("Reading indicies...\n");
            mesh.indicies.reserve(numIndices);
            const auto& aiFaces = aiMesh->mFaces;
            for (uint32_t i = 0; i < numFaces; ++i)
            {
                const auto& aiFace = aiFaces[i];
                mesh.indicies.push_back(aiFace.mIndices[1]);
                mesh.indicies.push_back(aiFace.mIndices[2]);
                mesh.indicies.push_back(aiFace.mIndices[3]);
            }
        }
    }

    printf("Saving Model...\n");
    ModelIO::SaveModel(arguments.outputFileName, model);


    printf("Saving Material...\n");
    ModelIO::SaveMaterial(arguments.outputFileName, model);

    printf("All Done\n");
    return 0;
}