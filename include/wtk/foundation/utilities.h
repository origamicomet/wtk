/*===-- wtk/foundation/utilities.h --------------------------*- mode: C -*-===*/
/*                                                                            */
/*                                     _   _                                  */
/*                               _ _ _| |_| |_                                */
/*                              | | | |  _| '_|                               */
/*                              |_____|_| |_,_|                               */
/*                                                                            */
/*       This file is distributed under the terms described in LICENSE.       */
/*                                                                            */
/*===----------------------------------------------------------------------===*/

#ifndef _WTK_FOUNDATION_UTILITIES_H_
#define _WTK_FOUNDATION_UTILITIES_H_

#include "wtk/config.h"
#include "wtk/linkage.h"

#include "wtk/foundation/types.h"

WTK_BEGIN_EXTERN_C

/**
 * \def WTK_MIN
 * \brief Computes minimum of @a and @b.
 */
#define WTK_MIN(a, b) \
  (((a) > (b)) ? (b) : (a))

/**
 * \def WTK_MAX
 * \brief Computes maximum of @a and @b.
 */
#define WTK_MAX(a, b) \
  (((a) > (b)) ? (a) : (b))

/**
 * \def WTK_CLAMP
 * \brief Clamps @v between @min and @max, inclusive.
 */
#define WTK_CLAMP(v, min, max) \
  WTK_MIN(max, WTK_MAX(min, v))

/**
 * \def WTK_BITS_TO_BYTES
 * \brief Computes the number of bytes required to represent @n bits.
 */
#define WTK_BITS_TO_BYTES(n) \
  (((n) + 7) / 8)

/**
 * \def WTK_BYTES_TO_BITS
 * \brief Computes the number of bits represented by @n bytes.
 */
#define WTK_BYTES_TO_BITS(n) \
  ((n) * 8)

/**
 * \def WTK_ALIGN_TO_BOUNDARY
 * \brief Aligns @ptr to @alignment bytes boundary.
 */
#define WTK_ALIGN_TO_BOUNDARY(ptr, alignment) \
  ((((ptr) + (alignment) - 1) / (alignment)) * (alignment))

/**
 * \def WTK_IS_POWER_OF_TWO
 * \brief Quickly determines if @n is a power of two.
 */
#define WTK_IS_POWER_OF_TWO(n) \
  ((n) && !((n) & ((n) - 1)))

WTK_END_EXTERN_C

#endif /* _WTK_FOUNDATION_UTILITIES_H_ */
