/*===-- wtk/foundation/support.h ----------------------------*- mode: C -*-===*/
/*                                                                            */
/*                                     _   _                                  */
/*                               _ _ _| |_| |_                                */
/*                              | | | |  _| '_|                               */
/*                              |_____|_| |_,_|                               */
/*                                                                            */
/*       This file is distributed under the terms described in LICENSE.       */
/*                                                                            */
/*===----------------------------------------------------------------------===*/

#ifndef _WTK_FOUNDATION_SUPPORT_H_
#define _WTK_FOUNDATION_SUPPORT_H_

#include "wtk/config.h"
#include "wtk/linkage.h"

/**
 * \def WTK_INLINE
 * \brief Code should be inlined.
 */
#if defined(DOXYGEN)
  #define WTK_INLINE
#else
  #if defined(_MSC_VER)
    #define WTK_INLINE __forceinline
  #elif defined(__clang__) || defined(__GNUC__)
    #define WTK_INLINE __inline __attribute__ ((always_inline))
  #endif
#endif

/**
 * \def WTK_TRAP
 * \brief Errant, but reachable, code path.
 */
#if defined(DOXYGEN)
  #define WTK_TRAP()
#else
  #if defined(_MSC_VER)
    #define WTK_TRAP() __debugbreak()
  #elif defined(__GNUC__)
    #define WTK_TRAP() __builtin_trap()
  #endif
#endif

/**
 * \def WTK_UNREACHABLE
 * \brief Code is unreachable.
 */
#if defined(DOXYGEN)
  #define WTK_UNREACHABLE()
#else
  #if defined(_MSC_VER)
    #define WTK_UNREACHABLE() __assume(0)
  #elif defined(__clang__)
    #define WTK_UNREACHABLE() __builtin_unreachable()
  #elif defined(__GNUC__)
    #if __GNUC_VERSION__ >= 40500
      #define WTK_UNREACHABLE() __builtin_unreachable()
    #else
      #include <signal.h>
      #define WTK_UNREACHABLE() do { ::signal(SIGTRAP); } while(0, 0)
    #endif
  #endif
#endif

#endif /* _WTK_FOUNDATION_SUPPORT_H_ */
