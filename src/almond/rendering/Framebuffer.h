#pragma once

#include "almond/core/base.h"

#include <initializer_list>
#include <vector>

namespace Almond {
    
    enum class FBTextureFormat
    {
        // R_8, RG_8, RGB_8,
        None = 0,
        RGBA_8,
        DEPTH_24_STENCIL_8,
        Depth = DEPTH_24_STENCIL_8
    };



    struct FBTextureSpecification
    {
    public:
        FBTextureSpecification() = default;
        FBTextureSpecification(FBTextureFormat textureFormat)
        : TextureFormat(textureFormat)
        {}

    public:
        FBTextureFormat TextureFormat = FBTextureFormat::None;
        // TODO: Add filtering and wrapping options
    };
    using FBAttachmentsSpecification = std::vector<FBTextureSpecification>;


    struct FramebufferSpecification
    {
        uint32_t Width, Height;
        // int SampleCount = 1;
        FBAttachmentsSpecification Attachments;
    };

    class Framebuffer
    {

    public:
        explicit Framebuffer(const FramebufferSpecification& spec);
        ~Framebuffer();

        inline const FramebufferSpecification& GetSpecification() const { return m_Spec; }
        inline FramebufferSpecification& GetSpecification() { return m_Spec; }

        inline auto GetColorAttachmentRendererId(int index = 0) const { return m_ColorAttachmentIds[index]; }

        void Bind();
        void Unbind();
        void Invalidate();
        void Resize(uint32_t width, uint32_t height);
        

    private:
        uint32_t m_FBId = 0;
        FramebufferSpecification m_Spec;

        // We support multiple color attachments but only one (optional) depth attachment
        std::vector<FBTextureSpecification> m_ColorAttachmentSpecs;
        std::vector<uint32_t> m_ColorAttachmentIds;

        FBTextureSpecification m_DepthAttachmentSpec { FBTextureFormat::None };
        uint32_t m_DepthAttachmentId = 0;
    };
}