#pragma once

#include "Component.h"
#include "TypeIds.h"
#include "GameObjectHandle.h"


namespace AndrewEngine
{
    class GameWorld;
    class GameObject final
    {
    public:
        GameObject() = default;

        void Initialize();
        void Terminate();

        void Update(float deltaTime);
        void DebugUI();
        void EditorUI();

        void OnCollision(GameObject* gameObject);

        template<class ComponentType>
        ComponentType* AddComponent()
        {
            ASSERT(!mInitialized, "GameObject: cannot add component after gameObject is Initalized");
            auto& newComponent = mComponents.emplace_back(std::make_unique<ComponentType>());
            newComponent->mOwner = this;
            return static_cast<ComponentType*>(newComponent.get());
        }

        template<class ComponentType>
        ComponentType* GetComponent()
        {
            //auto constThis = static_cast<const GameObjecy*>(this);
            //return const_cast<Component*>(constThis->GetComponent<ComponentType>());
            for (auto& component : mComponents)
            {
                if (component->GetTypeId() == ComponentType::StaticGetTypeId())
                {
                    return static_cast<ComponentType*>(component.get());
                }
            }
            return nullptr;
        }

        template<class ComponentType>
        const ComponentType* GetComponent() const
        {
            for (auto& component : mComponents)
            {
                if (component->GetTypeId() == ComponentType::StaticGetTypeId())
                {
                    return static_cast<ComponentType*>(component.get());
                }
            }
        }


        void SetName(const char* name) { mName = name; }
        const std::string& GetName() const { return mName; }

        GameWorld& GetWorld() { return *mWorld; }
        const GameWorld& GetWorld() const { return *mWorld; }
        const GameObjectHandle& GetHandle() const { return mHandle; }

        uint32_t GetUniqueId() const { return mUniqueId; }

        void Serialize(rapidjson::Document& doc, rapidjson::Value& value);

    private:
        friend class GameWorld;
        GameWorld* mWorld = nullptr;
        GameObjectHandle mHandle;

        using Components = std::vector<std::unique_ptr<Component>>;
        Components mComponents;


        std::string mName = "EMPTY";
        std::string mTemplate = "template_file.json";
        bool mInitialized = false;
        uint32_t mUniqueId = 0;

    };


}
