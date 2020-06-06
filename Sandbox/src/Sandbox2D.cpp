#include "Sandbox2D.h"

#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
    : Layer("Sandbox2D")
    , m_CameraController(1280.f / 720.0f, true)
{
}

void Sandbox2D::OnAttach()
{
    GE_PROFILE_FUNCTION();

    m_CheckrboardTexture = GE::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach()
{
    GE_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(GE::Timestep ts)
{

    GE_PROFILE_FUNCTION();

    // Update
    m_CameraController.onUpdate(ts);

    // Render
    {
        GE_PROFILE_SCOPE("Renderer Prep");
        GE::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
        GE::RenderCommand::Clear();
    }

    {
        GE_PROFILE_SCOPE("Renderer Draw");
        GE::Renderer2D::BeginScene(m_CameraController.GetCamera());

        GE::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
        GE::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });        
        GE::Renderer2D::DrawQuad({ -5.0f, -5.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckrboardTexture, 10.0f);
        GE::Renderer2D::DrawQuad({ -0.5f, -0.5f, 0.0f }, { 1.0f, 1.0f }, m_CheckrboardTexture, 20.0f);

        GE::Renderer2D::EndScene();
    }
}

void Sandbox2D::OnImGuiRender()
{
    GE_PROFILE_FUNCTION();

    ImGui::Begin("Test");
    ImGui::Text("Hello World");
    ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

    ImGui::End();
}

void Sandbox2D::OnEvent(GE::Event & e)
{
    m_CameraController.OnEvent(e);
}
