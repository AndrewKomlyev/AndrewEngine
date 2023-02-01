#pragma once

#include "Colours.h"

using namespace AndrewEngine::AEMath;

namespace AndrewEngine::Graphics
{
    class Camera;

    namespace SimpleDraw
    {

        void StaticInitialize(uint32_t msxVertexCount);
        void StaticTerminate();

        void AddLine(const Vector3& v0, const Vector3& v1, const Color& colour);
        void AddFace(const Vector3& v0, const Vector3& v1, const Vector3& v2, const Color& colour);

        void AddAABB(const Vector3& min, const Vector3& max, const Color& colour);
        void AddAABB(float minX, float minY, float minZ, float maxX, float maxY, float maxZ, const Color& colour);

        void AddFillAABB(const Vector3& min, const Vector3& max, const Color& colour);
        void AddFillAABB(float minX, float minY, float minZ, float maxX, float maxY, float maxZ, const Color& colour);

        void AddSphere(int slices, int ring, float radius, const Color& colour);

        void AddGroundPlane(float size, const Color& colour);

        void AddTransform(const Matrix4& m);

        void Render(const Camera& camera);
    }

}
