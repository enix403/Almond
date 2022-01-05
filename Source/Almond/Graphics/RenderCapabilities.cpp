#include "RenderCapabilities.h"

#include "almond/core/base.h"

#include <glad/gl.h>

namespace Almond
{
    RenderCapabilities::_CapStorage_t RenderCapabilities::Caps {};

    void RenderCapabilities::QueryCaps()
    {
        // Linked Shader Program 

        glGetIntegerv(GL_MAX_COMBINED_UNIFORM_BLOCKS,       &Caps.ShaderProgram.MaxCombinedUniformBlocks);
        glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS,  &Caps.ShaderProgram.MaxCombinedTextureSlots);
        glGetIntegerv(GL_MAX_UNIFORM_BUFFER_BINDINGS,       &Caps.ShaderProgram.MaxUBOBindings);

        // Vertex Shader

        glGetIntegerv(GL_MAX_VERTEX_UNIFORM_COMPONENTS,     &Caps.VertexShader.MaxUniformComponents);
        glGetIntegerv(GL_MAX_VERTEX_UNIFORM_BLOCKS,         &Caps.VertexShader.MaxUniformBlocks);
        glGetIntegerv(GL_MAX_VERTEX_OUTPUT_COMPONENTS,      &Caps.VertexShader.MaxOutputComponents);
        glGetIntegerv(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS,    &Caps.VertexShader.MaxTextureSlots);

        // Fragment Shader

        glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_COMPONENTS,   &Caps.FragmentShader.MaxUniformComponents);
        glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_BLOCKS,       &Caps.FragmentShader.MaxUniformBlocks);
        glGetIntegerv(GL_MAX_FRAGMENT_INPUT_COMPONENTS,     &Caps.FragmentShader.MaxInputComponents);
        glGetIntegerv(GL_MAX_DRAW_BUFFERS,                  &Caps.FragmentShader.MaxDrawBuffers);
        Caps.FragmentShader.MaxOutputComponents = Caps.FragmentShader.MaxDrawBuffers * 4; // Each buffer can output maximum of 4 components
        glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS,           &Caps.FragmentShader.MaxTextureSlots);

        // Geometry Shader

        glGetIntegerv(GL_MAX_GEOMETRY_UNIFORM_COMPONENTS,     &Caps.GeometryShader.MaxUniformComponents);
        glGetIntegerv(GL_MAX_GEOMETRY_UNIFORM_BLOCKS,         &Caps.GeometryShader.MaxUniformBlocks);
        glGetIntegerv(GL_MAX_GEOMETRY_INPUT_COMPONENTS,       &Caps.GeometryShader.MaxInputComponents);
        glGetIntegerv(GL_MAX_GEOMETRY_OUTPUT_COMPONENTS,      &Caps.GeometryShader.MaxOutputComponents);
        glGetIntegerv(GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS,    &Caps.GeometryShader.MaxTextureSlots);
    }

    void RenderCapabilities::Display()
    {
        #define DISPLAY_RENDER_CAP(display_name, target) \
          AD_CORE_LOG_INFO("RenderCap: " display_name " = {0}", target)

        AD_CORE_LOG_INFO("======= RenderCapabilities =======");

        DISPLAY_RENDER_CAP("SHADER_MAX_TEXTURE_SLOTS    ", Caps.ShaderProgram.MaxCombinedTextureSlots);
        DISPLAY_RENDER_CAP("SHADER_MAX_UNIFORM_BLOCKS   ", Caps.ShaderProgram.MaxCombinedUniformBlocks);
        DISPLAY_RENDER_CAP("SHADER_MAX_UBO_BINDINGS     ", Caps.ShaderProgram.MaxUBOBindings);


        DISPLAY_RENDER_CAP("VS_MAX_UNIFORM_COMPONENTS   ", Caps.VertexShader.MaxUniformComponents);
        DISPLAY_RENDER_CAP("VS_MAX_UNIFORM_BLOCKS       ", Caps.VertexShader.MaxUniformBlocks);
        DISPLAY_RENDER_CAP("VS_MAX_OUTPUT_COMPONENTS    ", Caps.VertexShader.MaxOutputComponents);
        DISPLAY_RENDER_CAP("VS_MAX_TEXTURE_SLOTS        ", Caps.VertexShader.MaxTextureSlots);

        DISPLAY_RENDER_CAP("FS_MAX_UNIFORM_COMPONENTS   ", Caps.FragmentShader.MaxUniformComponents);
        DISPLAY_RENDER_CAP("FS_MAX_UNIFORM_BLOCKS       ", Caps.FragmentShader.MaxUniformBlocks);
        DISPLAY_RENDER_CAP("FS_MAX_INPUT_COMPONENTS     ", Caps.FragmentShader.MaxInputComponents);
        DISPLAY_RENDER_CAP("FS_MAX_DRAW_BUFFERS         ", Caps.FragmentShader.MaxDrawBuffers);
        DISPLAY_RENDER_CAP("FS_MAX_OUTPUT_COMPONENTS    ", Caps.FragmentShader.MaxOutputComponents);
        DISPLAY_RENDER_CAP("FS_MAX_TEXTURE_SLOTS        ", Caps.FragmentShader.MaxTextureSlots);

        DISPLAY_RENDER_CAP("GS_MAX_UNIFORM_COMPONENTS   ", Caps.GeometryShader.MaxUniformComponents);
        DISPLAY_RENDER_CAP("GS_MAX_UNIFORM_BLOCKS       ", Caps.GeometryShader.MaxUniformBlocks);
        DISPLAY_RENDER_CAP("GS_MAX_INPUT_COMPONENTS     ", Caps.GeometryShader.MaxInputComponents);
        DISPLAY_RENDER_CAP("GS_MAX_OUTPUT_COMPONENTS    ", Caps.GeometryShader.MaxOutputComponents);
        DISPLAY_RENDER_CAP("GS_MAX_TEXTURE_SLOTS        ", Caps.GeometryShader.MaxTextureSlots);

        #undef DISPLAY_RENDER_CAP
    }

}