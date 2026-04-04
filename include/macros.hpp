#pragma once

#if defined(__GNUC__)
    #define EULER_COMPILER_GNU

    #if defined(__clang__)
        #define EULER_COMPILER_CLANG 
    #else
        #define EULER_COMPILER_GCC 
    #endif
#elif defined(_MSC_VER)
    #define EULER_COMPILER_MSVC
#elif defined(__INTEL_COMPILER)
    #define EULER_COMPILER_INTEL
#else
    #define EULER_COMPILER_UNKNOWN
#endif

#if defined(EULER_LIB_SHARED)
    #if defined(EULER_SOURCE)
        #define EULER_API __declspec(dllexport)
    #else
        #define EULER_API __declspec(dllimport)
    #endif
#else
    #define EULER_API
#endif

#define EULER_ENSURE_BOOL(x)    (!!(x))

#define EULER_MUST_BE_IMPLEMENTED(msg)  static_assert(false, msg)
