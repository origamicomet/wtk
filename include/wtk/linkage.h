/*===-- wtk/linkage.h ---------------------------------------*- mode: C -*-===*/
/*                                                                            */
/*                                     _   _                                  */
/*                               _ _ _| |_| |_                                */
/*                              | | | |  _| '_|                               */
/*                              |_____|_| |_,_|                               */
/*                                                                            */
/*       This file is distributed under the terms described in LICENSE.       */
/*                                                                            */
/*===----------------------------------------------------------------------===*/

#ifndef _WTK_LINKAGE_H_
#define _WTK_LINKAGE_H_

/**
 * \def WTK_LINKAGE_INTERNAL
 * \brief Export symbols for inclusion via objects.
 */
#define WTK_LINKAGE_INTERNAL 0

/**
 * \def WTK_LINKAGE_STATIC
 * \brief Export symbols for inclusion via static library.
 */
#define WTK_LINKAGE_STATIC 1

/**
 * \def WTK_LINKAGE_DYNAMIC
 * \brief Export symbols for inclusion via dynamic library.
 */
#define WTK_LINKAGE_DYNAMIC 2

/**
 * \def WTK_LINKAGE
 * \brief Specifies how you intend to link to WTK.
 */
#ifndef WTK_LINKAGE
  #error ("Please specify how you intend on linking to WTK by defining `WTK_LINKAGE'.")
#endif

/**
 * \def WTK_PUBLIC
 * \brief Marks a symbol for public usage.
 */
#if defined(DOXYGEN)
  #define WTK_PUBLIC
#else
  #if WTK_LINKAGE == WTK_LINKAGE_STATIC
    #define WTK_PUBLIC
  #elif WTK_LINKAGE == WTK_LINKAGE_DYNAMIC
    #if defined(__WTK_IS_BEING_COMPILED__)
      #if defined(__GNUC__)
        #if __GNUC__ >= 4
          #define WTK_PUBLIC __attribute__ ((visibility ("default")))
        #else
          #define WTK_PUBLIC
        #endif
      #elif defined(__clang__)
        #define WTK_PUBLIC __attribute__ ((visibility ("default")))
      #elif defined(_MSC_VER) || defined(__CYGWIN__)
        #define WTK_PUBLIC __declspec(dllexport)
      #else
        #error ("Unknown or unsupported toolchain!")
      #endif
    #else
      #if (defined(__GNUC__) && (__GNUC__ >= 4))
        #define WTK_PUBLIC
      #elif defined(__clang__)
        #define WTK_PUBLIC
      #elif defined(_MSC_VER) || defined(__CYGWIN__)
        #define WTK_PUBLIC __declspec(dllimport)
      #else
        #error ("Unknown or unsupported toolchain!")
      #endif
    #endif
  #endif
#endif

/**
 * \def WTK_PRIVATE
 * \brief Marks a symbol for internal usage.
 */
#if defined(DOXYGEN)
  #define WTK_PRIVATE
#else
  #if WTK_LINKAGE == WTK_LINKAGE_STATIC
    #define WTK_PRIVATE
  #elif WTK_LINKAGE == WTK_LINKAGE_DYNAMIC
    #if defined(__WTK_IS_BEING_COMPILED__)
      #if defined(__GNUC__)
        #if __GNUC__ >= 4
          #define WTK_PRIVATE __attribute__ ((visibility ("hidden")))
        #else
          #define WTK_PRIVATE
        #endif
      #elif defined(__clang__)
        #define WTK_PRIVATE __attribute__ ((visibility ("hidden")))
      #elif defined(_MSC_VER) || defined(__CYGWIN__)
        #define WTK_PRIVATE
      #else
        #error ("Unknown or unsupported toolchain!")
      #endif
    #else
      #define WTK_PRIVATE
    #endif
  #endif
#endif

/**
 * \def WTK_BEGIN_EXTERN_C
 * \internal
 */

/**
 * \def WTK_END_EXTERN_C
 * \internal
 */

#if defined(DOXYGEN)
  #define WTK_BEGIN_EXTERN_C
  #define WTK_END_EXTERN_C
#else
  #if defined(__cplusplus)
    #define WTK_BEGIN_EXTERN_C extern "C" {
    #define WTK_END_EXTERN_C }
  #else
    #define WTK_BEGIN_EXTERN_C
    #define WTK_END_EXTERN_C
  #endif
#endif

#endif /* _WTK_LINKAGE_H_ */
