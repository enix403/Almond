#pragma once

#include <vector>

#include <Almond/Utilities/typedefs.h>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>

namespace Almond
{
    struct MeshTransform
    {
        MeshTransform()
        { Update(); }

        glm::vec3 Position = { 0.f, 0.f, 0.f };
        glm::vec3 Rotation = { 0.f, 0.f, 0.f };
        glm::vec3 Scale = { 1.f, 1.f, 1.f };

        void Update();

        inline const glm::mat4& GetMatrix() const { return m_TrasformMatrix; }

    private:
        glm::mat4 m_TrasformMatrix;
    };

    struct Mesh
    {
        Mesh() = default;

        std::vector<glm::vec3> Vertices;
        std::vector<glm::vec3> Normals;
        std::vector<glm::vec2> TextureCoords;

        std::vector<uint32_t> Indices;

        inline int VertexCount() const { return Vertices.size(); }
    };
}