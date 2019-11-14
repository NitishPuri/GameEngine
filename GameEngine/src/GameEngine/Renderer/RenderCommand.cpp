#include "gepch.h"
#include "GameEngine/Renderer/RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace GE {
    Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();
}
