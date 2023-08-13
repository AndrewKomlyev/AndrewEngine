#include "Precompiled.h"
#include "GameWorld.h"
#include "GameObjectFactory.h"
#include "CameraService.h"
#include "RenderService.h"

#include "TransformComponent.h"
#include "RigidBodyComponent.h"

using namespace AndrewEngine;

void GameWorld::Initialize(uint32_t capacity)
{
    ASSERT(!mInitializied, "GameWorld: is already Initialized");
    mInitializied = true;

    for (auto& service : mServices)
    {
        service->Initialize();
    }

    mGameObjectSlots.resize(capacity);
    mFreeSlots.resize(capacity);
    std::iota(mFreeSlots.begin(), mFreeSlots.end(), 0);
}

void GameWorld::Terminate()
{
    ASSERT(!mUpdating, "GameWorld: cant terminate while updating");
    if (!mInitializied)
    {
        return;
    }

    for (auto& gameObject : mUpdateList)
    {
        DestroyGameObject(gameObject->GetHandle());
    }
    ProcessDestroyList();

    for (auto& service : mServices)
    {
        service->Terminate();
    }
    mInitializied = false;
}

void GameWorld::Update(float deltaTime)
{
    mUpdating = true;
    for (auto& gameObject : mUpdateList)
    {
        gameObject->Update(deltaTime);
    }

    for (auto& service : mServices)
    {
        service->Update(deltaTime);
    }

    mUpdating = false;
    ProcessDestroyList();
}

void GameWorld::Render()
{
    for (auto& service : mServices)
    {
        service->Render();
    }
}

void GameWorld::DebugUI()
{
    ImGui::Begin("Debug Control", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    for (auto& service : mServices)
    {
        service->DebugUI();
    }
    ImGui::End();
}

void GameWorld::LoadLevel(const std::filesystem::path& levelFile)
{
    FILE* file = nullptr;
    auto err = fopen_s(&file, levelFile.u8string().c_str(), "r");
    ASSERT(err == 0 && file != nullptr, "GameWorld: failed to open level %s", levelFile.u8string().c_str());

    char readBuffer[65536];
    rapidjson::FileReadStream readStream(file, readBuffer, sizeof(readBuffer));
    fclose(file);

    rapidjson::Document doc;
    doc.ParseStream(readStream);

    auto services = doc["Services"].GetObj();
    for (auto& service : services)
    {
        const char* serviceName = service.name.GetString();
        if (strcmp(serviceName, "CameraService") == 0)
        {
            auto cameraService = AddService<CameraService>();
        }
        else if (strcmp(serviceName, "RenderService") == 0)
        {
            auto renderService = AddService<RenderService>();
            if (service.value.HasMember("DirectionsLight"))
            {
                const auto& direction = service.value["DirectionalLight"].GetArray();
                const float x = direction[0].GetFloat();
                const float y = direction[1].GetFloat();
                const float z = direction[2].GetFloat();
                renderService->SetDirectionLight({ x, y, z });
            }
        }
        else
        {
            ASSERT(false, "GameWorld: service %s is not defined", serviceName);
        }

    }

    uint32_t capacity = static_cast<uint32_t>(doc["Capacity"].GetInt());
    Initialize(capacity);

    if (doc.HasMember("Physics"))
    {
        const auto& physicsData = doc["Physics"].GetObj();
        if (physicsData.HasMember("Gravity"))
        {
            const auto& gravity = physicsData["Gravity"].GetArray();
            const auto& x = gravity[0].GetFloat();
            const auto& y = gravity[1].GetFloat();
            const auto& z = gravity[2].GetFloat();

            Physics::PhysicsWorld::Get()->SetGravity({ x,y,z });
        }
    }

    auto gameObjects = doc["GameObjects"].GetObj();
    for (auto& gameObject : gameObjects)
    {
        const char* temlplateFile = gameObject.value["Template"].GetString();
        auto obj = CreateGameObject(temlplateFile);
        if (obj != nullptr)
        {
            const char* name = gameObject.name.GetString();
            obj->SetName(name);
            if (gameObject.value.HasMember("Position"))
            {
                const auto& pos = gameObject.value["Position"].GetArray();
                const float x = pos[0].GetFloat();
                const float y = pos[1].GetFloat();
                const float z = pos[2].GetFloat();

                auto transform = obj->GetComponent < TransformComponent>();
                transform->position = { x,y,z };

                auto rigidBodyComponent = obj->GetComponent<RigidBodyComponent>();
                if (rigidBodyComponent != nullptr)
                {
                    rigidBodyComponent->SetPosition(transform->position);
                }
            }
        }
    }
}

GameObject* GameWorld::CreateGameObject(const std::filesystem::path& templateFile)
{
    ASSERT(mInitializied, "GameWorld: is not Initialized");
    if (mFreeSlots.empty())
    {
        ASSERT(false, "GameWorld: no free slots availaible");
        return nullptr;

    }

    const uint32_t freeSlot = mFreeSlots.back();
    mFreeSlots.pop_back();

    auto& slot = mGameObjectSlots[freeSlot];
    auto& newObject = slot.gameObject;
    newObject = std::make_unique<GameObject>();

    GameObjectFactory::Make(templateFile, *newObject);

    newObject->mWorld = this;
    newObject->mHandle.mIndex = freeSlot;
    newObject->mHandle.mGeneration = slot.generation;
    newObject->Initialize();
    mUpdateList.push_back(newObject.get());
    return newObject.get();
}

GameObject* GameWorld::GetGameObject(const GameObjectHandle& handle)
{
    if (!IsValid(handle))
    {
        return nullptr;
    }

    return mGameObjectSlots[handle.mIndex].gameObject.get();
}

void GameWorld::DestroyGameObject(const GameObjectHandle& handle)
{
    if (!IsValid(handle))
    {
        return;
    }

    auto& slot = mGameObjectSlots[handle.mIndex];
    slot.generation++;
    mToBeDestoyed.push_back(handle.mIndex);
}

bool GameWorld::IsValid(const GameObjectHandle& handle)
{
    if (handle.mIndex < 0 || handle.mIndex >= mGameObjectSlots.size())
    {
        return false;
    }
    if (mGameObjectSlots[handle.mIndex].generation != handle.mGeneration)
    {
        return false;
    }

    return true;
}

void GameWorld::ProcessDestroyList()
{
    ASSERT(!mUpdating, "GameWorld: cant destroy when updating Object");
    for (auto& index : mToBeDestoyed)
    {
        auto& slot = mGameObjectSlots[index];

        GameObject* gameObject = slot.gameObject.get();
        ASSERT(!IsValid(gameObject->GetHandle()), "GameWorld: object is still alive");

        mUpdateList.erase(std::remove(mUpdateList.begin(), mUpdateList.end(), gameObject));
        gameObject->Terminate();
        slot.gameObject.reset();
        mFreeSlots.push_back(index);
    }

    mToBeDestoyed.clear();
}
