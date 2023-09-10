#include "Precompiled.h"
#include "GameObject.h"

using namespace AndrewEngine;

static uint32_t gUniqueId = 0;

void GameObject::Initialize()
{
    ASSERT(!mInitialized, "GameObject: is already intialized!");
    mInitialized = true;
    for (auto& component : mComponents)
    {
        component->Initialize();
    }
    mUniqueId = ++gUniqueId;
}

void GameObject::Terminate()
{
    for (auto& component : mComponents)
    {
        component->Terminate();
    }
}

void GameObject::Update(float deltaTime)
{
    for (auto& component : mComponents)
    {
        component->Update(deltaTime);
    }
}

void GameObject::DebugUI()
{
    for (auto& component : mComponents)
    {
        component->DebugUI();
    }
}


void GameObject::EditorUI()
{
    if (ImGui::Button("SaveTemplate"))
    {
        rapidjson::Document doc;
        rapidjson::Value components(rapidjson::kObjectType);
        Serialize(doc, components);
        doc.SetObject();
        doc.AddMember("GameObjects", components, doc.GetAllocator());

        FILE* file = nullptr;
        auto err = fopen_s(&file, mTemplate.c_str(), "w");
        ASSERT(err == 0 && file != nullptr, "GameWorld: failed to open level %s", mTemplate.c_str());

        char writeBuffer[65536];
        rapidjson::FileWriteStream writeStream(file, writeBuffer, sizeof(writeBuffer));

        rapidjson::Writer<rapidjson::FileWriteStream> writer(writeStream);
        doc.Accept(writer);

        fclose(file);
    }

    std::string gameObjectName = std::string("GameObject##" + std::to_string(mUniqueId)).c_str();
    if (ImGui::CollapsingHeader(mName.c_str(), ImGuiTreeNodeFlags_None))
    {
        char buffer[256];
        strcpy_s(buffer, mName.c_str());
        std::string objName = std::string("Name##" + std::to_string(mUniqueId)).c_str();
        if (ImGui::InputText(gameObjectName.c_str(), buffer, sizeof(buffer)))
        {
            mName = std::move(buffer);
        }
        for (auto& component : mComponents)
        {
            component->EditorUI();
        }
    }
}

void GameObject::OnCollision(GameObject* gameObject)
{
}

void GameObject::Serialize(rapidjson::Document& doc, rapidjson::Value& value)
{

    rapidjson::Value gameObjectValue(rapidjson::kObjectType);
    for (auto& component : mComponents)
    {
        component->Serialize(doc, gameObjectValue);
    }
    rapidjson::Value name(mName.c_str(), mName.size(), doc.GetAllocator());
    value.AddMember(name, gameObjectValue, doc.GetAllocator());
}
