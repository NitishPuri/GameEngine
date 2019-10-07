#include "gepch.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace GE {

  Renderer::SceneData* Renderer::s_ScenData = new Renderer::SceneData;

  void Renderer::BeginScene(OrthographicCamera& camera)
  {
    s_ScenData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
  }

  void Renderer::EndScene()
  {
  }

  void Renderer::Submit(const GE::Ref<Shader>& shader, 
                        const GE::Ref<VertexArray>& vertexArray,
                        const glm::mat4& transform)
  {
    shader->Bind();
    std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", s_ScenData->ViewProjectionMatrix);
    std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);

    vertexArray->Bind();
    RenderCommand::DrawIndexed(vertexArray);
  }
}
