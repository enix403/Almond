#include "almond/rendering/Texture.h"

#include <glad/gl.h>
#include <stb_image/stb_image.h>

#include "almond/core/Logging.h"

#define TEX_FORMAT_RGBA 1
#define TEX_FORMAT_RGB 2

namespace Almond
{
    Texture2D::Texture2D(u32 width, u32 height, int format)
        : m_Width(width)
        , m_Height(height)
        , m_InternalDataFormat(format)
    {

        glCreateTextures(GL_TEXTURE_2D, 1, &m_TexID);
        glTextureStorage2D(m_TexID, 1, m_InternalDataFormat == TEX_FORMAT_RGBA ? GL_RGBA8 : GL_RGB8, m_Width, m_Height);

        glTextureParameteri(m_TexID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_TexID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTextureParameteri(m_TexID, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(m_TexID, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }

    Texture2D::~Texture2D()
    {
        glDeleteTextures(1, &m_TexID);
        m_TexID = 0;
    }

    void Texture2D::Bind(int slot) const
    {
        // glBindTexture(GL_TEXTURE_2D, m_TexID);
        glBindTextureUnit(slot, m_TexID);
    }

    void Texture2D::SetData(int source_format, const void* data, u32 size)
    {
        int bytesPerPixel = source_format == TEX_FORMAT_RGBA ? 4 : 3;
        if(size != 0 && size != bytesPerPixel * m_Width * m_Height)
        {
            AD_CORE_LOG_WARN("Texture source data should be complete");
            return;
        }

        glTextureSubImage2D(
            m_TexID,
            0,
            0, 0,
            m_Width, m_Height,
            source_format == TEX_FORMAT_RGBA ? GL_RGBA : GL_RGB,
            GL_UNSIGNED_BYTE,
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

        int format;
        if(channels == 4)
        {
            format = TEX_FORMAT_RGBA;
        }
        else if(channels == 3)
        {
            format = TEX_FORMAT_RGB;
        }
        else
        {
            AD_CORE_LOG_ERROR("Invalid texture format with channels {0}", channels);
        }

        Ref<Texture2D> texture = CreateRef<Texture2D>(width, height, format);
        texture->SetData(format, data, 0);

        stbi_image_free(data);
        return texture;
    }

} // namespace Almond