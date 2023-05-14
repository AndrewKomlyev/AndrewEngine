#pragma once


#include "Keyframe.h"
#include "Transform.h"

namespace AndrewEngine::Graphics
{


    class Animation
    {
    public:
        AEMath::Vector3 GetPosition(float time) const;
        AEMath::Quaternion GetRotation(float time) const;
        AEMath::Vector3 GetScale(float time) const;

        Transform GetTransform(float time) const;

        float GetDuration() const;

    private:
        friend class AnimationBuilder;
        friend class AnimationIO;

        PositionKeys mPositionKeys;
        RotationKeys mRotationKeys;
        ScaleKeys mScaleKeys;
        float mDuration;
    };
}