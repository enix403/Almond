#pragma once

#include "almond/core/base.h"

namespace Almond {

    // enum FBAttachmentType
    // {
    //     ColorAttachment, DepthAttachment, StencilAttachment
    // };

    // struct FBAttachment
    // {
    //     uint32_t RendererId;
    //     FBAttachmentType Type;
    //     uint32_t Width, Height;
    // };

    struct FramebufferSpecification
    {
        uint32_t Width, Height;
        int SampleCount = 1;
    };

    class Framebuffer
    {

    public:
        explicit Framebuffer(const FramebufferSpecification& spec);
        ~Framebuffer();

        inline const FramebufferSpecification& GetSpecification() const { return m_Spec; }

        inline auto GetColorAttachmentRendererId() const { return m_ColorAttachment; }

        void Bind();
        void Unbind();
        void ReloadSpecs();
        

    private:
        uint32_t m_FBId;
        FramebufferSpecification m_Spec;

        uint32_t m_ColorAttachment, m_DepthAttachment;
    };
}