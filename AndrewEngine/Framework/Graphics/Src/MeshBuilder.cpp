#include "Precompiled.h"
#include "MeshBuilder.h"

using namespace AndrewEngine;
using namespace AndrewEngine::Graphics;

namespace
{
    Color GetNextColor(int& index)
    {
        constexpr Color colorTable[] = {
        Colors::DarkMagenta,
        Colors::LightSkyBlue,
        Colors::Coral,
        Colors::Red,
        Colors::Green,
        Colors::Yellow,
        Colors::DarkCyan,
        Colors::Snow,
        };

        index = (index + 1) % static_cast<int>(std::size(colorTable));
        return colorTable[index];
    }

    void CreateCubeIndicies(std::vector<uint32_t>& indicies)
    {
        indicies =
        {
            0,1,3,
            1,2,3,

            5,4,7,
            5,7,6,

            1,5,2,
            5,6,2,

            4,0,3,
            4,3,7,

            0,4,1,
            4,5,1,

            6,7,3,
            6,3,2
        };
    }




    void CreatePlaneIndicies(std::vector<uint32_t>& indicies, int rows, int collums)
    {
        for (int r = 0; r < rows; ++r)
        {
            for (int c = 0; c < collums; ++c)
            {
                int i = r * (collums + 1) + c;
                indicies.push_back(i);
                indicies.push_back(i + collums + 1);
                indicies.push_back(i + 1);


                indicies.push_back(i + 1);
                indicies.push_back(i + collums + 1);
                indicies.push_back(i + collums + 2);
            }
        }
    }

    void CreateCapsIndicies(std::vector<uint32_t>& indicies, int slices, int topIndex)
    {
        for (int s = 0; s < slices; ++s)
        {
            uint32_t bottomIndex = topIndex + 1;

            // bottom triangle
            indicies.push_back(s);
            indicies.push_back(s + 1);
            indicies.push_back(bottomIndex);

            // top triangle
            int topRow = topIndex - slices - 1 + s;
            indicies.push_back(topIndex);
            indicies.push_back(topRow + 1);
            indicies.push_back(topRow);
        }
    }

    void CreateCapsPC(MeshPC& mesh, int slices, float halfHeight)
    {
        // Caps
        int index = rand() % 100;
        uint32_t topIndex = mesh.vertices.size();
        uint32_t bottomIndex = topIndex + 1;

        // top center
        mesh.vertices.push_back({ {0.0f, halfHeight, 0.0f}, GetNextColor(index) });
        // bottom center
        mesh.vertices.push_back({ {0.0f, -halfHeight, 0.0f}, GetNextColor(index) });
        CreateCapsIndicies(mesh.indicies, slices, topIndex);
    }
}

Mesh MeshBuilder::CreatePlane(int numRows, int numColumns, float spacing)
{
    Mesh mesh;
    int index = rand() % 100;

    const float halfPlaneWidth = static_cast<float>(numColumns) * spacing * 0.5f;
    const float halfPlaneHeight = static_cast<float>(numRows) * spacing * 0.5f;

    float x = -halfPlaneWidth;
    float z = -halfPlaneHeight;

    const float uStep = 1.0f / static_cast<float>(numColumns);
    const float vStep = 1.0f / static_cast<float>(numRows);

    const AEMath::Vector3 n = AEMath::Vector3::YAxis;
    const AEMath::Vector3 t = AEMath::Vector3::XAxis;
    for (int r = 0; r <= numRows; ++r)
    {
        float rf = static_cast<float>(r);
        for (int c = 0; c <= numColumns; ++c)
        {
            float cf = static_cast<float>(c);

            float u = 1.0f - (uStep * cf);
            float v = (vStep * rf);

            mesh.vertices.push_back({ {x, 0.0f , z  }, n, t, AEMath::Vector2(u,v) });
            x += spacing;
        }
        x = -halfPlaneWidth;
        z += spacing;
    }

    CreatePlaneIndicies(mesh.indicies, numRows, numColumns);



    return mesh;
}


MeshPC MeshBuilder::CreateCubePC(float size, Color colour)
{
    MeshPC mesh;
    const float hs = size * 0.5f;
    //face
    mesh.vertices.push_back({ { -hs, hs, -hs }, colour });
    mesh.vertices.push_back({ { hs, hs, -hs }, colour });
    mesh.vertices.push_back({ { hs, -hs, -hs }, colour });
    mesh.vertices.push_back({ { -hs, -hs, -hs }, colour });

    //back
    mesh.vertices.push_back({ { -hs, hs, hs }, colour });
    mesh.vertices.push_back({ { hs, hs, hs }, colour });
    mesh.vertices.push_back({ { hs, -hs, hs }, colour });
    mesh.vertices.push_back({ { -hs, -hs, hs }, colour });

    CreateCubeIndicies(mesh.indicies);

    return mesh;
}

