
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
    GE_INFO("ExampleLayer::Update");
  }

  void OnEvent(GE::Event& event) override
  {
    GE_TRACE("{0}", event);
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
