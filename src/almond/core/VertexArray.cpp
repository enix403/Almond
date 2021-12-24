#include "almond/core/VertexArray.h"

#include <glad/gl.h>

namespace
{
    using namespace Almond;
    int GetComponentTypeByteCount(VertAttribComponentType type)
    {
        switch(type)
        {
        case VertAttribComponentType::Float:
            return sizeof(float);
        case VertAttribComponentType::Int:
            return sizeof(int);
        }
    }

    int ComponentTypeToOpenGlType(VertAttribComponentType type)
    {
        switch(type)
        {
        case VertAttribComponentType::Float:
            return GL_FLOAT;
        case VertAttribComponentType::Int:
            return GL_INT;
        }
    }
} // namespace

namespace Almond
{

    VertexArray::VertexArray()
    {
        glGenVertexArrays(1, &m_VaoId);
    }

    VertexArray::~VertexArray()
    {
        glDeleteVertexArrays(1, &m_VaoId);
        m_VaoId = 0;
    }

    void VertexArray::Bind() const
    {
        glBindVertexArray(m_VaoId);
    }
    void VertexArray::Unbind() const
    {
        glBindVertexArray(0);
    }

    void VertexArray::AddVertexBuffer(const VertexBuffer& buffer, const VertexLayout& layout)
    {
        glBindVertexArray(m_VaoId);
        buffer.Bind();

        int stride = 0;

        for(auto& elem : layout)
        {
            stride += elem.VecComponentCount * GetComponentTypeByteCount(elem.ComponentType);
        }

        int currentOffset = 0;

        for(VLayoutElement elem : layout)
        {
            glEnableVertexAttribArray(elem.LayoutIndex);
            glVertexAttribPointer(elem.LayoutIndex,
                                  elem.VecComponentCount,
                                  ComponentTypeToOpenGlType(elem.ComponentType),
                                  elem.IsNormalized ? GL_TRUE : GL_FALSE,
                                  stride,

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wint-to-void-pointer-cast"
                                  (void*)currentOffset
#pragma clang diagnostic pop

            );
            currentOffset += elem.VecComponentCount * GetComponentTypeByteCount(elem.ComponentType);
        }
    }

    void VertexArray::AddIndexBuffer(const IndexBuffer& buffer)
    {
        glBindVertexArray(m_VaoId);
        buffer.Bind();
    }
} // namespace Almond