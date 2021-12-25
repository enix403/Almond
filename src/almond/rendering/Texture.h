#pragma once

#include "almond/core/base.h"
#include "almond/utils/typedefs.h"

#include <string>

namespace Almond
{
    class Texture
    {
    public:
        virtual ~Texture() = default;

        virtual uint GetId() const = 0;
        virtual void Bind(int slot) const = 0;
    };

    enum class TexFormat
    {
        RGB_8, RGBA_8
    };

    class Texture2D : public Texture
    {
    public:
        Texture2D(u32 width, u32 height, TexFormat format);
        ~Texture2D();

    public:
        static Ref<Texture2D> CreateFromFile(const std::string& filepath);

        inline uint GetId() const override
        {
            return m_TexID;
        }
        inline u32 GetWidth() const
        {
            return m_Width;
        }
        inline u32 GetHeight() const
        {
            return m_Height;
        }

        void Bind(int slot) const override;
        inline void SetData(const void* data, u32 size) {
            SetData(0, 0, m_Width, m_Height, data, size);
        }
        void SetData(int x, int y, int width, int height, const void* data, u32 size);

    private:
        uint m_TexID;

        u32 m_Width;
        u32 m_Height;
        // int m_InternalDataFormat;

        unsigned int m_SourceDataFormat; // "rgb" or "rgba" or ...
        unsigned int m_SourceDataType; // "int", "unsigned byte", "float"

    };

} // namespace Almond