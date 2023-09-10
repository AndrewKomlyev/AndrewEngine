#include "Precompiled.h"
#include "GameObjectFactory.h"
#include "GameObject.h"

#include "AnimationComponent.h"
#include "CameraComponent.h"
#include "ColliderComponent.h"
#include "FPSCameraControllerComponent.h"
#include "MeshComponent.h"
#include "ModelComponent.h"
#include "RigidBodyComponent.h"
#include "TransformComponent.h"

using namespace AndrewEngine;
using namespace AndrewEngine::Graphics;
using namespace AndrewEngine::AEMath;

namespace rj = rapidjson;

namespace
{
    CustomMake TryMake;
}

void GameObjectFactory::SetCustomMake(CustomMake customMake)
{

    TryMake = customMake;
}

void GameObjectFactory::Make(const std::filesystem::path& templateFile, GameObject& gameObject)
{
    FILE* file = nullptr;
    auto err = fopen_s(&file, templateFile.u8string().c_str(), "r");
    ASSERT(err == 0 && file != nullptr, "GameObjectFactory: failer to open template file %s", templateFile.u8string().c_str());

    char readbuffer[65536];
    rj::FileReadStream readStream(file, readbuffer, sizeof(readbuffer));
    fclose(file);

    rj::Document doc;
    doc.ParseStream(readStream);

    auto components = doc["Components"].GetObj();

    for (auto& component : components)
    {
        const char* componentName = component.name.GetString();
        if (TryMake(componentName, component.value, gameObject))
        {

        }
        else if (strcmp(componentName, "CameraComponent") == 0)
        {
            CameraComponent* cameraComponent = gameObject.AddComponent<CameraComponent>();
            if (component.value.HasMember("Position"))
            {
                const auto& position = component.value["Position"].GetArray();
                const float x = position[0].GetFloat();
                const float y = position[1].GetFloat();
                const float z = position[2].GetFloat();
                cameraComponent->GetCamera().SetPosition({ x, y, z });
            }
            if (component.value.HasMember("LookAt"))
            {
                const auto& lookAt = component.value["LookAt"].GetArray();
                const float x = lookAt[0].GetFloat();
                const float y = lookAt[1].GetFloat();
                const float z = lookAt[2].GetFloat();
                cameraComponent->GetCamera().SetLookAt({ x, y, z });
            }

        }
        else if (strcmp(componentName, "FPSCameraControllerComponent") == 0)
        {
            FPSCameraControllerComponent* fpsCamera = gameObject.AddComponent<FPSCameraControllerComponent>();
            if (component.value.HasMember("MoveSpeed"))
            {
                const float moveSpeed = component.value["MoveSpeed"].GetFloat();
                fpsCamera->SetMoveSpeed(moveSpeed);
            }
            if (component.value.HasMember("TurnSpeed"))
            {
                const float turnSpeed = component.value["TurnSpeed"].GetFloat();
                fpsCamera->SetMoveSpeed(turnSpeed);
            }
        }
        else if (strcmp(componentName, "TransformComponent") == 0)
        {
            TransformComponent* transform = gameObject.AddComponent<TransformComponent>();
        }
        else if (strcmp(componentName, "ModelComponent") == 0)
        {
            ModelComponent* modelComponent = gameObject.AddComponent<ModelComponent>();
            if (component.value.HasMember("FileName"))
            {
                const char* fileName = component.value["FileName"].GetString();
                modelComponent->SetFileName(fileName);
            }
            if (component.value.HasMember("Animations"))
            {
                const auto& animationNames = component.value["Animations"].GetArray();
                for (const auto& animationName : animationNames)
                {
                    const char* animation = animationName.GetString();
                    modelComponent->AddAnimation(animation);
                }
            }
            {
                const char* fileName = component.value["FileName"].GetString();
                modelComponent->SetFileName(fileName);
            }

        }
        else if (strcmp(componentName, "AnimationComponent") == 0)
        {
            AnimationComponent* animationComponent = gameObject.AddComponent<AnimationComponent>();
        }
        else if (strcmp(componentName, "MeshComponent") == 0)
        {
            MeshComponent* meshComponent = gameObject.AddComponent<MeshComponent>();
            if (component.value.HasMember("Shape"))
            {
                const auto& shapeData = component.value["Shape"].GetObj();
                if (shapeData.HasMember("Type"))
                {
                    const char* shapeType = shapeData["Type"].GetString();
                    if (strcmp(shapeType, "Cube") == 0)
                    {
                        const float size = shapeData["Size"].GetFloat();
                        meshComponent->CreateCube(size);
                    }
                    else if (strcmp(shapeType, "Sphere") == 0)
                    {
                        const int slices = shapeData["Slices"].GetInt();
                        const int rings = shapeData["Sings"].GetInt();
                        const float radius = shapeData["Radius"].GetFloat();
                        meshComponent->CreateSphere(slices, rings, radius);
                    }
                    else if (strcmp(shapeType, "Plane") == 0)
                    {
                        const int rows = shapeData["Rows"].GetInt();
                        const int columns = shapeData["Columns"].GetInt();
                        const float size = shapeData["Spacing"].GetFloat();
                        meshComponent->CreatePlane(rows, columns, size);
                    }
                    else
                    {
                        ASSERT(false, "ShapeType: %s is not valid", shapeType);
                    }
                }
            }
            if (component.value.HasMember("Material"))
            {
                Material material;
                const auto& materialData = component.value["Material"].GetObj();
                if (materialData.HasMember("Ambient"))
                {
                    const auto& color = materialData["Ambient"].GetArray();
                    material.ambient.r = color[0].GetFloat();
                    material.ambient.g = color[1].GetFloat();
                    material.ambient.b = color[2].GetFloat();
                    material.ambient.a = color[3].GetFloat();
                }
                if (materialData.HasMember("Diffuse"))
                {
                    const auto& color = materialData["Diffuse"].GetArray();
                    material.diffuse.r = color[0].GetFloat();
                    material.diffuse.g = color[1].GetFloat();
                    material.diffuse.b = color[2].GetFloat();
                    material.diffuse.a = color[3].GetFloat();
                }
                if (materialData.HasMember("Specular"))
                {
                    const auto& color = materialData["Specular"].GetArray();
                    material.specular.r = color[0].GetFloat();
                    material.specular.g = color[1].GetFloat();
                    material.specular.b = color[2].GetFloat();
                    material.specular.a = color[3].GetFloat();
                }
                if (materialData.HasMember("Emissive"))
                {
                    const auto& color = materialData["Emissive"].GetArray();
                    material.emissive.r = color[0].GetFloat();
                    material.emissive.g = color[1].GetFloat();
                    material.emissive.b = color[2].GetFloat();
                    material.emissive.a = color[3].GetFloat();
                }
                if (materialData.HasMember("SpecularPower"))
                {
                    material.power = materialData["SpecularPower"].GetFloat();

                }
                meshComponent->SetMaterial(material);
            }
            if (component.value.HasMember("Textures"))
            {
                const auto& textureData = component.value["Textures"].GetObj();
                if (textureData.HasMember("DiffuseMap"))
                {
                    const char* diffuseMapFileName = textureData["DiffuseMap"].GetString();
                    meshComponent->SetDiffuseMap(diffuseMapFileName);
                }
                if (textureData.HasMember("DisplacementMap"))
                {
                    const char* displacementMapFileName = textureData["DisplacementMap"].GetString();
                    meshComponent->SetDisplacementMap(displacementMapFileName);
                }
                if (textureData.HasMember("NormalMap"))
                {
                    const char* normalMapFileName = textureData["NormalMap"].GetString();
                    meshComponent->SetNormalMap(normalMapFileName);
                }
                if (textureData.HasMember("SpecularMap"))
                {
                    const char* specularlMapFileName = textureData["SpecularMap"].GetString();
                    meshComponent->SetSpecularMap(specularlMapFileName);
                }

            }

        }
        else if (strcmp(componentName, "ColliderComponent") == 0)
        {
            ColliderComponent* colliderComponent = gameObject.AddComponent<ColliderComponent>();
            if (component.value.HasMember("Shape"))
            {
                const auto& shapeData = component.value["Shape"].GetObj();
                if (shapeData.HasMember("Type"))
                {
                    const char* shapeType = shapeData["Type"].GetString();
                    if (strcmp(shapeType, "Box") == 0)
                    {
                        const auto& halfExtents = shapeData["HalfExtents"].GetArray();
                        const float x = halfExtents[0].GetFloat();
                        const float y = halfExtents[1].GetFloat();
                        const float z = halfExtents[2].GetFloat();
                        colliderComponent->SetBoxCollider({ x,y,z });
                    }
                    else if (strcmp(shapeType, "Sphere") == 0)
                    {
                        const float radius = shapeData["Radius"].GetFloat();
                        colliderComponent->SetSphereCollision(radius);
                    }
                    else if (strcmp(shapeType, "Hull") == 0)
                    {
                        const auto& halfExtents = shapeData["HalfExtents"].GetArray();
                        const auto& origin = shapeData["Origin"].GetArray();
                        const float ex = halfExtents[0].GetFloat();
                        const float ey = halfExtents[1].GetFloat();
                        const float ez = halfExtents[2].GetFloat();
                        const float ox = origin[0].GetFloat();
                        const float oy = origin[1].GetFloat();
                        const float oz = origin[2].GetFloat();
                        colliderComponent->SetHullCollision({ ex,ey,ez }, { ox,oy,oz });
                    }
                    else
                    {
                        ASSERT(false, "ShapeType: %s is not valid", shapeType);
                    }
                }
                else
                {
                    ASSERT(false, "ColliderComponent: ShapeType is not valid");
                }
            }
        }
        else if (strcmp(componentName, "RigidBodyComponent") == 0)
        {
            RigidBodyComponent* rigidBodyComponent = gameObject.AddComponent<RigidBodyComponent>();
            if (component.value.HasMember("Mass"))
            {
                const float mass = component.value["Mass"].GetFloat();
                rigidBodyComponent->SetMass(mass);
            }
        }
        else
        {
            ASSERT(false, "GameObjectFactory: %s was not defined", componentName);
        }
    }


}