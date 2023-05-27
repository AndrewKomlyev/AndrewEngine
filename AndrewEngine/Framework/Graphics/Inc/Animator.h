#pragma once

#include "ModelManager.h"
#include "Bone.h"

namespace AndrewEngine::Graphics
{
    class BlendNode
    {
    public:
        void PlayAnimation(ModelId id, int clipIndex, bool looping);
        void Update(float deltaTime);
        bool GetToParentTransform(const Bone* bone, Transform& transform)const;

        bool IsFinished() const;
        float GetAnimationTick() const { return mAnimationTick; }
        bool IsLooping() const { return mLooping; }
        int GetClipIndex() const { return mClipIndex; }

        BlendNode() = default;
        BlendNode(BlendNode&) = delete;
        BlendNode& operator=(BlendNode&) = delete;

        BlendNode(BlendNode&& rhs);
        BlendNode& operator=(BlendNode&& rhs)
        {
            mModelId = rhs.mModelId;
            mClipIndex = rhs.mClipIndex;
            mAnimationTick = rhs.mAnimationTick;
            mLooping = rhs.mLooping;

            rhs.mModelId = 0;
            rhs.mClipIndex = -1;
            rhs.mAnimationTick = 0.0f;
            rhs.mLooping = false;
            return *this;
        }

    private:
        ModelId mModelId = 0;
        int mClipIndex = -1;
        float mAnimationTick = 0.0f;
        bool mLooping = false;
    };

    class Animator
    {
    public:
        void Initialize(ModelId id);
        void PlayAnimation(int clipIndex, bool looping, float blendDuration = 0.0f);
        void Update(float deltaTime);
        bool IsFinished();
        size_t GetAnimationCount() const;
        AEMath::Matrix4 GetToParentTransform(const Bone* bone) const;
    private:
        ModelId mModelId = 0;
        float mBlendDuration = -1.0f;
        float mBlendTime = -1.0f;

        BlendNode mCurrentAnimation;
        BlendNode mNextAnimation;
    };
}