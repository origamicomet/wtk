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

#include <wtk/wtk_control.h>

#include "_wtk_windows.h"
#include "_wtk_controls.h"

#include <wtk/wtk_mm.h>
#include <wtk/wtk_font.h>

#include <stdarg.h>

static LRESULT CALLBACK wtk_control_proc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

int WTK_API wtk_control_init()
{
    const WNDCLASSEX wcx = {
        sizeof(WNDCLASSEX),
        CS_HREDRAW | CS_VREDRAW,
        &wtk_control_proc,
        0, sizeof(wtk_control*),
        GetModuleHandle(0),
        LoadIcon(NULL, IDI_APPLICATION),
        LoadCursor(NULL, IDC_ARROW),
        (HBRUSH)(COLOR_WINDOW + 1),
        NULL,
        "_wtk_control",
        LoadIcon(NULL, IDI_APPLICATION)
    };

    return RegisterClassEx(&wcx) ? TRUE : FALSE;
}

struct wtk_control* WTK_API wtk_control_create( int x, int y, unsigned int width, unsigned int height, struct wtk_control* parent )
{
    HWND hWnd;
    struct wtk_control* control;

    WTK_ASSERT(parent);

    hWnd = CreateWindowEx(0, "_wtk_control", NULL, WS_CHILD | WS_VISIBLE, x, y, width, height, parent->hWnd, NULL, GetModuleHandle(0), 0);
    if( !hWnd ) return NULL;

    control = wtk_alloc(sizeof(wtk_control));
    memset((void*)control, 0, sizeof(struct wtk_control));
    control->type = WTK_CONTROL_TYPE(Base);
    control->hWnd = hWnd;
    control->font = wtk_font_default();

    SetWindowLongPtr(hWnd, 0, (LONG_PTR)control);
    PostMessage(hWnd, WM_SETFONT, (WPARAM)control->font->hFont, TRUE);
    PostMessage(hWnd, WM_USER + 0, 0, 0);
    return control;
}

void WTK_API wtk_control_destroy( struct wtk_control* control )
{
    WTK_ASSERT(control);
    DestroyWindow(control->hWnd);
}

void* WTK_API wtk_control_get_user_ptr( struct wtk_control* control )
{
    WTK_ASSERT(control);
    return control->user_ptr;
}

void WTK_API wtk_control_set_user_ptr( struct wtk_control* control, void* user_ptr )
{
    WTK_ASSERT(control);
    control->user_ptr = user_ptr;
}

void WTK_API wtk_control_get_position( struct wtk_control* control, int* x, int* y )
{
    HWND hWndParent;

    WTK_ASSERT(control);
    WTK_ASSERT(x);
    WTK_ASSERT(y);

    hWndParent = GetParent(control->hWnd);
    if( hWndParent ) {
        POINT p = { 0, };
        MapWindowPoints(control->hWnd, hWndParent, &p, 1);
        *x = p.x; *y = p.y;
    } else {
        RECT rect;
        GetWindowRect(control->hWnd, &rect);
        *x = rect.left; *y = rect.top;
    }
}

void WTK_API wtk_control_set_position( struct wtk_control* control, int x, int y )
{
    WTK_ASSERT(control);
    SetWindowPos(control->hWnd, 0, x, y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
}

void WTK_API wtk_control_get_size( struct wtk_control* control, unsigned int* width, unsigned int* height )
{
    RECT rect;

    WTK_ASSERT(control);
    WTK_ASSERT(width);
    WTK_ASSERT(height);
    
    GetWindowRect(control->hWnd, &rect);

    *width = rect.right - rect.left - 1;
    *height = rect.bottom - rect.top - 1;
}

void WTK_API wtk_control_set_size( struct wtk_control* control, unsigned int width, unsigned int height )
{
    WTK_ASSERT(control);
    SetWindowPos(control->hWnd, 0, 0, 0, width, height, SWP_NOZORDER | SWP_NOMOVE);
}

#include "_wtk_property_accessors.inl"

typedef struct {
    void (WTK_API *getter)( struct wtk_control*, va_list );
    void (WTK_API *setter)( struct wtk_control*, va_list );
} wtk_property_accessors;

static wtk_property_accessors _property_accessors[WTK_CONTROL_PROP_COUNT] = {
    { NULL, NULL },                                     // WTK_CONTROL_PROP_Invalid
    { &wtk_prop_font_getter, &wtk_prop_font_setter },   // WTK_CONTROL_PROP_Font
    { &wtk_prop_title_getter, &wtk_prop_title_setter }, // WTK_CONTROL_PROP_Title
    { &wtk_prop_text_getter, &wtk_prop_text_setter },   // WTK_CONTROL_PROP_Text
};

void WTK_API wtk_control_get_property( struct wtk_control* control, wtk_control_property property, ... )
{
    va_list args;

    WTK_ASSERT(control);
    WTK_ASSERT(((property > WTK_CONTROL_PROP_Invalid) && (property < WTK_CONTROL_PROP_COUNT)));

    va_start(args, property);
    _property_accessors[property].getter(control, args);
    va_end(args);
}

void WTK_API wtk_control_set_property( struct wtk_control* control, wtk_control_property property, ... )
{
    va_list args;

    WTK_ASSERT(control);
    WTK_ASSERT(((property > WTK_CONTROL_PROP_Invalid) && (property < WTK_CONTROL_PROP_COUNT)));

    va_start(args, property);
    _property_accessors[property].setter(control, args);
    va_end(args);
}

#include "_wtk_event_accessors.inl"

typedef struct {
    void (WTK_API *setter)( struct wtk_control*, wtk_event_callback );
} wtk_event_accessors;

static wtk_event_accessors _event_accessors[WTK_EVENT_COUNT] = {
    { NULL },                         // WTK_EVENT_Invalid
    { &wtk_event_on_create_setter },  // WTK_EVENT_OnCreate
    { &wtk_event_on_destroy_setter }, // WTK_EVENT_OnDestroy
    { &wtk_event_on_close_setter },   // WTK_EVENT_OnClose
    { &wtk_event_on_pressed_setter }, // WTK_EVENT_OnPressed
    { &wtk_event_on_release_setter }, // WTK_EVENT_OnRelease
    { &wtk_event_on_clicked_setter }, // WTK_EVENT_OnClicked
};

void WTK_API wtk_control_set_callback( struct wtk_control* control, wtk_event event, wtk_event_callback callback )
{
    WTK_ASSERT(control);
    WTK_ASSERT(((event > WTK_EVENT_Invalid) && (event < WTK_EVENT_COUNT)));
    _event_accessors[event].setter(control, callback);
}

static LRESULT CALLBACK wtk_control_proc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
    struct wtk_control* control = (struct wtk_control*)GetWindowLongPtr(hWnd, 0);
    if( !control ) return DefWindowProc(hWnd, uMsg, wParam, lParam);

    switch( uMsg ) {
        case WM_USER + 0: {
            if( control->on_create_callback ) control->on_create_callback(control, WTK_EVENT(OnCreate));
        } break;

        case WM_DESTROY: {
            if( control->on_destroy_callback ) control->on_destroy_callback(control, WTK_EVENT(OnDestroy));
            wtk_free(control);
        } break;

        default: {
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
        } break;
    }

    return 0;
}