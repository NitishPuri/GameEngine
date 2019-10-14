#include "Sandbox2D.h"

#include "imgui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

Sandbox2D::Sandbox2D()
  : Layer("Sandbox2D")
  , m_CameraController(1280.f / 720.0f, true)
{
}

void Sandbox2D::OnAttach()
{
  m_SquareVA = GE::VertexArray::Create();

  float squareVertices[3 * 4] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.5f,  0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f
  };

  GE::Ref<GE::VertexBuffer> squareVB;
  squareVB.reset(GE::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
  squareVB->SetLayout({
    { GE::ShaderDataType::Float3, "a_Position" }
    });

  m_SquareVA->AddVertexBuffer(squareVB);

  uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
  GE::Ref<GE::IndexBuffer> squareIB;
  squareIB.reset(GE::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
  m_SquareVA->SetIndexBuffer(squareIB);

  m_FlatColorShader = GE::Shader::Create("assets/shaders/FlatColor.glsl");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(GE::Timestep ts)
{
  // Update
  m_CameraController.onUpdate(ts);

  // Render
  GE::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
  GE::RenderCommand::Clear();

  GE::Renderer::BeginScene(m_CameraController.GetCamera());


  std::dynamic_pointer_cast<GE::OpenGLShader>(m_FlatColorShader)->Bind();
  std::dynamic_pointer_cast<GE::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);

  GE::Renderer::Submit(m_FlatColorShader, m_SquareVA, glm::scale( glm::mat4(1.0f), glm::vec3(1.5f) ) );

  GE::Renderer::EndScene();


}

void Sandbox2D::OnImGuiRender()
{
  ImGui::Begin("Test");
  ImGui::Text("Hello World");
  ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
  ImGui::End();
}

void Sandbox2D::OnEvent(GE::Event & e)
{
  m_CameraController.OnEvent(e);
}
