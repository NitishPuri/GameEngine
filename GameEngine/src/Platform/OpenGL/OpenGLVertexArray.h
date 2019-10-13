#pragma once

#include "GameEngine/Renderer/VertexArray.h"

namespace GE {

  class OpenGLVertexArray : public VertexArray
  {
  public:
    OpenGLVertexArray();
    virtual ~OpenGLVertexArray();

    virtual void Bind() const override;
    virtual void Unbind() const override;

    virtual void AddVertexBuffer(const GE::Ref<VertexBuffer>& vertexBuffer) override;
    virtual void SetIndexBuffer(const GE::Ref<IndexBuffer>& indexBuffer) override;

    virtual const std::vector<GE::Ref<VertexBuffer>>& GetVertexBuffers() const { return m_VertexBuffers; }
    virtual const GE::Ref<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }
  private:
    uint32_t m_RendererID;
    uint32_t m_VertexBufferIndex = 0;
    std::vector<GE::Ref<VertexBuffer>> m_VertexBuffers;
    GE::Ref<IndexBuffer> m_IndexBuffer;
  };
}

