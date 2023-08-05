#include "Precompiled.h"
#include "RenderService.h"
#include "ModelComponent.h"
#include "TransformComponent.h"


#include "CameraService.h"
#include "GameWorld.h"

using namespace AndrewEngine;
using namespace AndrewEngine::Graphics;
using namespace AndrewEngine::AEMath;

void RenderService::Initialize()
{
    mCameraService = GetWorld().GetService<CameraService>();

    mDirectionalLight.ambient = { 0.8f, 0.8f, 0.8f, 1.0f };
    mDirectionalLight.diffuse = { 0.7f, 0.7f, 0.7f, 1.0f };
    mDirectionalLight.specular = { 0.7f, 0.7f, 0.7f, 1.0f };

    mStandartEffect.Initialize(L"../../Assets/Shaders/Standard.fx");
    mStandartEffect.SetDireectionalLight(mDirectionalLight);
}

void RenderService::Terminate()
{
    mStandartEffect.Terminate();
}

void RenderService::Update(float deltaTime)
{
}

void RenderService::Render()
{
    const auto& camera = mCameraService->GetMain();
    mStandartEffect.SetCamera(camera);

    mStandartEffect.Begin();
    for (auto& entry : mRenderEntities)
    {
        DrawRenderGroup(mStandartEffect, entry.renderGroup);
    }
    mStandartEffect.End();
}

void RenderService::DebugUI()
{
    ImGui::Text("FPS: %f",mFPS);
    ImGui::Separator();

    if (ImGui::CollapsingHeader("Light", ImGuiTreeNodeFlags_DefaultOpen))
    {
        if (ImGui::DragFloat3("Direction##Light", &mDirectionalLight.direction.x, 0.01f, -1.0f, 1.0f))
        {
            mDirectionalLight.direction = Normalize(mDirectionalLight.direction);
        }
        ImGui::ColorEdit4("Ambient##Light", &mDirectionalLight.ambient.r);
        ImGui::ColorEdit4("Diffuse##Light", &mDirectionalLight.diffuse.r);
        ImGui::ColorEdit4("Specular##Light", &mDirectionalLight.specular.r);
    }

    mStandartEffect.DebugUI();
    mShadowEffect.DebugUI();

    SimpleDraw::Render(mCameraService->GetMain());

}

void AndrewEngine::RenderService::SetDirectionLight(const const AEMath::Vector3& direction)
{
    mDirectionalLight.direction = AEMath::Normalize(direction);
}

void AndrewEngine::RenderService::Register(const ModelComponent* modelComponent)
{
    auto& entry = mRenderEntities.emplace_back();

    auto& gameObject = modelComponent->GetOwner();
    entry.modelComponent = modelComponent;
    entry.transformComponent = gameObject.GetComponent<TransformComponent>();
    entry.renderGroup = CreateRenderGroup(modelComponent->GetModelId());
}

void AndrewEngine::RenderService::Unregister(const ModelComponent* modelComponent)
{
    auto iter = std::find_if(mRenderEntities.begin(), mRenderEntities.end(), [&](const Entry& entry)
        {
            return entry.modelComponent == modelComponent;
        }
    );

    if (iter != mRenderEntities.end())
    {
        auto& entry = *iter;
        CleanupRenderGroup(entry.renderGroup);
        mRenderEntities.erase(iter);
    }
}
