#pragma once

namespace AndrewEngine::AEMath
{
	struct  Vector2
	{
		float x, y;

		constexpr Vector2() : Vector2(0.0f) {}
		constexpr Vector2(float n) noexcept : Vector2(n, n) {}
		constexpr Vector2(float x, float y) : x{ x }, y{ y } {}

		static const Vector2 Zero;
		static const Vector2 One;
		static const Vector2 XAxis;
		static const Vector2 YAxis;

		constexpr Vector2 operator-();
		constexpr Vector2 operator+(const Vector2& rhs);
		constexpr Vector2 operator-(const Vector2& rhd);
		constexpr Vector2 operator*(float s);
		constexpr Vector2 operator/(float s);

		Vector2& operator+= (const Vector2& v);
		Vector2& operator-= (const Vector2& v);
		Vector2& operator*= (float s);
		Vector2& operator/= (float s);
	};


}