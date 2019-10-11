#pragma once

#include "RenderCommand.h"

#include "OrthographicCamera.h"
#include "Shader.h"

namespace GE {
  class Renderer
  {
  public:
    static void Init();

    static void BeginScene(OrthographicCamera& camera);
    static void EndScene();

    static void Submit(const GE::Ref<Shader>& shader,
                       const GE::Ref<VertexArray>& vertexArray,
                       const glm::mat4& transform = glm::mat4(1.0f));

    inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

  private:
    struct SceneData
    {
      glm::mat4 ViewProjectionMatrix;
    };

    static SceneData* s_ScenData;
  };
}
