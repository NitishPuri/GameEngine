#pragma once

#include <GameEngine.h>

class Sandbox2D : public GE::Layer
{
public:
    Sandbox2D();
    virtual ~Sandbox2D() = default;

    void OnAttach() override;
    void OnDetach() override;

    void OnUpdate(GE::Timestep ts) override;
    void OnImGuiRender() override;
    void OnEvent(GE::Event& e) override;

private:
    
    GE::OrthographicCameraController m_CameraController;

    GE::Ref<GE::Texture2D> m_CheckrboardTexture;

    glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f , 1.0f };
};
