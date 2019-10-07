#pragma once

#include "GameEngine/Renderer/RendererAPI.h"

namespace GE {
  class OpenGLRendererAPI : public RendererAPI
  {
  public:
    virtual void SetClearColor(const glm::vec4& color) override;

    virtual void Clear() override;

    virtual void DrawIndexed(const GE::Ref<VertexArray>& vertexArray) override;
  };
}
