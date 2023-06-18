#pragma once

namespace AndrewEngine::AEMath
{
    struct  Vector4
    {
        union { float x; float r; };
        union { float y; float g; };
        union { float z; float b; };
        union { float w; float a; };

        constexpr Vector4() : Vector4(0.0f) {}
        constexpr Vector4(float n) noexcept : Vector4(n, n, n, n) {}
        constexpr Vector4(float x, float y, float z, float w) : x{ x }, y{ y }, z{ z }, w{ w } {}

        static const Vector4 Zero;
        static const Vector4 One;
        static const Vector4 XAxis;
        static const Vector4 YAxis;
        static const Vector4 ZAxis;
        static const Vector4 WAxis;

        constexpr Vector4 operator-()
        {
            return Vector4(-x, -y, -z, -w);
        }

        constexpr Vector4 operator+(const Vector4& rhs)
        {
            return Vector4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
        }

        constexpr Vector4 operator-(const Vector4& rhs)
        {
            return Vector4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
        }

        constexpr Vector4 operator*(const Vector4& rhs)
        {
            return Vector4(x * rhs.x, y * rhs.y, z * rhs.z, w * rhs.w);
        }

        constexpr Vector4 operator*(float s)
        {
            return Vector4(x * s, y * s, z * s, w * s);
        }

        constexpr Vector4 operator/(float s)
        {
            if (s != 0)
            {
                return Vector4(x / s, y / s, z / s, w / s);
            }

            return Vector4(x, y, z, w);
        }

        constexpr Vector4& operator+= (const Vector4& v);
        constexpr Vector4& operator-= (const Vector4& v);
        constexpr Vector4& operator*= (const Vector4& v);
        constexpr Vector4& operator*= (float s);
        constexpr Vector4& operator/= (float s);
    };
}