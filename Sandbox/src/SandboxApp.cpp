
#include <GameEngine.h>
#include <GameEngine/Core/EntryPoint.h>

#include "Sandbox2D.h"
#include "ExampleLayer.h"

class Sandbox : public GE::Application
{
public:
    Sandbox()
    {
        //PushLayer(new ExampleLayer());
        PushLayer(new Sandbox2D());
    }

    ~Sandbox()
    {}
};

GE::Application* GE::CreateApplication()
{
    return new Sandbox();
}
