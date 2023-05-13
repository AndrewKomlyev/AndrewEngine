#pragma once
#include "ModelManager.h"

namespace AndrewEngine::Graphics::AnimationUtil
{
    using BoneTransforms = std::vector<AEMath::Matrix4>;

    void ComputeBoneTransform(ModelId modelId, BoneTransforms& boneTransforms);
    void ApplyBoneOffset(ModelId modelId, BoneTransforms& boneTransforms);
    void DrawSkeleton(ModelId modelId, BoneTransforms& boneTransforms);
}