
#include <GameEngine.h>

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

class ExampleLayer : public GE::Layer
{
public:
  ExampleLayer()
    : Layer("Example")
    , m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
    , m_CameraPosition(0.0f)
  {
    m_VertexArray.reset(GE::VertexArray::Create());

    float vertices[3 * 7] = {
      -0.5f, -0.5f, 0.0f,   0.8f, 0.2f, 0.8f, 1.0f,
       0.5f, -0.5f, 0.0f,   0.2f, 0.3f, 0.8f, 1.0f,
       0.0f,  0.5f, 0.0f,   0.8f, 0.8f, 0.2f, 1.0f
    };
    std::shared_ptr<GE::VertexBuffer> vertexBuffer;
    vertexBuffer.reset(GE::VertexBuffer::Create(vertices, sizeof(vertices)));
    GE::BufferLayout layout = {
      { GE::ShaderDataType::Float3, "a_Position" },
      { GE::ShaderDataType::Float4, "a_Color" }
    };

    vertexBuffer->SetLayout(layout);
    m_VertexArray->AddVertexBuffer(vertexBuffer);

    unsigned int indices[3] = { 0, 1, 2 };
    std::shared_ptr<GE::IndexBuffer> indexBuffer;
    indexBuffer.reset(GE::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
    m_VertexArray->SetIndexBuffer(indexBuffer);

    m_SquareVA.reset(GE::VertexArray::Create());

    float squareVertices[3 * 4] = {
      -0.5f, -0.5f, 0.0f,
       0.5f, -0.5f, 0.0f,
       0.5f,  0.5f, 0.0f,
      -0.5f,  0.5f, 0.0f,
    };

    std::shared_ptr<GE::VertexBuffer> squareVB;
    squareVB.reset(GE::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
    squareVB->SetLayout({{ 
        GE::ShaderDataType::Float3, "a_Position" }
      });
    m_SquareVA->AddVertexBuffer(squareVB);

    uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
    std::shared_ptr<GE::IndexBuffer> squareIB;
    squareIB.reset(GE::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
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

    m_Shader.reset(GE::Shader::Create(vertexSrc, fragmentSrc));

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

    m_FlatColorShader.reset(GE::Shader::Create(flatColorShaderVertexSrc, flatColorShaderFragmentSrc));

  }

  void OnUpdate(GE::Timestep ts) override
  {
    if (GE::Input::IsKeyPressed(GE_KEY_LEFT))
      m_CameraPosition.x -= m_CameraMoveSpeed * ts;
    else if (GE::Input::IsKeyPressed(GE_KEY_RIGHT))
      m_CameraPosition.x += m_CameraMoveSpeed * ts;

    if (GE::Input::IsKeyPressed(GE_KEY_UP))
      m_CameraPosition.y += m_CameraMoveSpeed * ts;
    else if (GE::Input::IsKeyPressed(GE_KEY_DOWN))
      m_CameraPosition.y -= m_CameraMoveSpeed * ts;

    if (GE::Input::IsKeyPressed(GE_KEY_A))
      m_CameraRotation += m_CameraRotationSpeed * ts;
    if (GE::Input::IsKeyPressed(GE_KEY_D))
      m_CameraRotation -= m_CameraRotationSpeed * ts;

    if (GE::Input::IsKeyPressed(GE_KEY_J))
      m_SquarePosition.x += m_SquareMoveSpeed * ts;
    if (GE::Input::IsKeyPressed(GE_KEY_L))
      m_SquarePosition.x -= m_SquareMoveSpeed * ts;

    if (GE::Input::IsKeyPressed(GE_KEY_I))
      m_SquarePosition.y += m_SquareMoveSpeed * ts;
    if (GE::Input::IsKeyPressed(GE_KEY_K))
      m_SquarePosition.y -= m_SquareMoveSpeed * ts;

    GE::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
    GE::RenderCommand::Clear();

    m_Camera.SetPosition(m_CameraPosition);
    m_Camera.SetRotation(m_CameraRotation);

    GE::Renderer::BeginScene(m_Camera);

    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

    std::dynamic_pointer_cast<GE::OpenGLShader>(m_FlatColorShader)->Bind();

    for (int y = 0; y < 20; y++)
    {
      for (int x = 0; x < 20; x++)
      {
        if ( (x + y) % 2 == 0) {
          std::dynamic_pointer_cast<GE::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);
        }
        else {
          std::dynamic_pointer_cast<GE::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColorAlt);
        }
        glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f) ;
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos + + m_SquarePosition) * scale;
        GE::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
      }
    }

    GE::Renderer::Submit(m_Shader, m_VertexArray);

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


  void OnEvent(GE::Event& event) override
  {
  }

private:
  std::shared_ptr<GE::Shader> m_Shader;
  std::shared_ptr<GE::VertexArray> m_VertexArray;

  std::shared_ptr<GE::Shader> m_FlatColorShader;
  std::shared_ptr<GE::VertexArray> m_SquareVA;

  GE::OrthographicCamera m_Camera;
  glm::vec3 m_CameraPosition;
  float m_CameraMoveSpeed = 5.0f;

  glm::vec3 m_SquarePosition = {0.f, 0.f, 0.f};
  float m_SquareMoveSpeed = 0.5f;

  float m_CameraRotation = 0.0f;
  float m_CameraRotationSpeed = 180.0f;

  glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
  glm::vec3 m_SquareColorAlt = { 0.8f, 0.3f, 0.2f };
};


class Sandbox : public GE::Application 
{
public:
  Sandbox()
  {
    PushLayer(new ExampleLayer());
  }

  ~Sandbox()
  {}
};

GE::Application* GE::CreateApplication()
{
  return new Sandbox();
}
