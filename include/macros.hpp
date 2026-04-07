/**
 * @file macros.hpp
 * @author Arnav Deshpande
 *
 * Contains important macro definitions used in the library.
 */

#pragma once

#if defined(__GNUC__)
    /// @brief Signifies GNU compiler is used for compilation.
    #define EULER_COMPILER_GNU

    #if defined(__clang__)
        /// @brief Signifies LLVM Clang compiler is used for compilation.
        #define EULER_COMPILER_CLANG 
    #else
        /// @brief Signifies GNU GCC/G++ compiler is used for compilation.
        #define EULER_COMPILER_GCC 
    #endif
#elif defined(_MSC_VER)
    /// @brief Signifies MSVC compiler is used for compilation.
    #define EULER_COMPILER_MSVC
#elif defined(__INTEL_COMPILER)
    /// @brief Signifies Intel compiler is used for compilation.
    #define EULER_COMPILER_INTEL
#else
    /// @brief Signifies that an unkown compiler is used for compilation/
    #define EULER_COMPILER_UNKNOWN
    #warning "EULER: Unkown compiler is used."
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

/**
 * @brief Ensures given condition is evaluated as a bool.
 * 
 * @par x Condition to be evaulated.
*/
#define EULER_ENSURE_BOOL(x)    (!!(x))

/**
 * @brief Indicates that a functionality is to be implemented.
 * Evaluates to a false static assert, functionality must be implemented to continue.
 *
 * @par msg Message to display.
 */
#define EULER_MUST_BE_IMPLEMENTED(msg)  static_assert(false, msg)
