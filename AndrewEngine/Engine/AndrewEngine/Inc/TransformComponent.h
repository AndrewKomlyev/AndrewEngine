#pragma once

#include "Component.h"

namespace AndrewEngine
{
    class TransformComponent final
        : public Component
        , public Graphics::Transform
    {
    public:
        SET_TYPE_ID(ComponentId::TransformComponent);

        void DebugUI() override;
        void EditorUI() override;

        void Serialize(rapidjson::Document& doc, rapidjson::Value& value) override;


    };
}