MeshPC CreateRectanglePC(float width, float height, float depth)
{
    MeshPC mesh;
    int index = rand() % 100;
    const float hw = width * 0.5f;
    const float hh = height * 0.5f;
    const float hd = depth * 0.5f;
    //face
    mesh.vertices.push_back({ { -hw, hh, -hd }, GetNextColor(index) });
    mesh.vertices.push_back({ { hw, hh, -hd }, GetNextColor(index) });
    mesh.vertices.push_back({ { hw, -hh, -hd }, GetNextColor(index) });
    mesh.vertices.push_back({ { -hw, -hh, -hd }, GetNextColor(index) });

    //back
    mesh.vertices.push_back({ { -hw, hh, hd }, GetNextColor(index) });
    mesh.vertices.push_back({ { hw, hh, hd }, GetNextColor(index) });
    mesh.vertices.push_back({ { hw, -hh, hd }, GetNextColor(index) });
    mesh.vertices.push_back({ { -hw, -hh, hd }, GetNextColor(index) });

    CreateCubeIndicies(mesh.indicies);
    

    return mesh;
    
}

MeshPC MeshBuilder::CreatePlanePC(int numRows, int numColumns, float spacing)
{
    MeshPC mesh;
    int index = rand() % 100;

    const float halfPlaneWidth = static_cast<float>(numColumns) * spacing * 0.5f;
    const float halfPlaneHeight = static_cast<float>(numRows) * spacing * 0.5f;

    float x = -halfPlaneWidth;
    float y = -halfPlaneHeight;

    for (int r = 0; r <= numRows; ++r)
    {
        for (int c = 0; c <= numColumns; ++c)
        {
            mesh.vertices.push_back({ {x, y ,0.0f }, GetNextColor(index) });
            x += spacing;
        }
        x = -halfPlaneWidth;
        y += spacing;
    }

    CreatePlaneIndicies(mesh.indicies, numRows, numColumns);

    

    return mesh;
}

MeshPC MeshBuilder::CreateCylinderPC(int slices, int rings)
{
    MeshPC mesh;
    int index = rand() % 100;
    const float halfHeight = static_cast<float>(rings) * 0.5f;

    for (int  r = 0; r <= rings; ++r)
    {
        float ring = static_cast<float>(r);
        float phi = r * (AEMath::Constants::Pi/static_cast<float>(rings));


        for (int s = 0; s < slices + 1; ++s)
        {
            float slice = static_cast<float>(s);
            float rotations = (slice / static_cast<float>(slices)) * AEMath::Constants::TwoPi;
            
            mesh.vertices.push_back({ { sin(rotations), ring - halfHeight, -cos(rotations) }, GetNextColor(index) });
        }
    }

    int numRows = slices + 1;
    int numColumns = rings;

    CreatePlaneIndicies(mesh.indicies, rings, slices);

    CreateCapsPC(mesh, slices, halfHeight);


    return mesh;
}

MeshPC MeshBuilder::CreateSpherePC(int slices, int rings, float radius)
{
    MeshPC mesh;
    int index = rand() % 100;

    float uStep = 1.0f / static_cast<float>(slices);
    float vStep = 1.0f / static_cast<float>(rings);


    //Plane
    for (int r = 0; r <= rings; ++r)
    {
        float ring = static_cast<float>(r);
        float phi = ring * (AEMath::Constants::Pi / static_cast<float>(rings - 1));

        for (int s = 0; s < slices + 1; ++s)
        {
            float slice = static_cast<float>(s);
            float rotation = (slice / static_cast<float>(slices)) * AEMath::Constants::TwoPi;

            float u = 1.0 - (uStep * slice);
            float v = vStep * ring;


            mesh.vertices.push_back({
                {radius * sin(rotation) * sin(phi),
                radius * cos(phi),
                radius * cos(rotation) * sin(phi)},
               GetNextColor(index)
                });
        }
    }

    CreatePlaneIndicies(mesh.indicies, rings, slices);

    return mesh;
}

