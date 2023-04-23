#pragma once

#include "Common.h"

namespace AndrewEngine::Graphics
{
    enum EaseType
    {
        None,
        EaseIn,
        EaseOut,
        EaseInOut,
        EaseInQuad,
        EaseOutQuad,
        EaseInOutQuad,
    };

    template<class T>
    struct KeyFrame
    {
        KeyFrame() = default;
        KeyFrame(const T& k, float t, EaseType e = EaseType::None) 
            : key(k), time(t), easeType(e)
        {

        }

        T key = T();
        float time = 0.0f;
        EaseType easeType = EaseType::None;
    };


    template<class T>
    using Keyframes = std::vector<KeyFrame<T>>;

    using PositionKeys = Keyframes<AEMath::Vector3>;
    using RotationKeys = Keyframes<AEMath::Quaternion>;
    using ScaleKeys = Keyframes<AEMath::Vector3>;

}