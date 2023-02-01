#include "Precompiled.h"
#include "Math/Inc/Vector2.h"

using namespace AndrewEngine::AEMath;

const Vector2 Vector2::Zero = Vector2(0.0f);
const Vector2 Vector2::One = Vector2(1.0f);
const Vector2 Vector2::XAxis = Vector2(1.0f, 0.0f);
const Vector2 Vector2::YAxis = Vector2(0.0f, 1.0f);


constexpr Vector2 Vector2::operator-()
{
	return Vector2(-x, -y);
}

constexpr Vector2 Vector2::operator+(const Vector2& rhs)
{
	return Vector2(x + rhs.x, y + rhs.y);
}

constexpr Vector2 Vector2::operator-(const Vector2& rhs)
{
	return Vector2(x - rhs.x, y - rhs.y);
}

constexpr Vector2 Vector2::operator*(float s)
{
	return Vector2(x * s, y * s);
}

constexpr Vector2 Vector2::operator/(float s)
{
	if (s != 0)
	{
		return Vector2(x / s, y / s);
	}

	return Vector2(x, y);
}

Vector2& Vector2::operator+= (const Vector2& v)
{
	x += v.x;
	y += v.y;
	return *this;
}

Vector2& Vector2::operator-= (const Vector2& v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}

Vector2& Vector2::operator*= (float s)
{
	x *= s;
	y *= s;
	return *this;
}

Vector2& Vector2::operator/= (float s)
{
	x /= s;
	y /= s;
	return *this;
}