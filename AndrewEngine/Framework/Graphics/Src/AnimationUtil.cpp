#include "Precompiled.h"
#include "AnimationUtil.h"
#include "Colours.h"
#include "SimpleDraw.h"
#include "Animator.h"

using namespace AndrewEngine;
using namespace AndrewEngine::Graphics;
using namespace AndrewEngine::Graphics::AnimationUtil;

namespace
{
    void ComputeBoneTransformRecursive(const Bone* bone, BoneTransforms& boneTransforms, const Animator* animator = nullptr)
    {
        if (bone != nullptr)
        {
            if (bone->parent != nullptr)
            {
                if (animator != nullptr)
                {
                    boneTransforms[bone->index] = animator->GetToParentTransform(bone) * boneTransforms[bone->parentIndex];
                }
                else
                {
                    boneTransforms[bone->index] = bone->toParentTransform * boneTransforms[bone->parentIndex];
                }
            }
            else
            {
                boneTransforms[bone->index] = bone->toParentTransform;
            }
            for (auto child : bone->children)
            {
                ComputeBoneTransformRecursive(child, boneTransforms, animator);
            }
        }
    }
}

void AnimationUtil::ComputeBoneTransform(ModelId modelId, BoneTransforms& boneTransforms, const Animator* animator)
{
    auto model = ModelManager::Get()->GetModel(modelId);
    if (model->skeleton != nullptr)
    {
        boneTransforms.resize(model->skeleton->bones.size(), AEMath::Matrix4::Identity);
        ComputeBoneTransformRecursive(model->skeleton->root, boneTransforms, animator);
    }
}

void AnimationUtil::ApplyBoneOffset(ModelId modelId, BoneTransforms& boneTransforms)
{
    auto model = ModelManager::Get()->GetModel(modelId);
    if (model->skeleton != nullptr)
    {
        for (auto& bone : model->skeleton->bones)
        {
            boneTransforms[bone->index] = bone->offsetTransform * boneTransforms[bone->index];
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