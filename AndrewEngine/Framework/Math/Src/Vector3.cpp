#include "Precompiled.h"
#include "Math/Inc/Vector3.h"

using namespace AndrewEngine::AEMath;

const Vector3 Vector3::Zero= Vector3(0.0f);
const Vector3 Vector3::One = Vector3(1.0f);
const Vector3 Vector3::XAxis = Vector3(1.0f, 0.0f, 0.0f);
const Vector3 Vector3::YAxis = Vector3(0.0f, 1.0f, 0.0f);
const Vector3 Vector3::ZAxis = Vector3(0.0f, 0.0f, 1.0f);

//constexpr Vector3 Vector3::operator-()
//{
//	return Vector3(-x, -y, -z);
//}
//
//constexpr Vector3 Vector3::operator+(const Vector3& rhs) const
//{
//	return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
//}
//
//constexpr Vector3 Vector3::operator-(const Vector3& rhs) const
//{
//	return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
//}

//constexpr Vector3 Vector3::operator*(float s) const 
//{
//	return Vector3(x * s, y * s, z * s);
//} 

//constexpr Vector3 Vector3::operator/(float s) const
//{
//	if (s != 0)
//	{
//		return Vector3(x / s, y / s, z / s);
//	}
//	
//	return Vector3(x, y, z);
//}

Vector3& Vector3::operator+= (const Vector3& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

Vector3& Vector3::operator-= (const Vector3& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

Vector3& Vector3::operator*= (const float s)
{
	x *= s;
	y *= s;
	z *= s;
	return *this;
}

Vector3& Vector3::operator/= (const float s)
{
	x /= s;
	y /= s;
	z /= s;
	return *this;
}