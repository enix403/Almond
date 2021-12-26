#pragma once

#include "almond/core/base.h"

#include <initializer_list>
#include <vector>

#include "almond/rendering//Texture.h"

namespace Almond {
    
    enum class FBTextureFormat
    {
        // R_8, RG_8, RGB_8,
        None = 0,
        RED_I32,
        RGBA_8,
        DEPTH_24_STENCIL_8,
        Depth = DEPTH_24_STENCIL_8
    };

    struct FBTextureSpecification
    {
    public:
        FBTextureSpecification() = default;

        FBTextureSpecification(FBTextureFormat textureFormat)
        :   TextureFormat(textureFormat)
        {}

        FBTextureSpecification(FBTextureFormat textureFormat, uint8_t filterDesc, uint16_t wrapDesc)
        :   TextureFormat(textureFormat),
            FilterDescription(filterDesc),
            WrapDescription(wrapDesc)
        {}

    public:
        FBTextureFormat TextureFormat = FBTextureFormat::None;

        TextureFilterDescription FilterDescription = TEX_FILTER_MIN(TEX_FILTER_MODE_LINEAR) 
                                                    | TEX_FILTER_MAG(TEX_FILTER_MODE_LINEAR);

        TextureWrapDescription WrapDescription = TEX_WRAP_R(TEX_WRAP_MODE_CLAMP_EDGE)
                                                | TEX_WRAP_S(TEX_WRAP_MODE_CLAMP_EDGE)
                                                | TEX_WRAP_T(TEX_WRAP_MODE_CLAMP_EDGE);
    };

    using FBAttachmentsSpecification = std::vector<FBTextureSpecification>;


    struct FramebufferSpecification
    {
        uint32_t Width, Height;
        int SampleCount = 1;
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
        
        int ReadPixelInt(int attachmentIndex, int x, int y);

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