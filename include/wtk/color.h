/*===-- wtk/color.h -----------------------------------------*- mode: C -*-===*/
/*                                                                            */
/*                                     _   _                                  */
/*                               _ _ _| |_| |_                                */
/*                              | | | |  _| '_|                               */
/*                              |_____|_| |_,_|                               */
/*                                                                            */
/*       This file is distributed under the terms described in LICENSE.       */
/*                                                                            */
/*===----------------------------------------------------------------------===*/

#ifndef _WTK_COLOR_H_
#define _WTK_COLOR_H_

#include "wtk/foundation.h"

WTK_BEGIN_EXTERN_C

/* See `wtk/types.h` for `wtk_color_t` definition. */

static WTK_INLINE wtk_color_t wtk_rgba(wtk_uint8_t r,
                                       wtk_uint8_t g,
                                       wtk_uint8_t b,
                                       wtk_uint8_t a)
{
  wtk_color_t color;

  color.rgba = ((wtk_uint32_t)a << 24)
             | ((wtk_uint32_t)b << 16)
             | ((wtk_uint32_t)g << 8)
             | ((wtk_uint32_t)r << 0);

  return color;
}

static WTK_INLINE wtk_color_t wtk_rgb(wtk_uint8_t r,
                                      wtk_uint8_t g,
                                      wtk_uint8_t b)
{
  return wtk_rgba(r, g, b, 255);
}

static WTK_INLINE wtk_color_t wtk_rgbaf(wtk_float32_t r,
                                        wtk_float32_t g,
                                        wtk_float32_t b,
                                        wtk_float32_t a)
{
  return wtk_rgba(WTK_CLAMP(r, 0.f, 1.f) * 255.f,
                  WTK_CLAMP(g, 0.f, 1.f) * 255.f,
                  WTK_CLAMP(b, 0.f, 1.f) * 255.f,
                  WTK_CLAMP(a, 0.f, 1.f) * 255.f);
}

static WTK_INLINE wtk_color_t wtk_rgbf(wtk_float32_t r,
                                       wtk_float32_t g,
                                       wtk_float32_t b)
{
  return wtk_rgb(WTK_CLAMP(r, 0.f, 1.f) * 255.f,
                 WTK_CLAMP(g, 0.f, 1.f) * 255.f,
                 WTK_CLAMP(b, 0.f, 1.f) * 255.f);
}

WTK_END_EXTERN_C

#endif /* _WTK_COLOR_H_ */
