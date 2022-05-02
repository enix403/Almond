#include "Renderer.h"
#include <memory>

#include <Almond/Core/Base.h>
#include <Almond/Utilities/colors.h>
#include <Almond/Platform/OpenGL/Shader.h>
#include <Almond/Platform/OpenGL/Texture.h>
// #include <Almond/Graphics/RenderCommand.h>
#include <Almond/Platform/OpenGL/Buffer.h>
#include <Almond/Platform/OpenGL/VertexArray.h>

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#include <glad/gl.h>

/*
namespace 
{
    using namespace Almond;

    static constexpr int MAX_TRIANGLES = 128; 
    static constexpr int MAX_VERTICES = MAX_TRIANGLES * 3; 
    static constexpr int MAX_INDICES = MAX_VERTICES; // Worst case: exactly one index referrring to each vertex 

    static ShaderLibrary s_ShaderLib;

    struct ShaderVertexData
    {
        glm::vec4 Pos;
        glm::vec3 Normal;
        glm::vec2 TexCoords;

        int EntityID = -1;
    };


    // Data that is not related to current scene or any entity i.e "pure static" data
    struct RendererStorage
    {
        Scoped<Texture2D> DefaultTexture;
        Ref<Shader> DefaultEntityShader;

        RenderCommandQueue MainCmdQueue { 200 };
    };

    struct RendererData
    {
        struct {
            glm::vec3 DirectionToLight;
            glm::mat4 ProjectionView;
        } CameraData;

        ShaderVertexData BtVertices[MAX_VERTICES];
        ShaderVertexData* BtVertexTop;

        uint32_t BtIndices[MAX_INDICES];
        uint32_t* BtIndexTop;

        Scoped<VertexArray> BatchVAO;
        Scoped<VertexBuffer> BatchVBO;
        Scoped<IndexBuffer> BatchIBO;
    };

    static RendererData s_Data;
    static RendererStorage s_Storage;
}
*/

/* ---------------- End renderer data ---------------- */

namespace Almond
{
    void Renderer::Init()
    {
        // s_Data.BatchVBO = CreateScoped<VertexBuffer>(sizeof(ShaderVertexData) * MAX_VERTICES, GL_DYNAMIC_DRAW);
        // s_Data.BatchIBO = CreateScoped<IndexBuffer>(MAX_INDICES, GL_DYNAMIC_DRAW);
        // s_Data.BatchVAO = CreateScoped<VertexArray>();

        // s_Data.BatchVAO->AddVertexBuffer(*s_Data.BatchVBO, {
        //     {0, "Position",     4, VertAttribComponentType::Float, false},
        //     {1, "Normal",       3, VertAttribComponentType::Float, false},
        //     {2, "TexCoords",    2, VertAttribComponentType::Float, false},
        //     {3, "Entity ID",    1, VertAttribComponentType::Int, false},
        // });

        // s_Data.BatchVAO->AddIndexBuffer(*s_Data.BatchIBO);

        // s_Storage.DefaultEntityShader = s_ShaderLib.LoadFromFile("EditorDiffuseModel", "Source/Almond/Shaders/EditorDiffuseModel.glsl");

        // s_Storage.DefaultTexture = CreateScoped<Texture2D>(1, 1, TexFormat::RGBA_8);

        // s_Storage.DefaultTexture->SetFilteringMode(TEX_FILTER_MIN(TEX_FILTER_MODE_NEAREST) | TEX_FILTER_MAG(TEX_FILTER_MODE_LINEAR));
        // s_Storage.DefaultTexture->SetWrappingMode(TEX_WRAP_S(TEX_WRAP_MODE_REPEAT) | TEX_WRAP_T(TEX_WRAP_MODE_REPEAT));
        
        // static const uint8_t texData[] = { 0xff, 0xff, 0xff, 0xff };
        // s_Storage.DefaultTexture->SetData(texData, sizeof(texData));
    }

    void Renderer::Deinit()
    {
        // s_Storage.DefaultTexture.reset();

        // s_Data.BatchVAO.reset();
        // s_Data.BatchVBO.reset();
        // s_Data.BatchIBO.reset();
    }

}