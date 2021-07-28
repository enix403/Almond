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
        virtual void SetData(int source_format, const void* data, u32 size) = 0;
    };

    class Texture2D : public Texture
    {
    public:
        Texture2D(u32 width, u32 height, int format);
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
        void SetData(int source_format, const void* data, u32 size) override;

    private:
        uint m_TexID;

        u32 m_Width;
        u32 m_Height;
        int m_InternalDataFormat;
    };

} // namespace Almond