#include "almond/core/Buffer.h"

#include <glad/gl.h>

namespace Almond
{

    /* ============================= VertexBuffer ============================= */
    VertexBuffer::VertexBuffer(size_t maxSize)
    : VertexBuffer(maxSize, GL_STATIC_DRAW)
    {}

    VertexBuffer::VertexBuffer(size_t maxSize, int usage)
    {
        glGenBuffers(1, &m_BufId);
        glBindBuffer(GL_ARRAY_BUFFER, m_BufId);
        glBufferData(GL_ARRAY_BUFFER, maxSize, NULL, usage);
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

    void VertexBuffer::SetData(const void* data, size_t offset, size_t size)
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_BufId);
        glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
    }

    void VertexBuffer::UpdateSize(size_t size, int usage, const void* newData)
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_BufId);
        glBufferData(GL_ARRAY_BUFFER, size, newData, usage);
    }

    /* ============================= IndexBuffer ============================= */
    
    IndexBuffer::IndexBuffer(int maxIndexCount)
    : IndexBuffer(maxIndexCount, GL_STATIC_DRAW)
    {}

    IndexBuffer::IndexBuffer(int maxIndexCount, int usage)
    {
        glGenBuffers(1, &m_BufId);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufId);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, maxIndexCount * sizeof(uint32_t), NULL, usage);
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

    void IndexBuffer::SetData(const uint32_t* data, int offset, int updateCount)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufId);
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset * sizeof(uint32_t), updateCount * sizeof(uint32_t), data);
    }

    void IndexBuffer::UpdateSize(int maxIndexCount, int usage, const uint32_t* newData)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufId);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, maxIndexCount * sizeof(uint32_t), newData, usage);
    }

    /* ============================= IndexBuffer ============================= */

} // namespace Almond