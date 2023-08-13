#pragma once

#include "Common.h"

namespace AndrewEngine
{
    enum class ComponentId
    {
        CameraComponent,
        ColliderComponent,
        FPSCameraControllerComponent,
        MeshComponent,
        ModelComponent,
        RigidBodyComponent,
        TransformComponent,

        Count
    };

    enum class ServiceId
    {
        Camera,
        Render,
        
        Count
    };
}

#define SET_TYPE_ID(id)\
    static uint32_t StaticGetTypeId() {return static_cast<uint32_t>(id);}\
    uint32_t GetTypeId() const override {return StaticGetTypeId();}