
#include <GameEngine.h>

class ExampleLayer : public GE::Layer
{
public:
  ExampleLayer()
    : Layer("Example")
  {
  }

  void OnUpdate() override
  {
    if (GE::Input::IsKeyPressed(GE_KEY_TAB))
      GE_TRACE("Tab key is pressed (poll)!");
  }

  void OnEvent(GE::Event& event) override
  {
    if (event.GetEventType() == GE::EventType::KeyPressed)
    {
      GE::KeyPressedEvent& e = (GE::KeyPressedEvent&)event;
      if (e.GetKeyCode() == GE_KEY_TAB)
        GE_TRACE("Tab key is pressed (event)!");
      GE_TRACE("{0}", (char)e.GetKeyCode());
    }
  }

};


class Sandbox : public GE::Application 
{
public:
  Sandbox()
  {
    PushLayer(new ExampleLayer());
    PushLayer(new GE::ImGuiLayer());
  }

  ~Sandbox()
  {}
};

GE::Application* GE::CreateApplication()
{
  return new Sandbox();
}
