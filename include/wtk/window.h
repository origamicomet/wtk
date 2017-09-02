/*===-- wtk/window.h ----------------------------------------*- mode: C -*-===*/
/*                                                                            */
/*                                     _   _                                  */
/*                               _ _ _| |_| |_                                */
/*                              | | | |  _| '_|                               */
/*                              |_____|_| |_,_|                               */
/*                                                                            */
/*       This file is distributed under the terms described in LICENSE.       */
/*                                                                            */
/*===----------------------------------------------------------------------===*/

#ifndef _WTK_WINDOW_H_
#define _WTK_WINDOW_H_

#include "wtk/foundation.h"

#include "wtk/handle.h"

/* REFACTOR(mtwilliams): Forward declare. */
#include "wtk/canvas.h"

WTK_BEGIN_EXTERN_C

typedef enum wtk_window_event_type {
  WTK_WINDOW_EVENT_OPENED,
  WTK_WINDOW_EVENT_CLOSED,
  WTK_WINDOW_EVENT_VISIBILITY,
  WTK_WINDOW_EVENT_MOVED,
  WTK_WINDOW_EVENT_RESIZED,
} wtk_window_event_type_t;

typedef struct wtk_window_event {
  wtk_window_event_type_t type;

  union {
    struct {
    } opened;

    struct {
      unsigned destroying;
    } closed;

    struct {
      unsigned visible;
    } visibility;
  };
} wtk_window_event_t;

typedef wtk_uint32_t (*wtk_window_event_handler_t)(wtk_handle_t handle,
                                                   const wtk_window_event_t *event,
                                                   void *context);

typedef struct wtk_window_desc {
  const char *title;

  wtk_uint32_t x;
  wtk_uint32_t y;
  wtk_uint32_t width;
  wtk_uint32_t height;

  unsigned resizeable;
  unsigned closable;

  wtk_window_event_handler_t event_handler;
  void *event_handler_context;
} wtk_window_desc_t;

extern WTK_PUBLIC
  wtk_handle_t wtk_window_open(
    const wtk_window_desc_t *desc);

extern WTK_PUBLIC
  void wtk_window_close(
    wtk_handle_t handle);

extern WTK_PUBLIC
  unsigned wtk_window_is_resizeable(
    wtk_handle_t handle);

extern WTK_PUBLIC
  unsigned wtk_window_is_closable(
    wtk_handle_t handle);

extern WTK_PUBLIC
  wtk_uintptr_t wtk_window_to_native(
    wtk_handle_t handle);

extern WTK_PUBLIC
  wtk_canvas_t *wtk_window_to_canvas(
    wtk_handle_t handle);

WTK_END_EXTERN_C

#endif /* _WTK_WINDOW_H_ */
