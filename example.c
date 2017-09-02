/*===-- example.c -------------------------------------------*- mode: C -*-===*/
/*                                                                            */
/*                                     _   _                                  */
/*                               _ _ _| |_| |_                                */
/*                              | | | |  _| '_|                               */
/*                              |_____|_| |_,_|                               */
/*                                                                            */
/*       This file is distributed under the terms described in LICENSE.       */
/*                                                                            */
/*===----------------------------------------------------------------------===*/

#include <stdlib.h>

#include "wtk.h"

static wtk_uint32_t my_event_handler(wtk_handle_t window,
                                     const wtk_window_event_t *e,
                                     void *context) {

  switch (e->type) {
    case WTK_WINDOW_EVENT_DRAW: {
      wtk_canvas_rect(e->draw.canvas, {0,       0,  1280, 720}, wtk_rgb(127, 127, 127), 0);
      wtk_canvas_rect(e->draw.canvas, {0 * 128, 0,   128, 128}, wtk_rgb(255, 0, 0), 0);
      wtk_canvas_rect(e->draw.canvas, {1 * 128, 0,   128, 128}, wtk_rgb(0, 255, 0), 0);
      wtk_canvas_rect(e->draw.canvas, {2 * 128, 0,   128, 128}, wtk_rgb(0, 0, 255), 0);
      wtk_canvas_rect(e->draw.canvas, {3 * 128, 0,   128, 128}, wtk_rgb(127, 0, 0), 0);
      wtk_canvas_rect(e->draw.canvas, {4 * 128, 0,   128, 128}, wtk_rgb(0, 127, 0), 0);
      wtk_canvas_rect(e->draw.canvas, {5 * 128, 0,   128, 128}, wtk_rgb(0, 0, 127), 0);
      wtk_canvas_push(e->draw.canvas, {768 + 32, 32, 384 - 32 - 32, 64});
        wtk_canvas_rect(e->draw.canvas, {6 * 128, 0,   128, 128}, wtk_rgb(63, 0, 0), 0);
        wtk_canvas_rect(e->draw.canvas, {7 * 128, 0,   128, 128}, wtk_rgb(0, 63, 0), 0);
        wtk_canvas_push(e->draw.canvas, {1024 + 16, 16, 128 - 16 - 16, 128 - 16});
          wtk_canvas_rect(e->draw.canvas, {8 * 128, 0,   128, 128}, wtk_rgb(0, 0, 63), 0);
        wtk_canvas_pop(e->draw.canvas);
      wtk_canvas_pop(e->draw.canvas);
    } return 0;
  }

  return 0;
}

static wtk_handle_t open_a_window(void) {
  wtk_window_desc_t desc;

  desc.title = "Example";

  desc.x = 0;
  desc.y = 0;

  desc.width = 1280;
  desc.height = 720;

  desc.resizeable = 1;

  desc.closable = 0;

  desc.event_handler = &my_event_handler;
  desc.event_handler_context = NULL;

  return wtk_window_open(&desc);
}

int main(int argc, const char *argv[]) {
  (void)argc;
  (void)argv;

  wtk_app_init();

  wtk_handle_t window = open_a_window();

  while (1)
    wtk_app_pump();

  wtk_app_shutdown();

  return EXIT_SUCCESS;
}
