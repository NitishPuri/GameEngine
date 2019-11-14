#include "Sandbox2D.h"

#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

template<typename Fn>
class Timer {
public:
    Timer(const char* name, Fn&& func) 
        : m_Name(name), m_Stopped(false), m_Func(func)
    {
        m_StartTimepoint = std::chrono::high_resolution_clock::now();
    }

    ~Timer()
    {
        if (!m_Stopped) {
            Stop();
        }
    }

    void Stop()
    {
        auto endTimepoint = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTimepoint - m_StartTimepoint).count();
        m_Stopped = true;

        m_Func({ m_Name, duration * 0.001f });
    }

private:
    const char* m_Name;
    bool m_Stopped;
    std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
    Fn m_Func;
};

#define PROFILE_SCOPE(name) Timer timer##__LINE__(name, [&](ProfileResult profileResult) { m_ProfileResults.push_back(profileResult); })

Sandbox2D::Sandbox2D()
    : Layer("Sandbox2D")
    , m_CameraController(1280.f / 720.0f, true)
{
}

void Sandbox2D::OnAttach()
{
    m_CheckrboardTexture = GE::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(GE::Timestep ts)
{

    PROFILE_SCOPE("Sandbox2D::OnUpdate");

    {
        PROFILE_SCOPE("CameraController::OnUpdate");
        // Update
        m_CameraController.onUpdate(ts);
    }

    {
        PROFILE_SCOPE("Renderer Draw");
        // Render
        GE::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
        GE::RenderCommand::Clear();

        GE::Renderer2D::BeginScene(m_CameraController.GetCamera());
        GE::Renderer2D::DrawQuad({ -1.0F, 0.0F }, { 0.8F, 0.8F }, {0.9, 0.1, 0.3, 1.0});
        GE::Renderer2D::DrawQuad({ 1.0F, 1.0F }, { 1.5F, 1.0F }, m_SquareColor);
        GE::Renderer2D::DrawQuad({ 1.5F, 0.0F, -0.1f }, { 10.0F, 10.0F }, m_CheckrboardTexture);
        GE::Renderer2D::EndScene();
    }
}

void Sandbox2D::OnImGuiRender()
{
    ImGui::Begin("Test");
    ImGui::Text("Hello World");
    ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

    for (auto& result : m_ProfileResults) {
        char label[50];
        strcpy_s(label, "%.3fms "); 
        strcat_s(label, result.Name);
        ImGui::Text(label, result.Time);
    }
    m_ProfileResults.clear();

    ImGui::End();
}

void Sandbox2D::OnEvent(GE::Event & e)
{
    m_CameraController.OnEvent(e);
}
