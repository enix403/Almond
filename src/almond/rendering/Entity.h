#pragma once

#include <string>
#include <vector>

#include "almond/core/base.h"
#include "almond/core/Buffer.h"
#include "almond/core/VertexArray.h"

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

namespace Almond
{
    struct ModelTransform
    {
        ModelTransform()
        { Update(); }

        glm::vec3 Postiton = { 0.f, 0.f, 0.f };
        glm::vec3 Rotation = { 0.f, 0.f, 0.f };
        glm::vec3 Scale = { 1.f, 1.f, 1.f };

        void Update();
        inline const glm::mat4& GetMatrix() const { return _m_TrasformMatrix; }

    private:
        glm::mat4 _m_TrasformMatrix;
    };

    struct ModelVertex
    {
        ModelVertex() = default;

        glm::vec3 Position;
        glm::vec3 Normal;
        glm::vec2 TextureCoords;

        int EntityID = -1;
    };

    class Entity
    {
    public:
        Entity(const std::string& name = "Unnamed Entity");

        inline const VertexArray& GetVA() const { return m_VA;   }

        inline int GetVertexCount() const { return m_VertexCount;  }
        inline int GetIndexCount()  const { return m_IndexCount;   }

        inline const ModelTransform& GetTransform() const { return m_Trasform; }


        void CreateBuffers( const std::vector<ModelVertex>& vertices,
                            const std::vector<uint32_t>& indices);
    private:
        std::string m_Name;
        uint32_t m_entityID;

        ModelTransform m_Trasform;

        VertexArray m_VA;

        VertexBuffer m_VBuf;
        // std::vector<ModelVertex> m_Vertices;
        int m_VertexCount = 0;

        IndexBuffer m_IBuf;
        // std::vector<uint32_t> m_Indices;
        int m_IndexCount = 0;

    private:
        static uint32_t s_NextEntityID;
    };
}