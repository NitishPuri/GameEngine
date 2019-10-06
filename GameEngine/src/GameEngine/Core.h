#pragma once

#ifdef GE_PLATFORM_WINDOWS
#if GE_DYNAMIC_LINK
  #ifdef GE_BUILD_DLL
    #define GE_API  __declspec(dllexport)
  #else // GE_BUILD_DLL
    #define GE_API  __declspec(dllimport)
  #endif // GE_BUILD_DLL
#else // GE_DYNAMIC_LINK
  #define GE_API
#endif // GE_DYNAMIC_LINK
#else // GE_PLATFORM_WINDOWS
  #error Game Engine only supports windows
#endif // GE_PLATFORM_WINDOWS

#ifdef GE_DEBUG
  #define GE_ENABLE_ASSERTS
#endif

#ifdef GE_ENABLE_ASSERTS
  #define GE_ASSERT(x, ...) { if(!(x)) { GE_ERROR("Asserion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
  #define GE_CORE_ASSERT(x, ...) { if(!(x)) { GE_CORE_ERROR("Asserion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else // GE_ENABLE_ASSERTS
  #define GE_ASSERT(x, ...) 
  #define GE_CORE_ASSERT(x, ...) 
#endif // GE_ENABLE_ASSERTS

#define BIT(x) (1 << x)

#define GE_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
