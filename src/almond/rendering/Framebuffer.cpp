#include "Framebuffer.h"

#include "almond/core/Logging.h"

#include <glad/gl.h>

namespace Almond {

    Framebuffer::Framebuffer(const FramebufferSpecification& spec)
    :   m_Spec(spec)
    {
        Invalidate();
    }

    Framebuffer::~Framebuffer() 
    {
        glDeleteFramebuffers(1, &m_FBId);
        glDeleteTextures(1, &m_ColorAttachment);
        glDeleteTextures(1, &m_DepthAttachment);
    }

    void Framebuffer::Invalidate()
    {
        if (m_FBId)
        {
            glDeleteFramebuffers(1, &m_FBId);
            glDeleteTextures(1, &m_ColorAttachment);
            glDeleteTextures(1, &m_DepthAttachment);
        }

        glCreateFramebuffers(1, &m_FBId);
        glBindFramebuffer(GL_FRAMEBUFFER, m_FBId);  

        glCreateTextures(GL_TEXTURE_2D, 1, &m_ColorAttachment);
        // glBindTexture(GL_TEXTURE_2D, m_ColorAttachment);
        glTextureStorage2D(m_ColorAttachment, 1, GL_RGBA8, m_Spec.Width, m_Spec.Height);
        // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Spec.Width, m_Spec.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
        glTextureParameteri(m_ColorAttachment, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_ColorAttachment, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glCreateTextures(GL_TEXTURE_2D, 1, &m_DepthAttachment);
        // glBindTexture(GL_TEXTURE_2D, m_DepthAttachment);
        glTextureStorage2D(m_DepthAttachment, 1, GL_DEPTH24_STENCIL8, m_Spec.Width, m_Spec.Height);
        // glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, m_Spec.Width, m_Spec.Height, 0, 
                        // GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachment, 0);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_DepthAttachment, 0);

        // TODO: ASSET(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)

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