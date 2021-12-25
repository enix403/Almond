#pragma once

#include "almond/core/Buffer.h"
#include "almond/core/VertexArray.h"
#include "almond/core/base.h"
#include "almond/layers/Layer.h"
#include "almond/rendering/OrthographicCamera2D.h"
#include "almond/rendering/Shader.h"
#include "almond/rendering/Texture.h"

namespace Almond::Editor
{

    class EditorLayer : public Layer
    {
    public:
        EditorLayer();

        void OnAttach() override;
        void OnDetach() override;
        void OnUpdate() override;

        bool OnEvent(const Events::Event& e) override;

    private:
        void CreateDockSpace();
        void CreateMenuBar();

    private:
        int m_MasterAreaFlags;
        int m_DockNodeFlags;

        Scoped<ShaderLibrary> m_ShaderLibrary;
        Ref<Shader> m_Shader;

        Scoped<VertexArray> m_vao;
        Scoped<VertexBuffer> m_vbo;
        Scoped<IndexBuffer> m_ibo;

        Ref<Texture2D> m_Texture;
        Ref<OrthographicCamera2D> m_Camera;
    };
} // namespace Almond::Editor