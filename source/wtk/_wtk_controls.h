// =============================================================================
// This file is part of the Windowing Toolkit.
// Copyright (C) 2012 Michael Williams <devbug@bitbyte.ca>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
// =============================================================================

#ifndef __WTK_CONTROLS_H_
#define __WTK_CONTROLS_H_

#include "_wtk_windows.h"
#include "_wtk_font.h"
#include "_wtk_image.h"

#include <wtk/wtk_align.h>
#include <wtk/wtk_gdi.h>
#include <wtk/wtk_mouse.h>
#include <wtk/wtk_keyboard.h>
#include <wtk/wtk_textbox.h>

struct wtk_control {
    // Shared:
    wtk_control_type type;
    void* user_ptr;
    struct wtk_font* font;

    // Callbacks:
    int (WTK_API *on_create_callback)( struct wtk_control* control, wtk_event event );
    int (WTK_API *on_destroy_callback)( struct wtk_control* control, wtk_event event );
    int (WTK_API *on_paint_callback)( struct wtk_control* control, wtk_event event, struct wtk_gdi* gid );

    int (WTK_API *on_pressed_callback)( struct wtk_control* control, wtk_event event, wtk_mouse_btn mouse_btn, int x, int y );
    int (WTK_API *on_released_callback)( struct wtk_control* control, wtk_event event, wtk_mouse_btn mouse_btn, int x, int y );
    int (WTK_API *on_clicked_callback)( struct wtk_control* control, wtk_event event );

    int (WTK_API *on_mouse_moved_callback)( struct wtk_control* control, wtk_event event, int x, int y );
    int (WTK_API *on_mouse_scrolled_callback)( struct wtk_control* control, wtk_event event, int scroll );

    int (WTK_API *on_key_pressed_callback)( struct wtk_control* control, wtk_event event, wtk_key_code key_code, unsigned int special_keys );
    int (WTK_API *on_key_released_callback)( struct wtk_control* control, wtk_event event, wtk_key_code key_code, unsigned int special_keys );

    // Platform specific:
    HWND hWnd;
};

struct wtk_window {
    wtk_control control;

    // Shared:
    const char* title;
    struct wtk_icon* icons[2];

    // Callbacks:
    int (WTK_API *on_close_callback)( struct wtk_control* control, wtk_event event );
};

struct wtk_label {
    wtk_control control;

    // Shared:
    const char* text;
    wtk_align text_align;
};

struct wtk_button {
    wtk_control control;

    // Shared:
    const char* text;
    struct wtk_icon* icon;
    wtk_align text_h_align;
    wtk_align text_v_align;
};

struct wtk_checkbox {
    wtk_control control;

    // Shared:
    const char* text;
    struct wtk_icon* icon;
    wtk_align text_align;

    // Callbacks:
    int (WTK_API *on_value_changed_callback)( struct wtk_control* control, wtk_event event );
};

struct wtk_textbox {
    wtk_control control;

    // Shared:
    const char* text_buffer;
    wtk_textbox_type type;
    wtk_align text_align;
    int max_len;

    // Callbacks:
    int (WTK_API *on_value_changed_callback)( struct wtk_control* control, wtk_event event );
};

#endif // __WTK_CONTROLS_H_