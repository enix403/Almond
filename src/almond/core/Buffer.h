#pragma once

#include <initializer_list>
#include <string>
#include <vector>

#include "almond/utils/typedefs.h"

// Aliases for OpenGL buffer usage constants (GL_STATIC_DRAW, GL_STREAM_DRAW etc).
// These are here so that the consumer of the buffer api defined below does not
// have to include the whole GLAD library to use these

// clang-format off
#define BUF_USAGE_STREAM_DRAW      0x88E0
#define BUF_USAGE_STREAM_READ      0x88E1
#define BUF_USAGE_STREAM_COPY      0x88E2
#define BUF_USAGE_STATIC_DRAW      0x88E4
#define BUF_USAGE_STATIC_READ      0x88E5
#define BUF_USAGE_STATIC_COPY      0x88E6
#define BUF_USAGE_DYNAMIC_DRAW     0x88E8
#define BUF_USAGE_DYNAMIC_READ     0x88E9
#define BUF_USAGE_DYNAMIC_COPY     0x88EA
// clang-format on

namespace Almond
{

    enum class VertAttribComponentType
    {
        Float,
        Int
    };

    struct VLayoutElement
    {
        int LayoutIndex;
        const std::string Name;
        int VecComponentCount; // number of components (i.e 4 for vec4) or 1 in case of float, int, etc
        VertAttribComponentType ComponentType;
        bool Normalize;
    };

    using VertexLayout = std::vector<VLayoutElement>;

    // class VertexLayout {
    // public:
    //     VertexLayout(const std::initializer_list<VLayoutElement>& elements)
    //     : m_Elements(elements) {}

    //     inline const std::vector<VLayoutElement>& GetElement() const { return m_Elements; }

    // private:
    //     std::vector<VLayoutElement> m_Elements;
    // };

    class VertexBuffer
    {
    public:
        VertexBuffer(size_t maxSize);
        VertexBuffer(size_t maxSize, int usage);

        ~VertexBuffer();

        void Bind() const;
        void Unbind() const;

        void UpdateSize(size_t size, int usage, const void* newData);
        inline void UpdateSize(size_t size, int usage) { UpdateSize(size, usage, NULL); }

        void SetData(const void* data, size_t offset, size_t size);
        inline void SetData(const void* data, size_t size) { SetData(data, 0, size); }

    private:
        uint m_BufId;
    };

    class IndexBuffer
    {
    public:
        IndexBuffer(size_t maxSize);
        IndexBuffer(size_t maxSize, int usage);
        ~IndexBuffer();

        void Bind() const;
        void Unbind() const;

        void UpdateSize(size_t size, int usage, const uint32_t* newData);
        inline void UpdateSize(size_t size, int usage) { UpdateSize(size, usage, NULL); }

        void SetData(const uint32_t* data, size_t offset, size_t size);
        inline void SetData(const uint32_t* data, size_t size) { SetData(data, 0, size); }

    private:
        uint m_BufId;
    };

} // namespace Almond


