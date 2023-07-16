#pragma once

#include "Component.h"
#include "TypeIds.h"


namespace AndrewEngine
{
    class GameObject final
    {
    public:
        GameObject() = default;

        void Initialize();
        void Terminate();

        void Update(float deltaTime);
        void DebugUI();

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

    private:

        using Components = std::vector<std::unique_ptr<Component>>;
        Components mComponents;

        std::string mName = "EMPTY";
        bool mInitialized = false;


    };


}
