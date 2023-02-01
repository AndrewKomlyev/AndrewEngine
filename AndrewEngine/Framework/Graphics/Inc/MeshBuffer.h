#pragma once

namespace AndrewEngine::Graphics
{ 
    class MeshBuffer final
    {
    public:
        enum class Topology
        {
            Points,
            Lines,
            Triangles
        };

        template<class VertexType>
        void Initialize(const std::vector<VertexType>& verticies)
        {
            Initialize(verticies.data(), static_cast<uint32_t>(sizeof(VertexType)), static_cast<uint32_t>(verticies.size()));
        }
        template<class MeshType>
        void Initialize(const MeshType& mesh)
        {
            Initialize(mesh.verticies.data(), static_cast<uint32_t>(sizeof(MeshType::VertexType)), static_cast<uint32_t>(mesh.verticies.size()), mesh.indicies.data(), static_cast<uint32_t>(mesh.indicies.size()));
        }
        void Initialize(const void* verticies, uint32_t vertexSize, uint32_t vertexCount);
        void Initialize(const void* verticies, uint32_t vertexSize, uint32_t vertexCount, const uint32_t* indicies, uint32_t indexCount);
        void Terminate();


        void Update(const void* vertices, uint32_t vertexCount);
        void SetTopology(Topology topology);
        void Render() const;

    private:

        void CreateVertexBuffer(const void* verticies, uint32_t vertexSize, uint32_t vertexCount);
        void CreateIndexBuffer(const uint32_t* indicies, uint32_t indexCount);
        ID3D11Buffer* mVertexBuffer = nullptr;
        ID3D11Buffer* mIndexBuffer = nullptr;
        
        D3D11_PRIMITIVE_TOPOLOGY mTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

        uint32_t mVertexSize;
        uint32_t mVertexCount;
        uint32_t mIndexCount;

    };
}