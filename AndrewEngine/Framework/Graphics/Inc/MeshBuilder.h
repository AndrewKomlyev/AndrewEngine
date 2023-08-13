#pragma once
#include "MeshTypes.h"

namespace AndrewEngine::Graphics
{
    class MeshBuilder
    {
    public:

        static MeshPC CreateCubePC(float size, Color colour);
        static MeshPC CreateRectanglePC(float width, float height, float depth);
        static MeshPC CreatePlanePC(int numRows, int numColumns, float spacing);
        static MeshPC CreateCylinderPC(int slices, int rings);
        static MeshPC CreateSpherePC(int slices, int rings, float radius);

        static MeshPX CreateCubePX(float size);
        static MeshPX CreateSpherePX(int slices, int rings, float radius);

        static Mesh CreateCube(float size);
        static Mesh CreateSphere(int slices, int rings, float radius);
        static Mesh CreatePlane(int numRows, int numColumns, float spacing);

        static MeshPX CreateScreenQuad();
    };
}