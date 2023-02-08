#pragma once

namespace AndrewEngine::Graphics
{
    struct Model;
    
    namespace ModelIO
    {
        void SaveModel(std::filesystem::path filePath, const Model& model);
        void LoadModel(std::filesystem::path filePath, Model& model);

        void SaveMaterial(std::filesystem::path filePath, const Model& model);
        void LoadMaterial(std::filesystem::path filePath, Model& model);
    }
}