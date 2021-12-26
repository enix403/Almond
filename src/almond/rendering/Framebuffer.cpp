#include "Framebuffer.h"

#include "almond/core/Logging.h"

#include <glad/gl.h>

namespace {
    namespace utils
    {
        using namespace Almond;
        bool IsDepthAttachmentFormat(FBTextureFormat format)
        {
            switch (format) {
                case FBTextureFormat::DEPTH_24_STENCIL_8:
                    return true;
                default:
                    return false;
            }
        }

        GLint OpenGLFilter(uint8_t value)
        {
            // Very, VERY temporary
            return value == 1 ? GL_LINEAR : GL_REPEAT;
        }
    }
}

namespace Almond {

    Framebuffer::Framebuffer(const FramebufferSpecification& spec)
    :   m_Spec(spec)
    {
        m_ColorAttachmentSpecs.clear();
        m_DepthAttachmentSpec = FBTextureFormat::None;

        for (const auto& attachment: spec.Attachments)
        {
            if (utils::IsDepthAttachmentFormat(attachment.TextureFormat))
                m_DepthAttachmentSpec = attachment;
            else
                m_ColorAttachmentSpecs.emplace_back(attachment);
        }


        Invalidate();
    }

    Framebuffer::~Framebuffer() 
    {
        glDeleteFramebuffers(1, &m_FBId);
        glDeleteTextures(m_ColorAttachmentIds.size(), m_ColorAttachmentIds.data());
        glDeleteTextures(1, &m_DepthAttachmentId);
    }
    
    void Framebuffer::Invalidate()
    {
        if (m_FBId)
        {
            glDeleteFramebuffers(1, &m_FBId);
            glDeleteTextures(m_ColorAttachmentIds.size(), m_ColorAttachmentIds.data());
            glDeleteTextures(1, &m_DepthAttachmentId);
        }

        m_ColorAttachmentIds.resize(m_ColorAttachmentSpecs.size());
        m_DepthAttachmentId = 0;

        glCreateFramebuffers(1, &m_FBId);
        glBindFramebuffer(GL_FRAMEBUFFER, m_FBId);

        glCreateTextures(GL_TEXTURE_2D, m_ColorAttachmentIds.size(), m_ColorAttachmentIds.data());
        for (int i = 0; i < m_ColorAttachmentSpecs.size(); i++)
        {
            const auto& attachment = m_ColorAttachmentSpecs[i];

            switch (attachment.TextureFormat) {
                case FBTextureFormat::RGBA_8:
                    glTextureStorage2D(m_ColorAttachmentIds[i], 1, GL_RGBA8, m_Spec.Width, m_Spec.Height);

                default:
                    break;
            }

            auto filterMode = static_cast<std::underlying_type_t<FBTextureFilterMode>>(attachment.FilterMode);

            glTextureParameteri(m_ColorAttachmentIds[i], GL_TEXTURE_MIN_FILTER, utils::OpenGLFilter(filterMode) & 0x03 >> 0);
            glTextureParameteri(m_ColorAttachmentIds[i], GL_TEXTURE_MAG_FILTER, utils::OpenGLFilter(filterMode) & 0x0C >> 2);

            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, m_ColorAttachmentIds[i], 0);
        }

        if (m_DepthAttachmentSpec.TextureFormat != FBTextureFormat::None)
        {
            glCreateTextures(GL_TEXTURE_2D, 1, &m_DepthAttachmentId);

            switch (m_DepthAttachmentSpec.TextureFormat) {
                case FBTextureFormat::DEPTH_24_STENCIL_8: 
                    glTextureStorage2D(m_DepthAttachmentId, 1, GL_DEPTH24_STENCIL8, m_Spec.Width, m_Spec.Height);
                    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_DepthAttachmentId, 0);

                default:
                    break;
            }
        }

        if (m_ColorAttachmentSpecs.size() > 1)
        {
            // TODO: Check for max attachments
            GLenum buffers[] = {
                GL_COLOR_ATTACHMENT0,
                GL_COLOR_ATTACHMENT1,
                GL_COLOR_ATTACHMENT2,
                GL_COLOR_ATTACHMENT3
            };
            glDrawBuffers(m_ColorAttachmentSpecs.size(), buffers);
        }
        else if (m_ColorAttachmentSpecs.empty())
        {
            glDrawBuffer(GL_NONE);
        }

        /*
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
            AD_CORE_LOG_INFO("Framebuffer is complete");
        else
            AD_CORE_LOG_ERROR("Framebuffer is not complete");
        */

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void Framebuffer::Resize(uint32_t width, uint32_t height)
    {
        m_Spec.Width = width;
        m_Spec.Height = height;
        Invalidate();
    }

    void Framebuffer::Bind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_FBId);
    }

    void Framebuffer::Unbind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

}