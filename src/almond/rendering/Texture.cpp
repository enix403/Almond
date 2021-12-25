#include "almond/rendering/Texture.h"

#include <glad/gl.h>
#include <stb_image/stb_image.h>

#include "almond/core/Logging.h"

#define TEX_FORMAT_RGBA 1
#define TEX_FORMAT_RGB 2

namespace Almond
{
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
        texture->SetData(data, 0);

        stbi_image_free(data);
        return texture;
    }

} // namespace Almond