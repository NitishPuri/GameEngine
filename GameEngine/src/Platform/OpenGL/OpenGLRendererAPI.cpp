#include "gepch.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

void GE::OpenGLRendererAPI::SetClearColor(const glm::vec4 & color)
{
  glClearColor(color.r, color.g, color.b, color.a);
}

void GE::OpenGLRendererAPI::Clear()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GE::OpenGLRendererAPI::DrawIndexed(const GE::Ref<VertexArray>& vertexArray)
{
  glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
}
