#include "gepch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace GE {

  Ref<Shader> Shader::Create(const std::string & filepath)
  {
    switch (Renderer::GetAPI())
    {
    case RendererAPI::API::None:
      GE_CORE_ASSERT(false, "RendererAPI::None is currently not supported.");
      return nullptr;
    case RendererAPI::API::OpenGL:
      return CreateRef<OpenGLShader>(filepath);
    }

    GE_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
  }


  Ref<Shader> Shader::Create(const std::string& name, const std::string & vertexSrc, const std::string & fragmentSrc)
  {
    switch (Renderer::GetAPI())
    {
    case RendererAPI::API::None:
      GE_CORE_ASSERT(false, "RendererAPI::None is currently not supported.");
      return nullptr;
    case RendererAPI::API::OpenGL:
      return CreateRef<OpenGLShader>(name, vertexSrc, fragmentSrc);
    }

    GE_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
  }

  void ShaderLibrary::Add(const std::string & name, const Ref<Shader>& shader)
  {
    GE_CORE_ASSERT(!Exists(name), "Shader already exists!");
    m_shaders[name] = shader;
  }

  void ShaderLibrary::Add(const Ref<Shader>& shader)
  {
    Add(shader->GetName(), shader);
  }

  Ref<Shader> ShaderLibrary::Load(const std::string & filepath)
  {
    auto shader = Shader::Create(filepath);
    Add(shader);
    return shader;
  }

  Ref<Shader> ShaderLibrary::Load(const std::string & name, const std::string & filepath)
  {
    auto shader = Shader::Create(filepath);
    Add(name, shader);
    return shader;
  }

  Ref<Shader> ShaderLibrary::Get(const std::string & name)
  {
    GE_CORE_ASSERT(Exists(name), "Shader not found!");
    return m_shaders[name];
  }

  bool ShaderLibrary::Exists(const std::string & name)
  {
    return m_shaders.find(name) != m_shaders.end();
  }

}
