/*===-- wtk/foundation/types.h ------------------------------*- mode: C -*-===*/
/*                                                                            */
/*                                     _   _                                  */
/*                               _ _ _| |_| |_                                */
/*                              | | | |  _| '_|                               */
/*                              |_____|_| |_,_|                               */
/*                                                                            */
/*       This file is distributed under the terms described in LICENSE.       */
/*                                                                            */
/*===----------------------------------------------------------------------===*/

#ifndef _WTK_FOUNDATION_TYPES_H_
#define _WTK_FOUNDATION_TYPES_H_

#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>

WTK_BEGIN_EXTERN_C

/*
 * Standard
 */

/* TODO(mtwilliams): Fallbacks for older versions of Visual C/C++. */

typedef uintptr_t wtk_uintptr_t;
typedef size_t wtk_size_t;

typedef int8_t wtk_int8_t;
typedef uint8_t wtk_uint8_t;
typedef int16_t wtk_int16_t;
typedef uint16_t wtk_uint16_t;
typedef int32_t wtk_int32_t;
typedef uint32_t wtk_uint32_t;
typedef int64_t wtk_int64_t;
typedef uint64_t wtk_uint64_t;

typedef float wtk_float32_t;
typedef double wtk_float64_t;

/*
 * Custom
 */

typedef struct wtk_rectangle {
  wtk_uint32_t x, y, w, h;
} wtk_rectangle_t;

WTK_END_EXTERN_C

#endif /* _WTK_FOUNDATION_TYPES_H_ */
