#include "almond/core/Buffer.h"

#include <glad/glad.h>

namespace Almond
{

    /* ============================= VertexBuffer ============================= */

    VertexBuffer::VertexBuffer()
    {
        glGenBuffers(1, &m_BufId);
    }

    VertexBuffer::~VertexBuffer()
    {
        glDeleteBuffers(1, &m_BufId);
        m_BufId = 0;
    }

    void VertexBuffer::Bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_BufId);
    }
    void VertexBuffer::Unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void VertexBuffer::SetData(const void* data, int size)
    {
        SetData(data, size, GL_STATIC_DRAW);
    }

    void VertexBuffer::SetData(const void* data, int size, int usage)
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_BufId);
        glBufferData(GL_ARRAY_BUFFER, size, data, usage);
    }

    /* ============================= IndexBuffer ============================= */

    IndexBuffer::IndexBuffer()
    {
        glGenBuffers(1, &m_BufId);
    }

    IndexBuffer::~IndexBuffer()
    {
        glDeleteBuffers(1, &m_BufId);
        m_BufId = 0;
    }

    void IndexBuffer::Bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufId);
    }
    void IndexBuffer::Unbind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void IndexBuffer::SetIndices(const uint* data, int size)
    {
        SetIndices(data, size, GL_STATIC_DRAW);
    }

    void IndexBuffer::SetIndices(const uint* data, int size, int usage)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufId);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);
    }

} // namespace Almond