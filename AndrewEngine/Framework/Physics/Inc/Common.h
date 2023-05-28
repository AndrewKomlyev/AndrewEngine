#pragma once
#include <Math/Inc/AEMath.h>
#include <Core/Inc/Core.h>
#include <Graphics/Inc/Transform.h>
#include <Graphics/Inc/Colours.h>

#include <Bullet/btBulletCollisionCommon.h>
#include <Bullet/btBulletDynamicsCommon.h>

template<class T>
inline void SafeDelete(T*& ptr)
{
    if (ptr)
    {
        delete ptr;
        ptr = nullptr;
    }
}

inline AndrewEngine::AEMath::Vector3 ConvertToVector3(const btVector3& vec)
{
    return { vec.x(), vec.y(), vec.z() };
}

inline btVector3 ConvertTobtVector3(const AndrewEngine::AEMath::Vector3& vec)
{
    return { vec.x, vec.y, vec.z };
}

inline btQuaternion ConvertTobtQuaternion(const AndrewEngine::AEMath::Quaternion& q)
{
    return { q.x, q.y, q.z, q.w };
}

inline AndrewEngine::AEMath::Quaternion ConvertToQuaternion(const btQuaternion& q)
{
    return { q.x(), q.y(), q.z(), q.w() };
}

inline AndrewEngine::Color ConvertToColour(const btVector3& btColor)
{
    return { btColor.x(), btColor.y(), btColor.z(), 1.0f };
}

inline btTransform ConvertTobtTransform(const AndrewEngine::Graphics::Transform& trans)
{
    return btTransform(btQuaternion(trans.rotation.x, trans.rotation.y, trans.rotation.z, trans.rotation.w),
        btVector3(trans.position.x, trans.position.y, trans.position.z));
}

inline AndrewEngine::Graphics::Transform ConvertToTransform(const btTransform& trans)
{
    const auto& origin = trans.getOrigin();
    const auto& rotation = trans.getRotation();
    AndrewEngine::Graphics::Transform retTrans;
    retTrans.position = ConvertToVector3(origin);
    retTrans.rotation = ConvertToQuaternion(rotation);
    return retTrans;
}

inline void ApplybtTransformToTransform(const btTransform& btTrans, AndrewEngine::Graphics::Transform& trans)
{
    trans.position = ConvertToVector3(btTrans.getOrigin());
    trans.rotation = ConvertToQuaternion(btTrans.getRotation());
}