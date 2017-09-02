/*===-- wtk/draw.h ------------------------------------------*- mode: C -*-===*/
/*                                                                            */
/*                                     _   _                                  */
/*                               _ _ _| |_| |_                                */
/*                              | | | |  _| '_|                               */
/*                              |_____|_| |_,_|                               */
/*                                                                            */
/*       This file is distributed under the terms described in LICENSE.       */
/*                                                                            */
/*===----------------------------------------------------------------------===*/

#ifndef _WTK_DRAW_H_
#define _WTK_DRAW_H_

#include "wtk/foundation.h"

WTK_BEGIN_EXTERN_C

#if WTK_ARCHITECTURE == WTK_ARCHITECTURE_X86 || \
    WTK_ARCHITECTURE == WTK_ARCHITECTURE_X86_X64
  /* Reduce bloat at cost of unaligned access. */
  #pragma pack(push, 1)
#endif

typedef struct wtk_vertex {
  wtk_uint16_t x, y;
  wtk_uint16_t u, v;
  wtk_uint32_t color;
  wtk_uint8_t  texture;
} wtk_vertex_t;

#if WTK_ARCHITECTURE == WTK_ARCHITECTURE_X86 || \
    WTK_ARCHITECTURE == WTK_ARCHITECTURE_X86_X64
  #pragma pack(pop)
#endif

typedef struct wtk_batch {
  struct wtk_batch *next;

  wtk_uint32_t id;

  /* Timestamps. */
  wtk_uint64_t started;
  wtk_uint64_t completed;

  wtk_rectangle_t clip;

  /* TODO(mtwilliams): Different blend modes? */
#if 0
  wtk_blend_t blend;
#endif

  /* TODO(mtwilliams): Texturing. */
#if 0
  /* Textures applied to primitives. */
  wtk_texture_set_t ts;
#endif

  /* Number of verticies. */
  wtk_uint32_t count;

  /* Maximum number of verticies until you need to start a new batch. */
  wtk_uint32_t limit;

  wtk_vertex_t verticies[0];
} wtk_batch_t;

WTK_END_EXTERN_C

#endif /* _WTK_DRAW_H_ */
