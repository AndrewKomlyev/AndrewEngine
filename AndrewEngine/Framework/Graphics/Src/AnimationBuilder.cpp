#include "Precompiled.h"
#include "AnimationBuilder.h"

using namespace AndrewEngine;
using namespace AndrewEngine::Graphics;
using namespace AndrewEngine::AEMath;

namespace
{
    template<class T>
    inline void PushKey(Keyframes<T>& keyframes, const T& value, float time, EaseType easeType)
    {
        ASSERT(keyframes.empty() || keyframes.back().time < time, "AnimationBuilder -- Cannot add Keyframe back in time");
        keyframes.emplace_back(value, time, easeType);
    }
}

AnimationBuilder& AnimationBuilder::AddPositionKey(const AEMath::Vector3& position, float time, EaseType easeType)
{
    PushKey(mWorkingCopy.mPositionKeys, position, time, easeType);
    mWorkingCopy.mDuration = Max(mWorkingCopy.mDuration, time);
    return *this;
}

AnimationBuilder& AnimationBuilder::AddRotationKey(const AEMath::Quaternion& rotation, float time, EaseType easeType)
{
    PushKey(mWorkingCopy.mRotationKeys, rotation, time, easeType);
    mWorkingCopy.mDuration = Max(mWorkingCopy.mDuration, time);
    return *this;
}

AnimationBuilder& AnimationBuilder::AddScaleKey(const AEMath::Vector3& scale, float time, EaseType easeType)
{
    PushKey(mWorkingCopy.mScaleKeys, scale, time, easeType);
    mWorkingCopy.mDuration = Max(mWorkingCopy.mDuration, time);
    return *this;
}

Animation AnimationBuilder::Build()
{
    ASSERT(!mWorkingCopy.mPositionKeys.empty() || !mWorkingCopy.mRotationKeys.empty() || mWorkingCopy.mScaleKeys.empty(), "AnimationBuilder -- Animation Keys are empty");
    //ASSERT(mWorkingCopy.mDuration > 0.0f, "Animation -- no key times");
    return std::move(mWorkingCopy);
}
