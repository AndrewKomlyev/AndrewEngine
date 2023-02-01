#include "Precompiled.h"
#include "Camera.h"

#include "GraphicsSystem.h"

using namespace AndrewEngine;
using namespace AndrewEngine::Graphics;

void Camera::SetMode(ProjectionMode mode)
{
	mProjectionMode = mode;
}

void Camera::SetPosition(const AEMath::Vector3& position)
{
	mPosition = position;
}

void Camera::SetDirection(const AEMath::Vector3& direction)
{
	// Prevent setting direction straight up or down
	auto dir = AEMath::Normalize(direction);
	if (AEMath::Abs(AEMath::Dot(dir, AEMath::Vector3::YAxis)) < 0.995f)
		mDirection = dir;
}

void Camera::SetLookAt(const AEMath::Vector3& target)
{
	SetDirection(target - mPosition);
}

void Camera::SetFov(float fov)
{
	constexpr float kMinFov = 10.0f * AEMath::Constants::DegToRad;
	constexpr float kMaxFov = 170.0f * AEMath::Constants::DegToRad;
	mFov = AEMath::Clamp(fov, kMinFov, kMaxFov);
}

void Camera::SetAspectRatio(float ratio)
{
	mAspectRatio = ratio;
}

void Camera::SetSize(float width, float height)
{
	mWidth = width;
	mHeight = height;
}

void Camera::SetNearPlane(float nearPlane)
{
	mNearPlane = nearPlane;
}

void Camera::SetFarPlane(float farPlane)
{
	mFarPlane = farPlane;
}

void Camera::Walk(float distance)
{
	mPosition += mDirection * distance;
}

void Camera::Strafe(float distance)
{
	const AEMath::Vector3 right = AEMath::Normalize(Cross(AEMath::Vector3::YAxis, mDirection));
	mPosition += right * distance;
}

void Camera::Rise(float distance)
{
	mPosition += (AEMath::Vector3::YAxis * distance);
}

void Camera::Yaw(float radian)
{
	AEMath::Matrix4 matRotate = AEMath::Matrix4::RotationY(radian);
	mDirection = AEMath::TransformNormal(mDirection, matRotate);
}

void Camera::Pitch(float radian)
{
	const AEMath::Vector3 right = AEMath::Normalize(Cross(AEMath::Vector3::YAxis, mDirection));
	const AEMath::Matrix4 matRot = AEMath::Matrix4::RotationAxis(right, radian);
	const AEMath::Vector3 newLook = AEMath::TransformNormal(mDirection, matRot);
	SetDirection(newLook);
}

void Camera::Zoom(float amount)
{
	constexpr float minZoom = 170.0f * AEMath::Constants::DegToRad;
	constexpr float maxZoom = 10.0f * AEMath::Constants::DegToRad;
	mFov = AEMath::Clamp(mFov - amount, maxZoom, minZoom);
}

const AEMath::Vector3& Camera::GetPosition() const
{
	return mPosition;
}

const AEMath::Vector3& Camera::GetDirection() const
{
	return mDirection;
}

AEMath::Matrix4 Camera::GetViewMatrix() const
{
	const AEMath::Vector3 l = mDirection;
	const AEMath::Vector3 r = AEMath::Normalize(AEMath::Cross(AEMath::Vector3::YAxis, l));
	const AEMath::Vector3 u = AEMath::Normalize(AEMath::Cross(l, r));
	const float x = -AEMath::Dot(r, mPosition);
	const float y = -AEMath::Dot(u, mPosition);
	const float z = -AEMath::Dot(l, mPosition);

	return
	{
		r.x, u.x, l.x, 0.0f,
		r.y, u.y, l.y, 0.0f,
		r.z, u.z, l.z, 0.0f,
		x,   y,   z,   1.0f
	};
}

AEMath::Matrix4 Camera::GetProjectionMatrix() const
{
	return (mProjectionMode == ProjectionMode::Perspective) ? GetPerspectiveMatrix() : GetOrthographicMatrix();
}

AEMath::Matrix4 Camera::GetPerspectiveMatrix() const
{
	const float a = (mAspectRatio == 0.0f) ? GraphicsSystem::Get()->GetBackBufferAspectRatio() : mAspectRatio;
	const float h = 1.0f / tan(mFov * 0.5f);
	const float w = h / a;
	const float zf = mFarPlane;
	const float zn = mNearPlane;
	const float q = zf / (zf - zn);

	return {
		w,    0.0f, 0.0f,    0.0f,
		0.0f, h,    0.0f,    0.0f,
		0.0f, 0.0f, q,       1.0f,
		0.0f, 0.0f, -zn * q, 0.0f
	};
}

AEMath::Matrix4 Camera::GetOrthographicMatrix() const
{
	const float w = (mWidth == 0.0f) ? GraphicsSystem::Get()->GetBackBufferWidth() : mWidth;
	const float h = (mHeight == 0.0f) ? GraphicsSystem::Get()->GetBackBufferHeight() : mHeight;
	const float f = mFarPlane;
	const float n = mNearPlane;
	return 	{
		2 / w, 0.0f,  0.0f,        0.0f,
		0.0f,  2 / h, 0.0f,        0.0f,
		0.0f,  0.0f,  1 / (f - n), 0.0f,
		0.0f,  0.0f,  n / (n - f), 1.0f
	};
}