#pragma once

namespace Almond {

    class RenderCapabilities
    {
    public:
        static void QueryCaps();
        static void Display();

        static inline const auto& Get() { return Caps; }

    private:
        static struct _CapStorage_t
        {
            _CapStorage_t() = default;

            struct {
                int MaxUniformComponents    = 0;
                int MaxUniformBlocks        = 0;
                int MaxOutputComponents     = 0;
                int MaxTextureSlots         = 0;
            } VertexShader;

            struct {
                int MaxUniformComponents    = 0;
                int MaxUniformBlocks        = 0;
                int MaxInputComponents      = 0;
                int MaxOutputComponents     = 0;
                int MaxDrawBuffers          = 0;
                int MaxTextureSlots         = 0;
            } FragmentShader;

            struct {
                int MaxUniformComponents    = 0;
                int MaxUniformBlocks        = 0;
                int MaxInputComponents      = 0;
                int MaxOutputComponents     = 0;
                int MaxTextureSlots         = 0;
            } GeometryShader;

            struct {
                int MaxCombinedUniformBlocks    = 0;
                int MaxCombinedTextureSlots     = 0;
                int MaxUBOBindings              = 0;
            } ShaderProgram;
        } Caps;
    };
}