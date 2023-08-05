#pragma once

#include "Common.h"

namespace AndrewEngine
{
    enum class ComponentId
    {
        Transform,
        Camera,
        FPSCameraController,
        Model,

        Count
    };

    enum class ServiceId
    {
        Camera,
        Render,
        Physics,
        

        Count
    };
}

#define SET_TYPE_ID(id)\
    static uint32_t StaticGetTypeId() {return static_cast<uint32_t>(id);}\
    uint32_t GetTypeId() const override {return StaticGetTypeId();}