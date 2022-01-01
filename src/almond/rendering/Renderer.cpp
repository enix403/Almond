#include "Renderer.h"
#include <memory>

#include "almond/core/base.h"
#include "almond/utils/colors.h"
#include "almond/rendering/Shader.h"
#include "almond/rendering/Texture.h"
#include "almond/rendering/RenderCommand.h"
#include "almond/core/Buffer.h"
#include "almond/core/VertexArray.h"

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#include <glad/gl.h>

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

/* ---------------- End renderer data ---------------- */

namespace Almond
{
    void Renderer::Init()
    {
        s_Data.BatchVBO = CreateScoped<VertexBuffer>(sizeof(ShaderVertexData) * MAX_VERTICES, GL_DYNAMIC_DRAW);
        s_Data.BatchIBO = CreateScoped<IndexBuffer>(MAX_INDICES, GL_DYNAMIC_DRAW);
        s_Data.BatchVAO = CreateScoped<VertexArray>();

        s_Data.BatchVAO->AddVertexBuffer(*s_Data.BatchVBO, {
            {0, "Position",     4, VertAttribComponentType::Float, false},
            {1, "Normal",       3, VertAttribComponentType::Float, false},
            {2, "TexCoords",    2, VertAttribComponentType::Float, false},
            {3, "Entity ID",    1, VertAttribComponentType::Int, false},
        });

        s_Data.BatchVAO->AddIndexBuffer(*s_Data.BatchIBO);

        s_Storage.DefaultEntityShader = s_ShaderLib.LoadFromFile("EditorDiffuseModel", "assets/shaders/EditorDiffuseModel.glsl");

        s_Storage.DefaultTexture = CreateScoped<Texture2D>(1, 1, TexFormat::RGBA_8);

        s_Storage.DefaultTexture->SetFilteringMode(TEX_FILTER_MIN(TEX_FILTER_MODE_NEAREST) | TEX_FILTER_MAG(TEX_FILTER_MODE_LINEAR));
        s_Storage.DefaultTexture->SetWrappingMode(TEX_WRAP_S(TEX_WRAP_MODE_REPEAT) | TEX_WRAP_T(TEX_WRAP_MODE_REPEAT));
        
        static const uint8_t texData[] = { 0xff, 0xff, 0xff, 0xff };
        s_Storage.DefaultTexture->SetData(texData, sizeof(texData));
    }

    void Renderer::Deinit()
    {
        s_Storage.DefaultTexture.reset();

        s_Data.BatchVAO.reset();
        s_Data.BatchVBO.reset();
        s_Data.BatchIBO.reset();
    }

    void Renderer::BeginScene(const Camera &camera)
    {
        s_Data.CameraData.ProjectionView = camera.GetProjectionView();
        s_Data.CameraData.DirectionToLight = -glm::normalize(camera.GetFowardDirection());

        s_Data.BtVertexTop = s_Data.BtVertices;
        s_Data.BtIndexTop = s_Data.BtIndices;

        s_Storage.MainCmdQueue.Clear();
    }

    void Renderer::DrawEntity(const Entity& entity)
    {
        const auto& mesh = entity.GetMesh();
        const auto& transform = entity.GetTransform().GetMatrix();    
        const auto& invTransform = entity.m_InverseTrasponse;

        auto indicesOffset = static_cast<int>(s_Data.BtVertexTop - s_Data.BtVertices);

        for (int i = 0; i < mesh.VertexCount(); i++)
        {
            s_Data.BtVertexTop->Pos = transform * glm::vec4(mesh.Vertices[i], 1.0f);
            s_Data.BtVertexTop->Normal = invTransform * mesh.Normals[i];
            s_Data.BtVertexTop->TexCoords = mesh.TextureCoords[i];

            s_Data.BtVertexTop->EntityID = entity.m_entityID;

            s_Data.BtVertexTop++;
        }

        for (auto index: mesh.Indices)
            *(s_Data.BtIndexTop++) = indicesOffset + index;
    }

    void Renderer::EndScene()
    {
        s_Storage.DefaultEntityShader->Bind();

        s_Storage.DefaultEntityShader->SetUniformFloat3("u_Color", IRGB_TO_FRGB(174, 177, 189));

        s_Storage.DefaultTexture->Bind(0);
        s_Storage.DefaultEntityShader->SetUniformInt("u_Texture", 0); // the slot the texture is bound to

        s_Storage.DefaultEntityShader->SetUniformMat4("u_PV", s_Data.CameraData.ProjectionView);
        s_Storage.DefaultEntityShader->SetUniformFloat3("u_DirectionToLight", s_Data.CameraData.DirectionToLight);

        s_Data.BatchVAO->Bind();

        auto vertexCount = static_cast<int>(s_Data.BtVertexTop - s_Data.BtVertices);
        auto indexCount = static_cast<int>(s_Data.BtIndexTop - s_Data.BtIndices);

        s_Data.BatchVBO->SetData(s_Data.BtVertices, vertexCount * sizeof(ShaderVertexData));
        s_Data.BatchIBO->SetData(s_Data.BtIndices, indexCount);

        // auto command = s_Storage.MainCmdQueue.EnqueueCommand<RenderCommands::Draw>(0);
        // command->StartVertex = 3;
        // command->VertexCount = vertexCount;

        s_Storage.MainCmdQueue.Submit();

        glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    }
}