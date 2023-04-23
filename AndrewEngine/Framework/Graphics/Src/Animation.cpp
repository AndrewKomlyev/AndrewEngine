#include "Precompiled.h"
#include "Animation.h"

using namespace AndrewEngine;
using namespace AndrewEngine::Graphics;
using namespace AndrewEngine::AEMath;

namespace
{
    float GetLerpTime(float startTime, float endTime, float time, EaseType easeType)
    {
        float t = (time - startTime) / (endTime - startTime);
        switch (easeType)
        {
        case None:

            break;
        case EaseIn:
            //t = t * t;
            break;
        case EaseOut:

            break;
        case EaseInOut:
            
            break;
        case EaseInQuad:
            t = t * t;
            break;
        case EaseOutQuad:
            t = -t * (t - 2.0f);
            break;
        case EaseInOutQuad:
        {
            t *= 2.0f;
            if (t < 1.0f)
            {
                t = 0.5f * t * t;
                break;
            }
            t -= 1.0f;
            t = -0.5f * ((t * (t - 2.0f)) - 1.0f);
        }
            break;
        default:
            break;
        }
        return t;
    }
}


Vector3 Animation::GetPosition(float time) const
{
    if (mPositionKeys.size() == 1)
    {
        return mPositionKeys[0].key;
    }

    for (int  i = 0; i < mPositionKeys.size(); ++i)
    {
        if (time < mPositionKeys[i].time)
        {
            if (i > 0)
            {
                float lerpTime = GetLerpTime(mPositionKeys[i - 1].time, mPositionKeys[i].time, time, mPositionKeys[i].easeType);
                return Lerp(mPositionKeys[i - 1].time, mPositionKeys[i].time, lerpTime);
            }

            return mPositionKeys[i].key;
        }
    }

    return Vector3::Zero;
}

Quaternion Animation::GetRotation(float time) const
{
    if (mRotationKeys.size() == 1)
    {
        return mRotationKeys[0].key;
    }

    for (int i = 0; i < mRotationKeys.size(); i)
    {
        if (time < mRotationKeys[i].time)
        {
            if (i > 0)
            {
                float lerpTime = GetLerpTime(mRotationKeys[i - 1].time, mRotationKeys[i].time, time, mRotationKeys[i].easeType );
                return Quaternion::Slerp(mRotationKeys[i - 1].key, mRotationKeys[i].key, lerpTime);
            }

            return mRotationKeys[i].key;
        }
    }

    return Quaternion::Zero;
}

Vector3 Animation::GetScale(float time) const
{
    if (mScaleKeys.size() == 1)
    {
        return mScaleKeys[0].key;
    }

    for (int i = 0; i < mScaleKeys.size(); i)
    {
        if (time < mScaleKeys[i].time)
        {
            if (i > 0)
            {
                float lerpTime = GetLerpTime(mScaleKeys[i - 1].time, mScaleKeys[i].time, time, mScaleKeys[i].easeType);
                return Lerp(mScaleKeys[i - 1].time, mScaleKeys[i].time, lerpTime);
            }

            return mScaleKeys[i].key;
        }
    }

    return Vector3::One;
}

Transform Animation::GetTransform(float time) const
{

    Transform transform;

    transform.position = GetPosition(time);
    transform.rotation = GetRotation(time);
    transform.scale = GetScale(time);
    return transform;
}

float Animation::GetDuration() const
{
    return mDuration;
}
