
#include <GameEngine.h>
#include <GameEngine/Core/EntryPoint.h>

#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Sandbox2D.h"

class ExampleLayer : public GE::Layer
{
public:
    ExampleLayer()
        : Layer("Example")
        , m_CameraController(1280.f / 720.0f, true)
    {
        m_VertexArray = GE::VertexArray::Create();

        float vertices[3 * 7] = {
          -0.5f, -0.5f, 0.0f,   0.8f, 0.2f, 0.8f, 1.0f,
           0.5f, -0.5f, 0.0f,   0.2f, 0.3f, 0.8f, 1.0f,
           0.0f,  0.5f, 0.0f,   0.8f, 0.8f, 0.2f, 1.0f
        };
        GE::Ref<GE::VertexBuffer> vertexBuffer = GE::VertexBuffer::Create(vertices, sizeof(vertices));
        GE::BufferLayout layout = {
          { GE::ShaderDataType::Float3, "a_Position" },
          { GE::ShaderDataType::Float4, "a_Color" }
        };

        vertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(vertexBuffer);

        unsigned int indices[3] = { 0, 1, 2 };
        GE::Ref<GE::IndexBuffer> indexBuffer = GE::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
        m_VertexArray->SetIndexBuffer(indexBuffer);

        m_SquareVA = GE::VertexArray::Create();

        float squareVertices[5 * 4] = {
          -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
           0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
           0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
          -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
        };

        GE::Ref<GE::VertexBuffer> squareVB = GE::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
        squareVB->SetLayout({
          { GE::ShaderDataType::Float3, "a_Position" },
          { GE::ShaderDataType::Float2, "a_TexCoord" }
            });

        m_SquareVA->AddVertexBuffer(squareVB);

        uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
        GE::Ref<GE::IndexBuffer> squareIB = GE::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
        m_SquareVA->SetIndexBuffer(squareIB);

        std::string vertexSrc = R"(
      #version 330 core
      
      layout(location = 0) in vec3 a_Position;
      layout(location = 1) in vec4 a_Color;

      uniform mat4 u_ViewProjection;
      uniform mat4 u_Transform;

      out vec3 v_Position;
      out vec4 v_Color;

      void main()
      {
        v_Position = a_Position;
        v_Color = a_Color;
        gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
      }
    )";

        std::string fragmentSrc = R"(
      #version 330 core
      
      layout(location = 0) out vec4 color;
      in vec3 v_Position;
      in vec4 v_Color;
      void main()
      {
        color = vec4(v_Position * 0.5 + 0.5, 1.0);
        color = v_Color;
      }
    )";

        m_Shader = GE::Shader::Create("VertexPosColor", vertexSrc, fragmentSrc);

        std::string flatColorShaderVertexSrc = R"(
      #version 330 core
      
      layout(location = 0) in vec3 a_Position;

      uniform mat4 u_ViewProjection;
      uniform mat4 u_Transform;

      out vec3 v_Position;
      void main()
      {
        v_Position = a_Position;
        gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);  
      }
    )";

        std::string flatColorShaderFragmentSrc = R"(
      #version 330 core
      
      layout(location = 0) out vec4 color;
      in vec3 v_Position;

      uniform vec3 u_Color;

      void main()
      {
        color = vec4(u_Color, 1.0);
      }
    )";

        m_FlatColorShader = GE::Shader::Create("FlatColorShader", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);


        auto textureShader = m_shaderLibrary.Load("assets/shaders/Texture.glsl");

        m_Texture = GE::Texture2D::Create("assets/textures/logo2.png");

        textureShader->Bind();
        textureShader->SetInt("u_Texture", 0);

    }

    void OnUpdate(GE::Timestep ts) override
    {
        // Update
        m_CameraController.onUpdate(ts);

        if (GE::Input::IsKeyPressed(GE_KEY_J))
            m_SquarePosition.x += m_SquareMoveSpeed * ts;
        if (GE::Input::IsKeyPressed(GE_KEY_L))
            m_SquarePosition.x -= m_SquareMoveSpeed * ts;

        if (GE::Input::IsKeyPressed(GE_KEY_I))
            m_SquarePosition.y += m_SquareMoveSpeed * ts;
        if (GE::Input::IsKeyPressed(GE_KEY_K))
            m_SquarePosition.y -= m_SquareMoveSpeed * ts;


        // Render
        GE::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
        GE::RenderCommand::Clear();

        GE::Renderer::BeginScene(m_CameraController.GetCamera());

        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

        m_FlatColorShader->Bind();

        for (int y = 0; y < 20; y++) {
            for (int x = 0; x < 20; x++) {
                if ((x + y) % 2 == 0) {
                    m_FlatColorShader->SetFloat3("u_Color", m_SquareColor);
                }
                else {
                    m_FlatColorShader->SetFloat3("u_Color", m_SquareColorAlt);
                }
                glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
                glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos + m_SquarePosition) * scale;
                GE::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
            }
        }

        //GE::Renderer::Submit(m_Shader, m_VertexArray);

        auto textureShader = m_shaderLibrary.Get("Texture");

        m_Texture->Bind();
        GE::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

        GE::Renderer::EndScene();
    }

    virtual void OnImGuiRender() override
    {
        ImGui::Begin("Test");
        ImGui::Text("Hello World");
        ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
        ImGui::ColorEdit3("Square Color Alt", glm::value_ptr(m_SquareColorAlt));
        ImGui::End();
    }


    void OnEvent(GE::Event& e) override
    {
        m_CameraController.OnEvent(e);
    }

private:
    GE::Ref<GE::Shader> m_Shader;
    GE::Ref<GE::VertexArray> m_VertexArray;

    GE::Ref<GE::Shader> m_FlatColorShader;
    GE::Ref<GE::VertexArray> m_SquareVA;

    GE::ShaderLibrary m_shaderLibrary;

    GE::Ref<GE::Texture> m_Texture;

    GE::OrthographicCameraController m_CameraController;

    glm::vec3 m_SquarePosition = { 0.f, 0.f, 0.f };
    float m_SquareMoveSpeed = 0.5f;
    glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
    glm::vec3 m_SquareColorAlt = { 0.8f, 0.3f, 0.2f };
};


class Sandbox : public GE::Application
{
public:
    Sandbox()
    {
        //PushLayer(new ExampleLayer());
        PushLayer(new Sandbox2D());
    }

    ~Sandbox()
    {}
};

GE::Application* GE::CreateApplication()
{
    return new Sandbox();
}
