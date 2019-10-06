#pragma once

#ifdef GE_PLATFORM_WINDOWS
  #ifdef GE_BUILD_DLL
    #define GE_API  __declspec(dllexport)
  #else // GE_BUILD_DLL
    #define GE_API  __declspec(dllimport)
  #endif // GE_BUILD_DLL
#else // GE_PLATFORM_WINDOWS
  #error Game Engine only supports windows
#endif // GE_PLATFORM_WINDOWS

#ifdef GE_ENABLE_ASSERTS
  #define GE_ASSERT(x, ...) { if(!(x)) { GE_ERROR("Asserion Failed: {0}", __VA_ARGS); __debug_break(); } }
  #define GE_CORE_ASSERT(x, ...) { if(!(x)) { GE_CORE_ERROR("Asserion Failed: {0}", __VA_ARGS); __debug_break(); } }
#else // GE_ENABLE_ASSERTS
  #define GE_ASSERT(x, ...) 
  #define GE_CORE_ASSERT(x, ...) 
#endif // GE_ENABLE_ASSERTS

#define BIT(x) (1 << x)
