#pragma once

#include <string>
#include <vector>

#include <Almond/Core/Base.h>
#include <Almond/Platform/OpenGL/Buffer.h>
#include <Almond/Platform/OpenGL/VertexArray.h>

#include <Almond/Graphics/Mesh.h>

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

typedef uint32_t EntityHandle_t;

namespace Almond
{

    class Entity
    {
    public:
        Entity(const std::string& name = "Unnamed Entity");

        inline const std::string& GetName() const { return m_Name; }

        inline const MeshTransform& GetTransform() const { return m_Transform; }
        inline MeshTransform& GetTransform() { return m_Transform; }

        inline const Mesh& GetMesh() const { return m_Mesh; }
        inline Mesh& GetMesh() { return m_Mesh; }

        void RecalculateTransformData();

        friend class Renderer;

    private:
        std::string m_Name;
        EntityHandle_t m_entityID;

    private:
        MeshTransform m_Transform {};
        Mesh m_Mesh {};

        glm::mat3 m_InverseTrasponse; // = transpose(inverse(m_Transform without translation)). Needed for lighting calculations

        static uint32_t s_NextEntityID;
    };
}