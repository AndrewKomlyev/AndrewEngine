#include "Precompiled.h"
#include "CameraComponent.h"
#include "CameraService.h"
#include "GameWorld.h"

using namespace AndrewEngine;

void CameraComponent::Initialize()
{
    auto cameraService = GetOwner().GetWorld().GetService<CameraService>();
    ASSERT(cameraService != nullptr, "CameraComponent: CameraService is not available.");
    cameraService->Register(this);

}

void CameraComponent::Terminate()
{
    auto cameraService = GetOwner().GetWorld().GetService<CameraService>();
    ASSERT(cameraService != nullptr, "CameraComponent: CameraService is not available.");
    cameraService->Unregister(this);
}
