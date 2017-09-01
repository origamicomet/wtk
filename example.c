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

static wtk_handle_t open_a_window(void) {
  wtk_window_desc_t desc;

  desc.title = "Example";

  desc.x = 0;
  desc.y = 0;

  desc.width = 1280;
  desc.height = 720;

  desc.resizeable = 1;

  desc.closable = 0;

  desc.event_handler = NULL;
  desc.event_handler_context = NULL;

  return wtk_window_open(&desc);
}

int main(int argc, const char *argv[]) {
  (void)argc;
  (void)argv;

  wtk_app_init();

  wtk_handle_t window = open_a_window();

  wtk_canvas_t *canvas = wtk_window_to_canvas(window);

  while (1) {
    wtk_canvas_begin(canvas);
      wtk_canvas_rect(canvas, {0,       0,  1280, 720}, 0x7f7f7fff, 0);
      wtk_canvas_rect(canvas, {0 * 128, 0,   128, 128}, 0xff0000ff, 0);
      wtk_canvas_rect(canvas, {1 * 128, 0,   128, 128}, 0x00ff00ff, 0);
      wtk_canvas_rect(canvas, {2 * 128, 0,   128, 128}, 0x0000ffff, 0);
      wtk_canvas_rect(canvas, {3 * 128, 0,   128, 128}, 0x7f0000ff, 0);
      wtk_canvas_rect(canvas, {4 * 128, 0,   128, 128}, 0x007f00ff, 0);
      wtk_canvas_rect(canvas, {5 * 128, 0,   128, 128}, 0x00007fff, 0);
      wtk_canvas_push(canvas, {768 + 32, 32, 384 - 32 - 32, 64});
        wtk_canvas_rect(canvas, {6 * 128, 0,   128, 128}, 0x3f0000ff, 0);
        wtk_canvas_rect(canvas, {7 * 128, 0,   128, 128}, 0x003f00ff, 0);
        wtk_canvas_rect(canvas, {8 * 128, 0,   128, 128}, 0x00003fff, 0);
      wtk_canvas_pop(canvas);
    wtk_canvas_end(canvas);

    wtk_app_pump();
  }

  wtk_app_shutdown();

  return EXIT_SUCCESS;
}
