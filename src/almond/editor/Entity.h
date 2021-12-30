#pragma once

#include <string>
#include <vector>

#include "almond/core/base.h"
#include "almond/core/Buffer.h"
#include "almond/core/VertexArray.h"

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

typedef uint32_t EntityHandle_t;

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
    };

    class Entity
    {
    public:
        Entity(const std::string& name = "Unnamed Entity");

        inline int GetVertexCount() const { return m_Vertices.size();  }
        inline int GetIndexCount()  const { return m_Indices.size();   }

        inline const ModelTransform& GetTransform() const { return m_Trasform; }

        void SetGeometry(   const std::vector<ModelVertex>& vertices,
                            const std::vector<uint32_t>& indices);

        // friend class Scene;
        friend class Renderer;

    private:
        std::string m_Name;
        EntityHandle_t m_entityID;

        ModelTransform m_Trasform;

        std::vector<ModelVertex> m_Vertices;
        std::vector<uint32_t> m_Indices;

    private:
        static uint32_t s_NextEntityID;
    };
}