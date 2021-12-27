#include "almond/rendering/Texture.h"

#include <glad/gl.h>
#include <stb_image/stb_image.h>

#include "almond/core/Logging.h"

#define TEX_FORMAT_RGBA 1
#define TEX_FORMAT_RGB 2

namespace Almond
{
    namespace TexUtils {
        int OpenGLTextureFilterEnum(TextureFilterMode filterMode)
        {
            switch (filterMode) {
                case TEX_FILTER_MODE_LINEAR:
                    return GL_LINEAR;
                case TEX_FILTER_MODE_NEAREST:
                    return GL_NEAREST;

                default:
                    return 0;
            }
        }

        int OpenGLTextureWrapEnum(TextureWrapMode wrapMode)
        {
            switch (wrapMode) {
                case TEX_WRAP_MODE_REPEAT:
                    return GL_REPEAT;
                case TEX_WRAP_MODE_REPEAT_MIRRORED:
                    return GL_MIRRORED_REPEAT;
                case TEX_WRAP_MODE_CLAMP_EDGE:
                    return GL_CLAMP_TO_EDGE;
                case TEX_WRAP_MODE_CLAMP_BORDER:
                    return GL_CLAMP_TO_BORDER;

                default:
                    return 0;
            }
        }
    }
}

namespace Almond
{
    
    /* static */ 
    void Texture2D::ConfigureParams(uint textureId,
                                    TextureFilterDescription filterDesc, 
                                    TextureWrapDescription wrapDesc)
    {
        auto minFilter = (filterDesc >> 0) & 0x03;
        auto magFilter = (filterDesc >> 2) & 0x03;

        if (minFilter)
            glTextureParameteri(textureId, GL_TEXTURE_MIN_FILTER, 
                TexUtils::OpenGLTextureFilterEnum(static_cast<TextureFilterMode>(minFilter)));

        if (magFilter)
            glTextureParameteri(textureId, GL_TEXTURE_MAG_FILTER, 
                TexUtils::OpenGLTextureFilterEnum(static_cast<TextureFilterMode>(magFilter)));

        auto wrapR = (wrapDesc >> 0) & 0x0f;
        auto wrapS = (wrapDesc >> 4) & 0x0f;
        auto wrapT = (wrapDesc >> 8) & 0x0f;

        if (wrapR)
            glTextureParameteri(textureId, GL_TEXTURE_WRAP_R, 
                TexUtils::OpenGLTextureWrapEnum(static_cast<TextureWrapMode>(wrapR)));

        if (wrapS)
            glTextureParameteri(textureId, GL_TEXTURE_WRAP_S,
                TexUtils::OpenGLTextureWrapEnum(static_cast<TextureWrapMode>(wrapS)));

        if (wrapT)
            glTextureParameteri(textureId, GL_TEXTURE_WRAP_T, 
                TexUtils::OpenGLTextureWrapEnum(static_cast<TextureWrapMode>(wrapT)));
    }

    void Texture2D::SetFilteringMode(TextureFilterDescription filterDesc)
    {
        ConfigureParams(m_TexID, filterDesc, 0);
    }

    void Texture2D::SetWrappingMode(TextureWrapDescription wrapDesc)
    {
        ConfigureParams(m_TexID, 0, wrapDesc);
    }

    Texture2D::Texture2D(u32 width, u32 height, TexFormat format)
        : m_Width(width)
        , m_Height(height)
    {

        m_SourceDataType = GL_UNSIGNED_BYTE;
        switch (format) {
            case TexFormat::RGB_8:  m_SourceDataFormat = GL_RGB; break;
            case TexFormat::RGBA_8: m_SourceDataFormat = GL_RGBA; break;
        }

        glCreateTextures(GL_TEXTURE_2D, 1, &m_TexID);
        glTextureStorage2D(m_TexID, 1, GL_RGBA8, m_Width, m_Height);
    }

    Texture2D::~Texture2D()
    {
        glDeleteTextures(1, &m_TexID);
        m_TexID = 0;
    }

    void Texture2D::Bind(int slot) const
    {
        glBindTextureUnit(slot, m_TexID);
    }

    void Texture2D::SetData(int x, int y, int width, int height, const void* data, u32 size)
    {
        glTextureSubImage2D(
            m_TexID,
            0,
            x, y,
            width, height,
            m_SourceDataFormat,
            m_SourceDataType,
            data
        );
    }

    // ===============================

    Ref<Texture2D> Texture2D::CreateFromFile(const std::string& filepath)
    {
        stbi_set_flip_vertically_on_load(true);

        int width, height, channels;
        stbi_uc* data = stbi_load(filepath.c_str(), &width, &height, &channels, 0);

        if(data == nullptr)
        {
            AD_CORE_LOG_ERROR("Unable to load texture file \"{0}\"", filepath);
        }

        TexFormat format;
        if(channels == 4)
        {
            format = TexFormat::RGBA_8;
        }
        else if(channels == 3)
        {
            format = TexFormat::RGB_8;
        }
        else
        {
            AD_CORE_LOG_ERROR("Invalid texture format with channels {0}", channels);
        }

        Ref<Texture2D> texture = CreateRef<Texture2D>(width, height, format);
        texture->SetFilteringMode(TEX_FILTER_MIN(TEX_FILTER_MODE_NEAREST) | TEX_FILTER_MAG(TEX_FILTER_MODE_LINEAR));
        texture->SetWrappingMode(TEX_WRAP_S(TEX_WRAP_MODE_REPEAT) | TEX_WRAP_T(TEX_WRAP_MODE_REPEAT));
        texture->SetData(data, 0);

        stbi_image_free(data);
        return texture;
    }

} // namespace Almond