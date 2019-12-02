#pragma once

#include "GameEngine/Core/Core.h"

#ifdef GE_PLATFORM_WINDOWS

extern GE::Application* GE::CreateApplication();

int main(int argc, char** argv)
{
    GE::Log::Init();

    GE_PROFILE_BEGIN_SESSION("Startup", "GEProfile-Startup.json");
    auto app = GE::CreateApplication();
    GE_PROFILE_END_SESSION();

    GE_PROFILE_BEGIN_SESSION("Runtime", "GEProfile-Runtime.json");
    app->Run();
    GE_PROFILE_END_SESSION();

    GE_PROFILE_BEGIN_SESSION("Shutdown", "GEProfile-Shutdown.json");
    delete app;
    GE_PROFILE_END_SESSION();
}

#endif // GE_PLATFORM_WINDOWS
