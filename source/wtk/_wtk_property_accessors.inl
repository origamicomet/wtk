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

#include "_wtk_controls.h"

#include <stdarg.h>

// =============================================================================
// WTK_CONTROL_PROP_UserPtr
// =============================================================================

static void WTK_API wtk_prop_user_ptr_getter( struct wtk_control* control, va_list args )
{
    void** out;
    out = va_arg(args, void**);
    *out = control->user_ptr;
}

static void WTK_API wtk_prop_user_ptr_setter( struct wtk_control* control, va_list args )
{
    void* user_ptr;
    user_ptr = va_arg(args, void*);
    control->user_ptr = user_ptr;
}

// =============================================================================
// WTK_CONTROL_PROP_Position
// =============================================================================

static void WTK_API wtk_prop_position_getter( struct wtk_control* control, va_list args )
{
    HWND hWndParent;
    int *x_out, *y_out;
    
    x_out = va_arg(args, int*);
    y_out = va_arg(args, int*);

    hWndParent = GetParent(control->hWnd);
    if( hWndParent ) {
        POINT p = { 0, };
        MapWindowPoints(control->hWnd, hWndParent, &p, 1);
        *x_out = p.x; *y_out = p.y;
    } else {
        RECT rect;
        GetWindowRect(control->hWnd, &rect);
        *x_out = rect.left; *y_out = rect.top;
    }
}

static void WTK_API wtk_prop_position_setter( struct wtk_control* control, va_list args )
{
    int x, y;
    
    x = va_arg(args, int);
    y = va_arg(args, int);

    SetWindowPos(control->hWnd, 0, x, y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
}

// =============================================================================
// WTK_CONTROL_PROP_Size
// =============================================================================

static void WTK_API wtk_prop_size_getter( struct wtk_control* control, va_list args )
{
    RECT rect;
    int *width_out, *height_out;
    
    width_out = va_arg(args, int*);
    height_out = va_arg(args, int*);

    GetWindowRect(control->hWnd, &rect);

    *width_out = rect.right - rect.left - 1;
    *height_out = rect.bottom - rect.top - 1;
}

static void WTK_API wtk_prop_size_setter( struct wtk_control* control, va_list args )
{
    int width, height;
    
    width = va_arg(args, int);
    height = va_arg(args, int);

    SetWindowPos(control->hWnd, 0, 0, 0, width, height, SWP_NOZORDER | SWP_NOMOVE);
}

// =============================================================================
// WTK_CONTROL_PROP_Font
// =============================================================================

static void WTK_API wtk_prop_font_getter( struct wtk_control* control, va_list args )
{
    struct wtk_font** out;
    out = va_arg(args, struct wtk_font**);
    *out = control->font;
}

static void WTK_API wtk_prop_font_setter( struct wtk_control* control, va_list args )
{
    struct wtk_font* font;
    font = va_arg(args, struct wtk_font*);
    PostMessage(control->hWnd, WM_SETFONT, (WPARAM)font->hFont, TRUE);
    control->font = font;
}

// =============================================================================
// WTK_CONTROL_PROP_Title
// =============================================================================

static void WTK_API wtk_prop_title_getter( struct wtk_control* control, va_list args )
{
    const char** out;

    WTK_ASSERT(control->type == WTK_CONTROL_TYPE(Window));

    out = va_arg(args, const char**);
    *out = ((struct wtk_window*)control)->title;
}

static void WTK_API wtk_prop_title_setter( struct wtk_control* control, va_list args )
{
    const char* value;

    WTK_ASSERT(control->type == WTK_CONTROL_TYPE(Window));

    value = va_arg(args, const char*);
    SetWindowTextA(control->hWnd, value);
    ((struct wtk_window*)control)->title = value;
}

// =============================================================================
// WTK_CONTROL_PROP_Text
// =============================================================================

static void WTK_API wtk_prop_text_getter( struct wtk_control* control, va_list args )
{
    const char** out;

    WTK_ASSERT(
        ( control->type == WTK_CONTROL_TYPE(Label) ||
          control->type == WTK_CONTROL_TYPE(Button) )
    );

    out = va_arg(args, const char**);

    switch( control->type ) {
        case WTK_CONTROL_TYPE(Label): {
            *out = ((struct wtk_button*)control)->text;
        } break;

        case WTK_CONTROL_TYPE(Button): {
            *out = ((struct wtk_button*)control)->text;
        } break;
    }
}

static void WTK_API wtk_prop_text_setter( struct wtk_control* control, va_list args )
{
    const char* value;

    WTK_ASSERT(
        ( control->type == WTK_CONTROL_TYPE(Label) ||
          control->type == WTK_CONTROL_TYPE(Button) )
    );

    value = va_arg(args, const char*);
    SetWindowTextA(control->hWnd, value);
    ((struct wtk_button*)control)->text = value;
}