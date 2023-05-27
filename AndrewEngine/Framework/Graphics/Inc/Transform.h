#pragma once
#include "Common.h"

namespace AndrewEngine::Graphics
{
    struct Transform
    {
        AEMath::Vector3 position = AEMath::Vector3::Zero;
        AEMath::Quaternion rotation = AEMath::Quaternion::Identity;
        AEMath::Vector3 scale = AEMath::Vector3::One;

        Transform() = default;
        Transform(AEMath::Matrix4 m)
        {
            position = AEMath::GetTranslation(m);
            rotation = AEMath::Quaternion::CreateFromRotationMatrix(m);
            scale = AEMath::GetScale(m);
        }

        AEMath::Matrix4 GetMatrix4() const
        {
            return
            {
                AEMath::Matrix4::Scaling(scale) *
                AEMath::Matrix4::MatrixRotationQuaternion(rotation) *
                AEMath::Matrix4::Translation(position)
            };
        }
    };
}