MeshPX MeshBuilder::CreateCubePX(float size)
{
    MeshPX mesh;
    const float hs = size * 0.5f;
    //face
    mesh.vertices.push_back({ { -hs, hs, -hs }, {0.25f, 0.33f} });
    mesh.vertices.push_back({{ hs, hs, -hs }, {0.5f, 0.33f} });
    mesh.vertices.push_back({{ hs, -hs, -hs }, {0.5f, 0.66f} });
    mesh.vertices.push_back({{ -hs, -hs, -hs }, {0.25f, 0.66f} });

    //back
    mesh.vertices.push_back({{ -hs, hs, hs }, {0.0f, 0.33f} });
    mesh.vertices.push_back({{ hs, hs, hs }, {0.5f, 0.0f} });
    mesh.vertices.push_back({{ hs, -hs, hs }, {0.5f, 1.0f} });
    mesh.vertices.push_back({{ -hs, -hs, hs }, {0.25f, 1.0f} });

    CreateCubeIndicies(mesh.indicies);

    return mesh;
}

MeshPX MeshBuilder::CreateSpherePX(int slices, int rings, float radius)
{
    MeshPX mesh;
    int index = rand() % 100;

    float uStep = 1.0f / static_cast<float>(slices);
    float vStep = 1.0f / static_cast<float>(rings);


    //Plane
    for (int r = 0; r <= rings; ++r)
    {
        float ring = static_cast<float>(r);
        float phi = ring * (AEMath::Constants::Pi / static_cast<float>(rings - 1));

        for (int s = 0; s < slices + 1; ++s)
        {
            float slice = static_cast<float>(s);
            float rotation = (slice / static_cast<float>(slices)) * AEMath::Constants::TwoPi;

            float u = 1.0 - (uStep * slice);
            float v = vStep * ring;


            mesh.vertices.push_back({
                {radius * sin(rotation) * sin(phi),
                radius * cos(phi),
                radius * cos(rotation) * sin(phi)},
                {u,v}
                });
        }
    }

    CreatePlaneIndicies(mesh.indicies, rings, slices);

    return mesh;
}

