#include <Almond/Platform/OpenGL/VertexArray.h>

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

        for (const VLayoutElement& elem : layout)
        {
            glEnableVertexAttribArray(elem.LayoutIndex);

            switch (elem.ComponentType)
            {
            case VertAttribComponentType::Float:
                glVertexAttribPointer(
                    elem.LayoutIndex,
                    elem.VecComponentCount,
                    ComponentTypeToOpenGlType(elem.ComponentType),
                    elem.Normalize ? GL_TRUE : GL_FALSE,
                    stride,
                    (void*)currentOffset
                );
                break;
            case VertAttribComponentType::Int:
                glVertexAttribIPointer(
                    elem.LayoutIndex,
                    elem.VecComponentCount,
                    ComponentTypeToOpenGlType(elem.ComponentType),
                    stride,
                    (void*)currentOffset
                );
            }

            currentOffset += elem.VecComponentCount * GetComponentTypeByteCount(elem.ComponentType);
        }
    }

    void VertexArray::AddIndexBuffer(const IndexBuffer& buffer)
    {
        glBindVertexArray(m_VaoId);
        buffer.Bind();
    }
} // namespace Almond