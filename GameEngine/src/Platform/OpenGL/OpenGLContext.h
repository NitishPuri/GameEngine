#pragma once

#include "GameEngine/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace GE {
  class OpenGLContext : public GraphicsContext {
  public:
    OpenGLContext(GLFWwindow* window);

    void Init() override;
    void SwapBuffers() override;
  private:
    GLFWwindow* m_WindowHandle;
  };
}
