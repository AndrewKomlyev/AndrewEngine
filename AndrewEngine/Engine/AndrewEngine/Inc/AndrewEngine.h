#pragma once

#include "Common.h"
#include "App.h"
#include "AppState.h"
#include "Component.h"
#include "GameObject.h"
#include "GameObjectFactory.h"
#include "GameObjectHandle.h"
#include "GameWorld.h"
#include "Services.h"
#include "TypeIds.h"

#include "CameraComponent.h"
#include "FPSCameraControllerComponent.h"
#include "ModelComponent.h"
#include "TransformComponent.h"

#include "CameraService.h"
#include "RenderService.h"
namespace AndrewEngine
{
    App& MainApp();
}