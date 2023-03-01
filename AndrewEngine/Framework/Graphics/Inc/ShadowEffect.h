#pragma once

#include "Camera.h"
#include "ConstantBuffer.h"
#include "LightTypes.h"
#include "PixelShader.h"
#include "VertexShader.h"
#include  "RenderTarget.h"

namespace AndrewEngine::Graphics
{
    class RenderObject;

    class ShadowEffect
    {
    public:
        void Initialize();
        void Terminate();

        void Begin();
        void End();

        void Render(const RenderObject& renderObject);

        void SetDirectionalLight(const DirectionalLight& directionalLight);

        void SetFocus(const AEMath::Vector3& focusPosition) { mFocusPosition = focusPosition; }
        void SetSize(float size) { mSize = size; }

        const Camera& GetLightCamera() const { return mLightCamera; }
        const Texture& GetDepthMap() const { return mDepthRenderTarget; }

        void DebugUI();
    private:
        void UpdateLightCamera();

        struct TransformData
        {
            AEMath::Matrix4 wvp;
        };
        using TransformBuffer = TypeConstantBuffer<TransformData>;

        TransformBuffer mTransformBuffer;
        VertexShader mVertexShader;
        PixelShader mPixelShader;

        const DirectionalLight* mDirectionalLight = nullptr;

        Camera mLightCamera;
        RenderTarget mDepthRenderTarget;

        AEMath::Vector3 mFocusPosition;
        float mSize;
    };


}