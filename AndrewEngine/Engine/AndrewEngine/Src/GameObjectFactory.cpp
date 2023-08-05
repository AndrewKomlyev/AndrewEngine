#include "Precompiled.h"
#include "GameObjectFactory.h"
#include "GameObject.h"
#include "CameraComponent.h"
#include "FPSCameraControllerComponent.h"
#include "ModelComponent.h"
#include "TransformComponent.h"

using namespace AndrewEngine;
using namespace AndrewEngine::Graphics;
using namespace AndrewEngine::AEMath;

namespace rj = rapidjson;

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
        if (strcmp(componentName, "CameraComponent") == 0)
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
        }
        else
        {
            ASSERT(false, "GameObjectFactory: %s was not defined", componentName);
        }
    }


}