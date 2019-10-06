#pragma once

#include "GameEngine/Layer.h"

#include "GameEngine/Events/ApplicationEvent.h"
#include "GameEngine/Events/KeyEvent.h"
#include "GameEngine/Events/MouseEvent.h"

namespace GE {

  class GE_API ImGuiLayer : public Layer
  {
  public:
    ImGuiLayer();
    ~ImGuiLayer();

    void OnAttach() override;
    void OnDetach() override;
    virtual void OnImGuiRender() override;

    void Begin();
    void End();

  private:
    float m_Time = 0.0f;
  };

}
