#pragma once

#include <Almond/Platform/OpenGL/Buffer.h>

namespace Almond
{
    class VertexArray
    {
    public:
        VertexArray();
        ~VertexArray();

        void Bind() const;
        void Unbind() const;

        void AddVertexBuffer(const VertexBuffer& buffer, const VertexLayout& layout);
        void AddIndexBuffer(const IndexBuffer& buffer);

    private:
        uint m_VaoId;
    };
} // namespace Almond