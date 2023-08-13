#pragma once

#include "Services.h"

namespace AndrewEngine
{
    class CameraService;
    class MeshComponent;
    class ModelComponent;
    class TransformComponent;

    class RenderService final : public Service
    {
    public:
        SET_TYPE_ID(ServiceId::Render);

        void Initialize() override;
        void Terminate() override;
        void Update(float deltaTime) override;
        void Render() override;
        void DebugUI() override;

        void SetDirectionLight(const const AEMath::Vector3& direction);
    private: 

        friend class MeshComponent;

        void Register(const MeshComponent* meshComponent);
        void Unregister(const MeshComponent* meshComponent);

        friend class ModelComponent;

        void Register(const ModelComponent* modelComponent);
        void Unregister(const ModelComponent* modelComponent);

        struct Entry
        {
            const MeshComponent* meshComponent = nullptr;
            const ModelComponent* modelComponent = nullptr;
            const TransformComponent* transformComponent = nullptr;
            Graphics::RenderGroup renderGroup;
        };

        using RenderEntities = std::vector<Entry>;
        RenderEntities mRenderEntities;

        const CameraService* mCameraService = nullptr;

        Graphics::DirectionalLight mDirectionalLight;
        Graphics::StandardEffect mStandartEffect;
        Graphics::ShadowEffect mShadowEffect;;

        float mFPS = 0.0f;
    };
}