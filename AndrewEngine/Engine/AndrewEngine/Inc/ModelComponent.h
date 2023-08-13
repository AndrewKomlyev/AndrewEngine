#pragma once

#include "Component.h"

namespace AndrewEngine
{
    class ModelComponent final : public Component
    {
    public:
        SET_TYPE_ID(ComponentId::ModelComponent);

        void Initialize() override;
        void Terminate() override;

        void SetFileName(const char* fileName) { mFileName = fileName; }

        Graphics::ModelId GetModelId() const { return mModelId; }
        const Graphics::Model& GetModel() const
        {
            return *Graphics::ModelManager::Get()->GetModel(mModelId);
        }

    private:
        std::string mFileName;

        Graphics::ModelId mModelId = 0;
    };
}