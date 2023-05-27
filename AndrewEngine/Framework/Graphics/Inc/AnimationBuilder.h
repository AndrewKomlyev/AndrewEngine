#pragma once
#include "Animation.h"

namespace AndrewEngine::Graphics
{
    class AnimationBuilder
    {
    public:
        AnimationBuilder& AddPositionKey(const AEMath::Vector3& position, float time, EaseType easeType = EaseType::None);
        AnimationBuilder& AddRotationKey(const AEMath::Quaternion& rotation, float time, EaseType easeType = EaseType::None);
        AnimationBuilder& AddScaleKey(const AEMath::Vector3& scale, float time, EaseType easeType = EaseType::None);

        [[nodiscard]] Animation Build();

    private:
        Animation mWorkingCopy;
    };
}
