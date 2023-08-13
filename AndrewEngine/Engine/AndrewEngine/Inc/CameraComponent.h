#pragma once

#include "Component.h"

namespace AndrewEngine
{
    class CameraComponent final : public Component
    {
    public:

        SET_TYPE_ID(ComponentId::CameraComponent);

        void Initialize() override;
        void Terminate() override;

        Graphics::Camera& GetCamera() { return mCamera; }
        const Graphics::Camera& GetCamera() const { return mCamera; }

    private:
        Graphics::Camera mCamera;
    };
}