Mesh MeshBuilder::CreateCube(float size)
{
    Mesh mesh;

    float hs = size * 0.5f;

    // FRONT
    mesh.vertices.push_back({ AEMath::Vector3{  hs,  hs, -hs }, AEMath::Vector3::ZAxis, AEMath::Vector3::XAxis, AEMath::Vector2(0.5f, 0.33f) }); // Top Right Close
    mesh.vertices.push_back({ AEMath::Vector3{ -hs, -hs, -hs }, AEMath::Vector3::ZAxis, AEMath::Vector3::XAxis, AEMath::Vector2(0.25f, 0.66f) }); // Bottom Left Close
    mesh.vertices.push_back({ AEMath::Vector3{  hs, -hs, -hs }, AEMath::Vector3::ZAxis, AEMath::Vector3::XAxis, AEMath::Vector2(0.5f, 0.66f) }); // Bottom Right Close
                                                               
    mesh.vertices.push_back({ AEMath::Vector3{  hs,  hs, -hs }, AEMath::Vector3::ZAxis, AEMath::Vector3::XAxis, AEMath::Vector2(0.5f, 0.33f) }); // Top Right Close
    mesh.vertices.push_back({ AEMath::Vector3{ -hs,  hs, -hs }, AEMath::Vector3::ZAxis, AEMath::Vector3::XAxis, AEMath::Vector2(0.25f, 0.33f) }); // Top Left Close
    mesh.vertices.push_back({ AEMath::Vector3{ -hs, -hs, -hs }, AEMath::Vector3::ZAxis, AEMath::Vector3::XAxis, AEMath::Vector2(0.25f, 0.66f) }); // Bottom Left Close
                                                               
    // BACK                                                     
    mesh.vertices.push_back({ AEMath::Vector3{ -hs,  hs,  hs }, -AEMath::Vector3::ZAxis, -AEMath::Vector3::XAxis, AEMath::Vector2(1.0f, 0.33f) }); // Top Left Far
    mesh.vertices.push_back({ AEMath::Vector3{  hs, -hs,  hs }, -AEMath::Vector3::ZAxis, -AEMath::Vector3::XAxis, AEMath::Vector2(0.75f, 0.66f) }); // Bottom Right Far
    mesh.vertices.push_back({ AEMath::Vector3{ -hs, -hs,  hs }, -AEMath::Vector3::ZAxis, -AEMath::Vector3::XAxis, AEMath::Vector2(1.0f, 0.66f) }); // Bottom Left Far
                                                                
    mesh.vertices.push_back({ AEMath::Vector3{ -hs,  hs,  hs }, -AEMath::Vector3::ZAxis, -AEMath::Vector3::XAxis, AEMath::Vector2(1.0f, 0.33f) }); // Top Left Far
    mesh.vertices.push_back({ AEMath::Vector3{  hs,  hs,  hs }, -AEMath::Vector3::ZAxis, -AEMath::Vector3::XAxis, AEMath::Vector2(0.75f, 0.33f) }); // Top Right Far
    mesh.vertices.push_back({ AEMath::Vector3{  hs, -hs,  hs }, -AEMath::Vector3::ZAxis, -AEMath::Vector3::XAxis, AEMath::Vector2(0.75f, 0.66f) }); // Bottom Right Far
                                                                
    // RIGHT                                                    
    mesh.vertices.push_back({ AEMath::Vector3{  hs,  hs,  hs }, AEMath::Vector3::XAxis, AEMath::Vector3::ZAxis, AEMath::Vector2(0.75f, 0.33f) }); // Top Right Far
    mesh.vertices.push_back({ AEMath::Vector3{  hs, -hs, -hs }, AEMath::Vector3::XAxis, AEMath::Vector3::ZAxis, AEMath::Vector2(0.5f, 0.66f) }); // Bottom Right Close
    mesh.vertices.push_back({ AEMath::Vector3{  hs, -hs,  hs }, AEMath::Vector3::XAxis, AEMath::Vector3::ZAxis, AEMath::Vector2(0.75f, 0.66f) }); // Bottom Right Far
                                                              
    mesh.vertices.push_back({ AEMath::Vector3{  hs,  hs,  hs }, AEMath::Vector3::XAxis, AEMath::Vector3::ZAxis, AEMath::Vector2(0.75f, 0.33f) }); // Top Right Far
    mesh.vertices.push_back({ AEMath::Vector3{  hs,  hs, -hs }, AEMath::Vector3::XAxis, AEMath::Vector3::ZAxis, AEMath::Vector2(0.5f, 0.33f) }); // Top Right Close
    mesh.vertices.push_back({ AEMath::Vector3{  hs, -hs, -hs }, AEMath::Vector3::XAxis, AEMath::Vector3::ZAxis, AEMath::Vector2(0.5f, 0.66f) }); // Bottom Right Close
                                                                
    // Left                                                     
    mesh.vertices.push_back({ AEMath::Vector3{ -hs,  hs, -hs }, -AEMath::Vector3::XAxis, -AEMath::Vector3::ZAxis, AEMath::Vector2(0.25f, 0.33f) }); // Top Left Close
    mesh.vertices.push_back({ AEMath::Vector3{ -hs, -hs,  hs }, -AEMath::Vector3::XAxis, -AEMath::Vector3::ZAxis, AEMath::Vector2(0.0f, 0.66f) }); // Bottom Left Far
    mesh.vertices.push_back({ AEMath::Vector3{ -hs, -hs, -hs }, -AEMath::Vector3::XAxis, -AEMath::Vector3::ZAxis, AEMath::Vector2(0.25f, 0.66f) }); // Bottom Left Close
                                                                 
    mesh.vertices.push_back({ AEMath::Vector3{ -hs,  hs, -hs }, -AEMath::Vector3::XAxis, -AEMath::Vector3::ZAxis, AEMath::Vector2(0.25f, 0.33f) }); // Top Left Close
    mesh.vertices.push_back({ AEMath::Vector3{ -hs,  hs,  hs }, -AEMath::Vector3::XAxis, -AEMath::Vector3::ZAxis, AEMath::Vector2(0.0f, 0.33f) }); // Top Left Far
    mesh.vertices.push_back({ AEMath::Vector3{ -hs, -hs,  hs }, -AEMath::Vector3::XAxis, -AEMath::Vector3::ZAxis, AEMath::Vector2(0.0f, 0.66f) }); // Bottom Left Far
                                                                 
    // Top                                                       
    mesh.vertices.push_back({ AEMath::Vector3{  hs,  hs,  hs }, AEMath::Vector3::YAxis, AEMath::Vector3::XAxis, AEMath::Vector2(0.5f,  0.0f) }); // Top Right Far
    mesh.vertices.push_back({ AEMath::Vector3{ -hs,  hs, -hs }, AEMath::Vector3::YAxis, AEMath::Vector3::XAxis, AEMath::Vector2(0.25f, 0.33f) }); // Top Left Close
    mesh.vertices.push_back({ AEMath::Vector3{  hs,  hs, -hs }, AEMath::Vector3::YAxis, AEMath::Vector3::XAxis, AEMath::Vector2(0.5f, 0.33f) }); // Top Right Close
                                                                 
    mesh.vertices.push_back({ AEMath::Vector3{  hs,  hs,  hs }, AEMath::Vector3::YAxis, AEMath::Vector3::XAxis, AEMath::Vector2(0.5f,  0.0f) }); // Top Right Far
    mesh.vertices.push_back({ AEMath::Vector3{ -hs,  hs,  hs }, AEMath::Vector3::YAxis, AEMath::Vector3::XAxis, AEMath::Vector2(0.25f,  0.0f) }); // Top Left Far
    mesh.vertices.push_back({ AEMath::Vector3{ -hs,  hs, -hs }, AEMath::Vector3::YAxis, AEMath::Vector3::XAxis, AEMath::Vector2(0.25f, 0.33f) }); // Top Left Close
                               
    // Bottom                  
    mesh.vertices.push_back({ AEMath::Vector3{  hs, -hs, -hs }, -AEMath::Vector3::YAxis, -AEMath::Vector3::XAxis, AEMath::Vector2(0.5f, 0.66f) }); // Bottom Right Close
    mesh.vertices.push_back({ AEMath::Vector3{ -hs, -hs,  hs }, -AEMath::Vector3::YAxis, -AEMath::Vector3::XAxis, AEMath::Vector2(0.25f,  1.0f) }); // Bottom Left Far
    mesh.vertices.push_back({ AEMath::Vector3{  hs, -hs,  hs }, -AEMath::Vector3::YAxis, -AEMath::Vector3::XAxis, AEMath::Vector2(0.5f,  1.0f) }); // Bottom Right Far
                               
    mesh.vertices.push_back({ AEMath::Vector3{  hs, -hs, -hs }, -AEMath::Vector3::YAxis, -AEMath::Vector3::XAxis, AEMath::Vector2(0.5f, 0.66f) }); // Bottom Right Close
    mesh.vertices.push_back({ AEMath::Vector3{ -hs, -hs, -hs }, -AEMath::Vector3::YAxis, -AEMath::Vector3::XAxis, AEMath::Vector2(0.25f, 0.66f) }); // Bottom Left Close
    mesh.vertices.push_back({ AEMath::Vector3{ -hs, -hs,  hs }, -AEMath::Vector3::YAxis, -AEMath::Vector3::XAxis, AEMath::Vector2(0.25f,  1.0f) }); // Bottom Left Far

    int i = 0;
    for (const auto& vertex : mesh.vertices)
    {
        mesh.indicies.push_back(i);
        ++i;
    }

    return mesh;
}

