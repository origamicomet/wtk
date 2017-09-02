/*===-- wtk/canvas.c ----------------------------------------*- mode: C -*-===*/
/*                                                                            */
/*                                     _   _                                  */
/*                               _ _ _| |_| |_                                */
/*                              | | | |  _| '_|                               */
/*                              |_____|_| |_,_|                               */
/*                                                                            */
/*       This file is distributed under the terms described in LICENSE.       */
/*                                                                            */
/*===----------------------------------------------------------------------===*/

#include "wtk/canvas.h"

/* For batches. */
#include "wtk/draw.h"

WTK_BEGIN_EXTERN_C

/* FIXME(mtwilliams): Batch ordering when parent is flushed. */
/* FIXME(mtwilliams): Batch ordering in general. */

/* PERF(mtwilliams): Tag batches with magic. Internally, magic is frame and
 * widget identifier. Hash batch after drawing. Check if hash matches previous
 * frame. If it does, discard.
 */

/* PERF(mtwilliams): Dirty area optimization. Instead of drawing everything
 * again, set the viewport to the dirty area and render anything that is
 * potentially visible, making sure to clip scissors against the viewport. We
 * can also discard whole batches, by calculating (or maintaining) a bounding
 * rectangle.
 */

/* MEM(mtwilliams): Batch overlapping. Allocate batches for best case, i.e. a
 * a lot of verticies. When flushed or finished, identify free space. If a
 * bunch is left, use free space as backing memory for a smaller batch. If a
 * smaller batch is exhausted, copy to full size block, and push previously
 * used free space into a free-list.
 */

/* TODO(mtwilliams): Debug.
 * TODO(mtwilliams): Wireframe.
 * TODO(mtwilliams): Hollow rectangles.
 * TODO(mtwilliams): Feathering. Extrude by one pixel and set alpha to zero.
 */

static wtk_batch_t *allocate_a_batch(wtk_block_t *block)
{
  /* Maximum number of verticies per batch. */
  static const wtk_uint32_t VERTICIES_PER_BATCH = 1024;

  static wtk_uint32_t id = 0;

  wtk_batch_t *batch =
    (wtk_batch_t *)wtk_block_allocate_s(block,
                                        sizeof(wtk_batch_t) + VERTICIES_PER_BATCH * sizeof(wtk_vertex_t));

  batch->next = NULL;

  /* Assign a globally unique identifier to aid debugging. */
  batch->id = ++id;

  batch->count = 0;
  batch->limit = VERTICIES_PER_BATCH;

  return batch;
}

wtk_canvas_t *wtk_canvas_create(wtk_uint32_t width,
                                wtk_uint32_t height,
                                wtk_uint32_t flags)
{
  wtk_canvas_t *canvas =
    (wtk_canvas_t *)wtk_allocate_s(sizeof(wtk_canvas_t), 16);

  canvas->width = width;
  canvas->height = height;

  canvas->batches = NULL;
  canvas->batch = NULL;
  canvas->batch_at_depth[0] = NULL;
  canvas->batch_at_depth[1] = NULL;
  canvas->batch_at_depth[2] = NULL;
  canvas->batch_at_depth[3] = NULL;
  canvas->batch_at_depth[4] = NULL;
  canvas->batch_at_depth[5] = NULL;
  canvas->batch_at_depth[6] = NULL;
  canvas->batch_at_depth[7] = NULL;

  canvas->permanent.base   = (wtk_uintptr_t)wtk_allocate_s(65535, 16);
  canvas->permanent.offset = 0;
  canvas->permanent.size   = 65535;

  /* TODO(mtwilliams): Dynamically grow and shrink transient arena. */
  canvas->transient.base   = (wtk_uintptr_t)wtk_allocate_s(1048575, 16);
  canvas->transient.offset = 0;
  canvas->transient.size   = 65535;

  canvas->drawing = 0;

  return canvas;
}

void wtk_canvas_destroy(wtk_canvas_t *canvas)
{
  wtk_free((void *)canvas->permanent.base);
  wtk_free((void *)canvas->transient.base);
  wtk_free((void *)canvas);
}

void wtk_canvas_begin(wtk_canvas_t *canvas)
{
  wtk_assert_debug(canvas->drawing == 0);

  /* Blow away allocations from previous frame. */
  wtk_block_reset(&canvas->transient);

  /*
   * Reset clipping stack.
   */

  canvas->clip[0].x = 0;
  canvas->clip[0].y = 0;
  canvas->clip[0].w = canvas->width;
  canvas->clip[0].h = canvas->height;

  canvas->depth = 0;

  /*
   * Restart batching.
   */

  wtk_batch_t *batch = allocate_a_batch(&canvas->transient);

  /* TODO(mtwilliams): Timestamp batches. */
  batch->started = batch->completed = 0;

  /* First batch spans entirety of canvas. */
  batch->clip = canvas->clip[0];

  canvas->batches           = batch;
  canvas->batch             = batch;
  canvas->batch_at_depth[0] = batch;
  canvas->batch_at_depth[1] = NULL;
  canvas->batch_at_depth[2] = NULL;
  canvas->batch_at_depth[3] = NULL;
  canvas->batch_at_depth[4] = NULL;
  canvas->batch_at_depth[5] = NULL;
  canvas->batch_at_depth[6] = NULL;
  canvas->batch_at_depth[7] = NULL;

  /* Mark start of drawing. */
  canvas->drawing = 1;
}

