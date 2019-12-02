#pragma once

#include <GameEngine.h>

class ExampleLayer : public GE::Layer
{
public:
    ExampleLayer();

    void OnUpdate(GE::Timestep ts) override;

    virtual void OnImGuiRender() override;

    void OnEvent(GE::Event& e) override;

private:
    GE::Ref<GE::Shader> m_Shader;
    GE::Ref<GE::VertexArray> m_VertexArray;

    GE::Ref<GE::Shader> m_FlatColorShader;
    GE::Ref<GE::VertexArray> m_SquareVA;

    GE::ShaderLibrary m_shaderLibrary;

    GE::Ref<GE::Texture> m_Texture;

    GE::OrthographicCameraController m_CameraController;

    glm::vec3 m_SquarePosition = { 0.f, 0.f, 0.f };
    float m_SquareMoveSpeed = 0.5f;
    glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
    glm::vec3 m_SquareColorAlt = { 0.8f, 0.3f, 0.2f };
};