Mesh MeshBuilder::CreateSphere(int slices, int rings, float radius)
{
    Mesh mesh;
    float uStep = 1.0f / static_cast<float>(slices);
    float vStep = 1.0f / static_cast<float>(rings);

    //Plane
    for (int r = 0; r <= rings; ++r)
    {
        float ring = static_cast<float>(r);
        float phi = ring * (AEMath::Constants::Pi / static_cast<float>(rings - 1));

        for (int s = 0; s < slices + 1; ++s)
        {
            float slice = static_cast<float>(s);
            float rotation = (slice / static_cast<float>(slices)) * AEMath::Constants::TwoPi;

            float u = 1.0 - (uStep * slice);
            float v = vStep * ring;

            float x = radius * sin(rotation) * sin(phi);
            float y = radius * cos(phi);
            float z = radius * cos(rotation) * sin(phi);

            const AEMath::Vector3 pos = {x, y, z};
            const AEMath::Vector3 norm = AEMath::Normalize(pos);
            const AEMath::Vector3 tan = AEMath::Normalize({-z, 0.0f, x});
            mesh.vertices.push_back({ pos, norm, tan, {u, v} });
        }
    }

    CreatePlaneIndicies(mesh.indicies, rings, slices);

    return mesh;
}

MeshPX MeshBuilder::CreateScreenQuad()
{
    MeshPX mesh;
    mesh.vertices.push_back({ {-1.0f, -1.0f, 0.0f}, {0.0f, 1.0f} });
    mesh.vertices.push_back({ {-1.0f,  1.0f, 0.0f}, {0.0f, 0.0f} });
    mesh.vertices.push_back({ { 1.0f,  1.0f, 0.0f}, {1.0f, 0.0f} });
    mesh.vertices.push_back({ { 1.0f, -1.0f, 0.0f}, {1.0f, 1.0f} });
    mesh.indicies = { 0,1,2,0,2,3 };
    return mesh;
}