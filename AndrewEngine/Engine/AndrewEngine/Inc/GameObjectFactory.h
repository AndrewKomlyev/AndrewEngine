#pragma once


namespace AndrewEngine
{
    class GameObject;

    using CustomMake = std::function<bool(const char*, const rapidjson::Value&, GameObject&)>;

    namespace GameObjectFactory
    {
        void SetCustomMake(CustomMake customMake);
        void Make(const std::filesystem::path& templateFile, GameObject& gameObject);
    }
}