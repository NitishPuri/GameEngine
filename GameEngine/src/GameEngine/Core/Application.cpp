#include "gepch.h"
#include "GameEngine/Core/Application.h"

#include "GameEngine/Events/ApplicationEvent.h"

#include "GameEngine/Renderer/Renderer.h"

#include "GameEngine/Core/Input.h"

#include <glfw/glfw3.h>

namespace GE {

    Application* Application::s_Instance = nullptr;

    Application::Application()
    {
        GE_PROFILE_FUNCTION();

        GE_CORE_ASSERT(!s_Instance, "Application already exists!");
        s_Instance = this;

        m_Window = Window::Create();
        m_Window->SetEventCallback(GE_BIND_EVENT_FN(Application::OnEvent));

        Renderer::Init();

        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);
    }

    Application::~Application()
    {
        GE_PROFILE_FUNCTION();

        Renderer::Shutdown();
    }

    void Application::Run()
    {
        GE_PROFILE_FUNCTION();

        while (m_Running)
        {
            GE_PROFILE_SCOPE("RunLoop");
            float time = (float)glfwGetTime();
            Timestep timestep = time - m_LastFrameTime;
            m_LastFrameTime = time;

            if (!m_Minimized) {
                {
                    GE_PROFILE_SCOPE("LayerStack OnUpdate");
                    for (Layer* layer : m_LayerStack) {
                        layer->OnUpdate(timestep);
                    }
                }

                m_ImGuiLayer->Begin();
                {
                    GE_PROFILE_SCOPE("LayerStack OnImGuiRender");
                    for (Layer* layer : m_LayerStack)
                        layer->OnImGuiRender();
                }
                m_ImGuiLayer->End();
            }

            m_Window->OnUpdate();
        }
    }

    void Application::OnEvent(Event & e)
    {
        GE_PROFILE_FUNCTION();

        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(GE_BIND_EVENT_FN(Application::OnWindowClose));
        dispatcher.Dispatch<WindowResizeEvent>(GE_BIND_EVENT_FN(Application::OnWindowResize));

        for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it) {
            (*it)->OnEvent(e);
            if (e.Handled) {
                break;
            }
        }
    }

    void Application::PushLayer(Layer * layer)
    {
        GE_PROFILE_FUNCTION();

        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer * overlay)
    {
        GE_PROFILE_FUNCTION();

        m_LayerStack.PushOverlay(overlay);
        overlay->OnAttach();
    }

    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        m_Running = false;
        return true;
    }

    bool Application::OnWindowResize(WindowResizeEvent& e)
    {
        GE_PROFILE_FUNCTION();

        if (e.GetWidth() == 0 || e.GetHeight() == 0) {
            m_Minimized = true;
            return false;
        }

        m_Minimized = false;
        Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

        return true;
    }
}
