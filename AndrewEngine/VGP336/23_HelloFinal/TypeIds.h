#pragma once


#include <AndrewEngine/Inc/TypeIds.h>

enum class CustomComponentId
{
    AnimationChangeComponentId = static_cast<uint32_t>(AndrewEngine::ComponentId::Count),
    CharacterControllerComponentId
};

enum class CustomServiceId
{
    AnimationChangeInputServiceId = static_cast<uint32_t>(AndrewEngine::ServiceId::Count)
};