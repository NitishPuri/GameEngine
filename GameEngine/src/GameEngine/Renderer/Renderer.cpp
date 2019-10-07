#include "gepch.h"
#include "Renderer.h"

namespace GE {

  Renderer::SceneData* Renderer::s_ScenData = new Renderer::SceneData;

  void Renderer::BeginScene(OrthographicCamera& camera)
  {
    s_ScenData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
  }

  void Renderer::EndScene()
  {
  }

  void Renderer::Submit(const std::shared_ptr<Shader>& shader, 
                        const std::shared_ptr<VertexArray>& vertexArray,
                        const glm::mat4& transform)
  {
    shader->Bind();
    shader->UploadUniformMat4("u_ViewProjection", s_ScenData->ViewProjectionMatrix);
    shader->UploadUniformMat4("u_Transform", transform);

    vertexArray->Bind();
    RenderCommand::DrawIndexed(vertexArray);
  }
}
