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

#include <wtk/wtk_window.h>

#include <wtk/wtk_mm.h>
#include "_wtk_controls.h"

#include <string.h>

static LRESULT CALLBACK wtk_window_proc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

int WTK_API wtk_window_init()
{
    const WNDCLASSEX wcx = {
        sizeof(WNDCLASSEX),
        CS_HREDRAW | CS_VREDRAW,
        &wtk_window_proc,
        0, sizeof(wtk_control*),
        GetModuleHandle(0),
        LoadIcon(NULL, IDI_APPLICATION),
        LoadCursor(NULL, IDC_ARROW),
        (HBRUSH)(COLOR_WINDOW + 1),
        NULL,
        "_wtk_window",
        LoadIcon(NULL, IDI_APPLICATION)
    };

    return RegisterClassEx(&wcx) ? TRUE : FALSE;
}

struct wtk_window* WTK_API wtk_window_create( int x, int y, int width, int height, struct wtk_control* parent )
{
    struct wtk_window* window = NULL;
    HWND hWnd = CreateWindowExA(WS_EX_APPWINDOW | WS_EX_OVERLAPPEDWINDOW, "_wtk_window", NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, x, y, width, height, parent ? parent->hWnd : NULL, NULL, GetModuleHandle(0), 0);
    if( !hWnd ) return NULL;

    window = wtk_alloc(sizeof(struct wtk_window));
    memset((void*)window, 0, sizeof(struct wtk_window));
    window->control.type = WTK_CONTROL_TYPE(Window);
    window->control.hWnd = hWnd;

    SetWindowLongPtr(hWnd, 0, (LONG_PTR)window);
    PostMessage(hWnd, WM_USER + 0, 0, 0);
    return window;
}

static LRESULT CALLBACK wtk_window_proc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
    struct wtk_window* window = (struct wtk_window*)GetWindowLongPtr(hWnd, 0);
    struct wtk_control* control = window ? &window->control : NULL;
    if( !window ) return DefWindowProc(hWnd, uMsg, wParam, lParam);

    switch( uMsg ) {
        case WM_USER + 0: {
            if( control->on_create_callback ) control->on_create_callback(control, WTK_EVENT(OnCreate), NULL);
        } break;

        case WM_DESTROY: {
            if( control->on_destroy_callback ) control->on_destroy_callback(control, WTK_EVENT(OnDestroy), NULL);
        } break;

        case WM_CLOSE: {
            if( window->on_close_callback ) return window->on_close_callback(control, WTK_EVENT(OnClose), NULL);
        } break;

        default: {
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
        } break;
    }

    return 0;
}