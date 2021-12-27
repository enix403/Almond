#pragma once

#include "almond/core/base.h"
#include "almond/utils/typedefs.h"

#include <string>

namespace Almond
{

    enum TextureFilterMode: uint8_t 
    {
        TEX_FILTER_MODE_NONE = 0,
        TEX_FILTER_MODE_LINEAR,
        TEX_FILTER_MODE_NEAREST
    };

    enum TextureWrapMode: uint8_t
    {
        TEX_WRAP_MODE_NONE = 0, 
        TEX_WRAP_MODE_REPEAT, 
        TEX_WRAP_MODE_REPEAT_MIRRORED, 
        TEX_WRAP_MODE_CLAMP_EDGE, 
        TEX_WRAP_MODE_CLAMP_BORDER
    };
    
    namespace TexUtils
    {
        /* TODO: These utility functions are way out of place. 
        * But they needed here because they are used by multiple files and I don't like duplicating...
        *
        * They convert the above TextureFilterMode and TextureWrapMode to the corresponding opengl constants
        */
        int OpenGLTextureFilterEnum(TextureFilterMode filterMode);
        int OpenGLTextureWrapEnum(TextureWrapMode wrapMode);
    }

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


    // Bytes (from high to low bit) = {4-bit padding} {2-bit MAG_FILTER} {2-bit MIN_FILTER}
    typedef uint8_t TextureFilterDescription;
    #define TEX_FILTER_MIN(x) ((x) << 0)
    #define TEX_FILTER_MAG(x) ((x) << 2)

    // Bytes (from high to low bit) = {4-bit padding} {4-bit T_WRAP} {4-bit S_WRAP} {4-bit R_WRAP}
    typedef uint16_t TextureWrapDescription;
    #define TEX_WRAP_R(x) ((x) << 0)
    #define TEX_WRAP_S(x) ((x) << 4)
    #define TEX_WRAP_T(x) ((x) << 8)

    class Texture2D : public Texture
    {
    public:
        Texture2D(
            u32 width,
            u32 height,
            TexFormat format
        );
        ~Texture2D();

    public:
        static Ref<Texture2D> CreateFromFile(const std::string& filepath);

        inline uint GetId() const override { return m_TexID;  }
        inline u32 GetWidth() const        { return m_Width;  }
        inline u32 GetHeight() const       { return m_Height; }

        void Bind(int slot) const override;
        inline void SetData(const void* data, u32 size) {
            SetData(0, 0, m_Width, m_Height, data, size);
        }
        void SetData(int x, int y, int width, int height, const void* data, u32 size);

        void SetFilteringMode(TextureFilterDescription filterDesc);
        void SetWrappingMode(TextureWrapDescription wrapDesc);

    public:
        static void ConfigureParams(uint textureId, TextureFilterDescription filterDesc, TextureWrapDescription wrapDesc);

    private:
        uint m_TexID;

        u32 m_Width;
        u32 m_Height;
        // int m_InternalDataFormat;

        unsigned int m_SourceDataFormat; // "rgb" or "rgba" or ...
        unsigned int m_SourceDataType; // "int", "unsigned byte", "float"

    };

} // namespace Almond