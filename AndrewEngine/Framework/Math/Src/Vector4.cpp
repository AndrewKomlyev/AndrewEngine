#include "Precompiled.h"
#include "Math/Inc/Vector4.h"

using namespace AndrewEngine::AEMath;

const Vector4 Vector4::Zero = Vector4(0.0f);
const Vector4 Vector4::One = Vector4(1.0f);
const Vector4 Vector4::XAxis = Vector4(1.0f, 0.0f, 0.0f, 0.0f);
const Vector4 Vector4::YAxis = Vector4(0.0f, 1.0f, 0.0f, 0.0f);
const Vector4 Vector4::ZAxis = Vector4(0.0f, 0.0f, 1.0f, 0.0f);
const Vector4 Vector4::WAxis = Vector4(0.0f, 0.0f, 0.0f, 1.0f);

constexpr Vector4 Vector4::operator-()
{
	return Vector4(-x, -y, -z, -w);
}

constexpr Vector4 Vector4::operator+(const Vector4& rhs)
{
	return Vector4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
}

constexpr Vector4 Vector4::operator-(const Vector4& rhs)
{
	return Vector4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
}

constexpr Vector4 Vector4::operator*(const Vector4& rhs)
{
	return Vector4(x * rhs.x, y * rhs.y, z * rhs.z, w * rhs.w);
}

constexpr Vector4 Vector4::operator*(float s)
{
	return Vector4(x * s, y * s, z * s, w * s);
}

constexpr Vector4 Vector4::operator/(float s)
{
	if (s != 0)
	{
		return Vector4(x / s, y / s, z / s, w / s);
	}

	return Vector4(x, y, z, w);
}

constexpr Vector4& Vector4::operator+= (const Vector4& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	w += v.w;

	return *this;
}

constexpr Vector4& Vector4::operator-= (const Vector4& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	w -= v.w;
	return *this;
}

constexpr Vector4& Vector4::operator*= (const Vector4& v)
{
	x *= v.x;
	y *= v.y;
	z *= v.z;
	w *= v.w;
	return *this;
}

constexpr Vector4& Vector4::operator*= (float s)
{
	x *= s;
	y *= s;
	z *= s;
	w *= s;
	return *this;
}

constexpr Vector4& Vector4::operator/= (float s)
{
	x /= s;
	y /= s;
	z /= s;
	w /= s;
	return *this;
}