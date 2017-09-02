/*===-- wtk/canvas.h ----------------------------------------*- mode: C -*-===*/
/*                                                                            */
/*                                     _   _                                  */
/*                               _ _ _| |_| |_                                */
/*                              | | | |  _| '_|                               */
/*                              |_____|_| |_,_|                               */
/*                                                                            */
/*       This file is distributed under the terms described in LICENSE.       */
/*                                                                            */
/*===----------------------------------------------------------------------===*/

#ifndef _WTK_CANVAS_H_
#define _WTK_CANVAS_H_

#include "wtk/foundation.h"

WTK_BEGIN_EXTERN_C

typedef struct wtk_canvas {
  /*! Dimensions. */
  wtk_uint32_t width;
  wtk_uint32_t height;

  /*! Clipping stack. */
  wtk_rectangle_t clip[8];
  wtk_uint32_t depth;

  /*! Linked-list of batches to submit. */
  struct wtk_batch *batches;

  /*! Current batch. */
  struct wtk_batch *batch;

  /*! Current batch for each level in clipping stack. */
  struct wtk_batch *batch_at_depth[8];

  /*! Allocations for lifetime of canvas. */
  wtk_block_t permanent;

  /*! Allocations for lifetime of a frame. */
  wtk_block_t transient;

  /*! Indicates if a canvas is being drawn to. */
  unsigned drawing;
} wtk_canvas_t;

extern WTK_PUBLIC
  wtk_canvas_t *wtk_canvas_create(
    wtk_uint32_t width,
    wtk_uint32_t height,
    wtk_uint32_t flags);

extern WTK_PUBLIC
  void wtk_canvas_destroy(
    wtk_canvas_t *canvas);

extern WTK_PUBLIC
  void wtk_canvas_begin(
    wtk_canvas_t *canvas);

extern WTK_PUBLIC
  void wtk_canvas_end(
    wtk_canvas_t *canvas);

extern WTK_PUBLIC
  void wtk_canvas_push(
    wtk_canvas_t *canvas,
    wtk_rectangle_t clip);

extern WTK_PUBLIC
  void wtk_canvas_pop(
    wtk_canvas_t *canvas);

extern WTK_PUBLIC
  void wtk_canvas_rect(
    wtk_canvas_t *canvas,
    wtk_rectangle_t rectangle,
    wtk_color_t color,
    wtk_uint32_t flags);

WTK_END_EXTERN_C

#endif /* _WTK_CANVAS_H_ */
