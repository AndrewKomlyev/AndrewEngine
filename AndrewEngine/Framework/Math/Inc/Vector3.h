#pragma once

namespace AndrewEngine::AEMath
{
    struct  Vector3
    {
        float x, y, z;

        constexpr Vector3() : Vector3(0.0f) {}
        constexpr Vector3(float n) noexcept : Vector3(n, n, n) {}
        constexpr Vector3(float x, float y, float z) : x{ x }, y{ y }, z{ z } {}

        static const Vector3 Zero;
        static const Vector3 One;
        static const Vector3 XAxis;
        static const Vector3 YAxis;
        static const Vector3 ZAxis;

        constexpr Vector3 operator-()
        {
            return Vector3(-x, -y, -z);
        }
        constexpr Vector3 operator+(const Vector3& rhs) const
        {
            return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
        }
        constexpr Vector3 operator-(const Vector3& rhd) const
        {
            return Vector3(x - rhd.x, y - rhd.y, z - rhd.z);
        }
        constexpr Vector3 operator*(float s) const
        {
            return Vector3(x * s, y * s, z * s);
        }
        constexpr Vector3 operator/(float s) const
        {
            if (s != 0)
            {
                return Vector3(x / s, y / s, z / s);
            }

            return Vector3(x, y, z);
        }

        Vector3& operator+= (const Vector3& v);
        Vector3& operator-= (const Vector3& v);
        Vector3& operator*= (const float s);
        Vector3& operator/= (const float s);
    };
}