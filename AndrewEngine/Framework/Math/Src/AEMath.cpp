#include "Precompiled.h"
#include "Math/Inc/AEMath.h"

using std::sqrtf;

using namespace AndrewEngine::AEMath;

//Vector2

//Vector3

//Vector4

const Matrix4 Matrix4::Zero
({
  0,0,0,0,
  0,0,0,0,
  0,0,0,0,
  0,0,0,0
    });
const Matrix4 Matrix4::Identity
({
  1,0,0,0,
  0,1,0,0,
  0,0,1,0,
  0,0,0,1
    });

const Quaternion Quaternion::Identity = { 0.f, 0.f, 0.f, 1.f };
const Quaternion Quaternion::Zero = { 0.f, 0.f, 0.f, 0.f };