void wtk_canvas_end(wtk_canvas_t *canvas)
{
  /*
   * Prevent erroneous drawing outside of markers.
   */

  canvas->depth = 0;

  canvas->batch             = NULL;
  canvas->batch_at_depth[0] = NULL;
  canvas->batch_at_depth[1] = NULL;
  canvas->batch_at_depth[2] = NULL;
  canvas->batch_at_depth[3] = NULL;
  canvas->batch_at_depth[4] = NULL;
  canvas->batch_at_depth[5] = NULL;
  canvas->batch_at_depth[6] = NULL;
  canvas->batch_at_depth[7] = NULL;

  /* Mark end of drawing. */
  canvas->drawing = 0;
}

void wtk_canvas_push(wtk_canvas_t *canvas,
                     wtk_rectangle_t clip)
{
  wtk_assert_debug(canvas->depth <= 8);

  canvas->depth += 1;

  wtk_batch_t *batch = allocate_a_batch(&canvas->transient);

  /* TODO(mtwilliams): Timestamp batches. */
  batch->started = batch->completed = 0;

  /* Circumscribed by previous clipping rectangle. */
  clip.x = WTK_MAX(clip.x, canvas->clip[canvas->depth - 1].x);
  clip.y = WTK_MAX(clip.y, canvas->clip[canvas->depth - 1].y);
  clip.w = WTK_MIN(clip.w, canvas->clip[canvas->depth - 1].w);
  clip.h = WTK_MIN(clip.h, canvas->clip[canvas->depth - 1].h);

  /* New clipping rectangle. */
  canvas->clip[canvas->depth] = batch->clip = clip;

  /* Add to linked-list of batches. */
  batch->next = canvas->batch->next;
  canvas->batch->next = batch;

  /* Replace current batch. */
  canvas->batch = canvas->batch_at_depth[canvas->depth] = batch;
}

void wtk_canvas_pop(wtk_canvas_t *canvas)
{
  canvas->depth -= 1;

  /* Reinstate previous batch. */
  canvas->batch = canvas->batch_at_depth[canvas->depth];
}

static void wtk_canvas_flush(wtk_canvas_t *canvas)
{
  wtk_batch_t *batch = allocate_a_batch(&canvas->transient);

  /* TODO(mtwilliams): Timestamp batches. */
  batch->started = batch->completed = 0;

  /* Continuation of previous batch, so continue. */
  batch->clip = canvas->batch->clip;

  /* Add to linked-list of batches. Since current batch may not be at maximum
   * depth, we have to take care to link prior to children ensure correct
   * ordering.
   */
  batch->next = canvas->batch->next;
  canvas->batch->next = batch;

  /* Replace current batch. */
  canvas->batch = canvas->batch_at_depth[canvas->depth] = batch;
}

static void wtk_canvas_flush_if_nessecary(wtk_canvas_t *canvas,
                                          wtk_uint32_t verticies)
{
  if ((canvas->batch->limit - canvas->batch->count) >= verticies)
    /* Enough room. */
    return;

  wtk_canvas_flush(canvas);
}

static void wtk_canvas_vert(wtk_canvas_t *canvas,
                            wtk_uint16_t x,
                            wtk_uint16_t y,
                            wtk_color_t color)
{
  wtk_vertex_t *v = &canvas->batch->verticies[canvas->batch->count++];

  v->x = x;
  v->y = y;

  v->u = 0;
  v->v = 0;

  v->color = color.rgba;

  v->texture = 0;
}

void wtk_canvas_rect(wtk_canvas_t *canvas,
                     wtk_rectangle_t r,
                     wtk_color_t color,
                     wtk_uint32_t flags)
{
  wtk_canvas_flush_if_nessecary(canvas, 6);

  wtk_canvas_vert(canvas, r.x,       r.y,       color);
  wtk_canvas_vert(canvas, r.x + r.w, r.y,       color);
  wtk_canvas_vert(canvas, r.x,       r.y + r.h, color);
  wtk_canvas_vert(canvas, r.x,       r.y + r.h, color);
  wtk_canvas_vert(canvas, r.x + r.w, r.y,       color);
  wtk_canvas_vert(canvas, r.x + r.w, r.y + r.h, color);
}

WTK_END_EXTERN_C
