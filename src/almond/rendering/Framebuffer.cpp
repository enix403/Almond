#include "Framebuffer.h"

#include "almond/core/Logging.h"

#include <glad/gl.h>

namespace {
    namespace utils
    {
        using namespace Almond;

        // GLenum OpenGlInternalColorFormat(FBTextureFormat format)
        // {
        //     switch (format) {
        //         case Almond::FBTextureFormat::RGBA_8:
        //             return GL_RGBA8;
        //         case Almond::FBTextureFormat::RED_I32:
        //             return GL_RED_INTEGER;

        //         default: break;
        //     }

        //     // TODO: ASSERT(false, "Unknown color texture type")
        //     return 0;
        // }

        bool IsDepthAttachmentFormat(FBTextureFormat format)
        {
            switch (format) {
                case FBTextureFormat::DEPTH_24_STENCIL_8:
                    return true;
                default:
                    return false;
            }
        }
        
        inline constexpr GLenum OpenGlTextureTarget(bool multisampled)
        {
            return multisampled ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
        }

        inline void AttachColorTexture(int index, uint32_t texId, GLenum internalFormat, uint32_t width, uint32_t height, int samples)
        {
            bool multisampled = samples > 1;
            if (multisampled)
                glTextureStorage2DMultisample(texId, samples, internalFormat, width, height, GL_FALSE);
            else 
                glTextureStorage2D(texId, 1, internalFormat, width, height);

            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, OpenGlTextureTarget(multisampled), texId, 0);
        }

        inline void AttachSingularTexture(uint32_t texId, GLenum internalFormat, GLenum attachmentType, uint32_t width, uint32_t height, int samples)
        {
            bool multisampled = samples > 1;
            if (multisampled)
                glTextureStorage2DMultisample(texId, samples, internalFormat, width, height, GL_FALSE);
            else 
                glTextureStorage2D(texId, 1, internalFormat, width, height);
            
            glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, OpenGlTextureTarget(multisampled), texId, 0);
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

        bool multisampled = m_Spec.SampleCount > 1;

        if (m_ColorAttachmentSpecs.size())
        {
            glCreateTextures(utils::OpenGlTextureTarget(multisampled), m_ColorAttachmentIds.size(), m_ColorAttachmentIds.data());
            for (int i = 0; i < m_ColorAttachmentSpecs.size(); i++)
            {
                const auto& attachment = m_ColorAttachmentSpecs[i];
                auto texId = m_ColorAttachmentIds[i];

                switch (attachment.TextureFormat) {
                    case FBTextureFormat::RGBA_8:
                        utils::AttachColorTexture(i, texId, GL_RGBA8, m_Spec.Width, m_Spec.Height, m_Spec.SampleCount);
                    case FBTextureFormat::RED_I32:
                        utils::AttachColorTexture(i, texId, GL_R32I, m_Spec.Width, m_Spec.Height, m_Spec.SampleCount);

                    default:
                        break;
                }
                
                // utils::AttachColorTexture(i, texId, utils::OpenGlInternalColorFormat(attachment.TextureFormat), 
                            // m_Spec.Width, m_Spec.Height, m_Spec.SampleCount);

                Texture2D::ConfigureParams(texId, attachment.FilterDescription, attachment.WrapDescription);
            }
        }

        if (m_DepthAttachmentSpec.TextureFormat != FBTextureFormat::None)
        {
            glCreateTextures(utils::OpenGlTextureTarget(multisampled), 1, &m_DepthAttachmentId);

            switch (m_DepthAttachmentSpec.TextureFormat) {
                case FBTextureFormat::DEPTH_24_STENCIL_8:
                    utils::AttachSingularTexture(m_DepthAttachmentId, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT, 
                        m_Spec.Width, m_Spec.Height, m_Spec.SampleCount);

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

    int Framebuffer::ReadPixelI(int attachmentIndex, int x, int y)
    {
        // TODO: Check if attachment is valid
        glReadBuffer(GL_COLOR_ATTACHMENT0 + attachmentIndex);
        int pixelData;
        glReadPixels(x, y, 1, 1, GL_RED_INTEGER, GL_INT, &pixelData);
        return pixelData;
    }

    void Framebuffer::ClearColorAttachment(int index, int value)
    {
        // TODO: Check if attachment is valid
        glClearTexImage(m_ColorAttachmentIds[index], 0, GL_RED_INTEGER, GL_INT, &value);
    }
}