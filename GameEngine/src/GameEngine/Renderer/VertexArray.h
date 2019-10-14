#pragma once

#include <memory>
#include "GameEngine/Renderer/Buffer.h"

namespace GE {

  class VertexArray {
  public:
    virtual ~VertexArray() {}

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    virtual void AddVertexBuffer(const GE::Ref<VertexBuffer>& vertexBuffer) = 0;
    virtual void SetIndexBuffer(const GE::Ref<IndexBuffer>& indexBuffer) = 0;

    virtual const std::vector<GE::Ref<VertexBuffer>>& GetVertexBuffers() const = 0;
    virtual const GE::Ref<IndexBuffer>& GetIndexBuffer() const = 0;

    static Ref<VertexArray> Create();
  };
}
