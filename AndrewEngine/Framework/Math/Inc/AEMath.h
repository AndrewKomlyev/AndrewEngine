#pragma once
#include "Common.h"

namespace AndrewEngine::AEMath
{
    inline float MagnitudeSqr(const Vector3& v)
    {
        return v.x * v.x + v.y * v.y + v.z * v.z;
    }
    inline float Magnitude(const Vector3& v)
    {
        return sqrtf(MagnitudeSqr(v));
    }
    inline Vector3 Normalize(const Vector3& v)
    {
        return (v) / Magnitude(v);
    }
    


    template <typename T> inline T Min(T a, T b)
    {
        return (a > b) ? b : a;
    }
    template <typename T> inline T Max(T a, T b)
    {
        return (a < b) ? b : a;
    }
    template <typename T> inline T Clamp(T v, T min, T max)
    {
        return Max(min, Min(max, v));
    }
    template <typename T> inline T Lert(T a, T b, float t)
    {
        return a + ((b - a) * t);
    }
    template <typename T> inline T Abs(T v)
    {
        return (v >= 0) ? v : -v;
    }
    //Vector2
    inline float Dot(const Vector2& a, const Vector2& b)
    {
        return (a.x * b.x) + (a.y * b.y);
    }
    inline float DistanceSqr(const Vector2& a, const Vector2& b)
    {
        return ((a.x - b.x) * (a.x - b.x)) + ((a.y - b.y) * (a.y - b.y));
    }

    //Vector3
    inline float Dot(const Vector3& a, const Vector3& b)
    {
        return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
    }
    inline Vector3 Cross(const Vector3& a, const Vector3& b)
    {
        return Vector3((a.y * b.y) - (a.z * b.y), (a.z * b.x) - (a.x * b.z), (a.x * b.y) - (a.y * b.x));
    }
    inline float DistanceSqr(const Vector3& a, const Vector3& b)
    {
        return ((a.x - b.x) * (a.x - b.x)) + ((a.y - b.y) * (a.y - b.y)) + ((a.z - b.z) * (a.z - b.z));
    }
    inline float Distance(const Vector3& a, const Vector3& b)
    {
        return sqrt(DistanceSqr(a, b));
    }
    inline Vector3 TransformCoord(const Vector3& a, const Matrix4& b)
    {
        float x = a.x * b._11 + a.y * b._21 + a.z * b._31 + b._41;
        float y = a.x * b._12 + a.y * b._22 + a.z * b._32 + b._42;
        float z = a.x * b._13 + a.y * b._23 + a.z * b._33 + b._43;

        return { x,y,z };
    }
    inline Vector3 TransformNormal(const Vector3& a, const Matrix4& b)
    {
        float x = a.x * b._11 + a.y * b._21 + a.z * b._31;
        float y = a.x * b._12 + a.y * b._22 + a.z * b._32;
        float z = a.x * b._13 + a.y * b._23 + a.z * b._33;

        return { x,y,z };
    }
    

    
    //Vector4
    inline float Dot(const Vector4& a, const Vector4& b)
    {
        return (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
    }


    //Matrix4
    inline Matrix4 Matrix4::RotationAxis(const Vector3& axis, float rad)
    {
        const Vector3 u = Normalize(axis);
        const float x = u.x;
        const float y = u.y;
        const float z = u.z;
        const float s = sin(rad);
        const float c = cos(rad);
        return
        {
            c + (x * x * (1.0f - c)),
            x * y * (1.0f - c) + z * s,
            x * z * (1.0f - c) - y * s,
            0.0f,

            x * y * (1.0f - c) - z * s,
            c + (y * y * (1.0f - c)),
            y * z * (1.0f - c) + x * s,
            0.0f,

            x * z * (1.0f - c) + y * s,
            y * z * (1.0f - c) - x * s,
            c + (z * z * (1.0f - c)),
            0.0f,

            0.0f, 0.0f, 0.0f, 0.0f
        };
    }

    inline Matrix4 Transpose(const Matrix4& m)
    {
        return Matrix4
        (
            m._11, m._21, m._31, m._41,
            m._12, m._22, m._32, m._42,
            m._13, m._23, m._33, m._43,
            m._14, m._24, m._34, m._44
        );
    }
}