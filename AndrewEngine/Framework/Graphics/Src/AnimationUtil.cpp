#include "Precompiled.h"
#include "AnimationUtil.h"
#include "Colours.h"
#include "SimpleDraw.h"

using namespace AndrewEngine;
using namespace AndrewEngine::Graphics;
using namespace AndrewEngine::Graphics::AnimationUtil;

namespace
{
    void ComputeBoneTransformRecursive(const Bone* bone, BoneTransforms& boneTransforms)
    {
        if (bone != nullptr)
        {
            if (bone->parent != nullptr)
            {
                boneTransforms[bone->index] = bone->toParentTransform * boneTransforms[bone->parentIndex];
            }
            else
            {
                boneTransforms[bone->index] = bone->toParentTransform;
            }
            for (auto child : bone->children)
            {
                ComputeBoneTransformRecursive(child, boneTransforms);
            }
        }
    }
}

void AnimationUtil::ComputeBoneTransform(ModelId modelId, BoneTransforms& boneTransforms)
{
    auto model = ModelManager::Get()->GetModel(modelId);
    if (model->skeleton != nullptr)
    {
        boneTransforms.resize(model->skeleton->bones.size(), AEMath::Matrix4::Identity);
        ComputeBoneTransformRecursive(model->skeleton->root, boneTransforms);
    }
}

void AnimationUtil::ApplyBoneOffset(ModelId modelId, BoneTransforms& boneTransforms)
{
    auto model = ModelManager::Get()->GetModel(modelId);
    if (model->skeleton != nullptr)
    {
        for (auto& bone : model->skeleton->bones)
        {
            boneTransforms[bone->index] = bone->toParentTransform * boneTransforms[bone->parentIndex];
        }
    }
}

void AnimationUtil::DrawSkeleton(ModelId modelId, BoneTransforms& boneTransforms)
{
    auto model = ModelManager::Get()->GetModel(modelId);
    if (model->skeleton != nullptr)
    {
        for (auto& bone : model->skeleton->bones)
        {
            if (bone->parent != nullptr)
            {
                const auto posA = AEMath::GetTranslation(boneTransforms[bone->index]);
                const auto posB = AEMath::GetTranslation(boneTransforms[bone->parentIndex]);
                SimpleDraw::AddLine(posA, posB, Colors::HotPink);
            }
        }
    }
}