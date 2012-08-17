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

#include <wtk/wtk_button.h>

#include "_wtk_windows.h"
#include "_wtk_controls.h"

#include <wtk/wtk_mm.h>

static LRESULT CALLBACK wtk_button_proc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

int WTK_API wtk_button_init()
{
    return TRUE;
}

struct wtk_button* WTK_API wtk_button_create( int x, int y, int width, int height, struct wtk_control* parent )
{
    struct wtk_button* button = NULL;
    HWND hWnd;

    WTK_ASSERT(parent);

    hWnd = CreateWindowExA(0, "BUTTON", NULL, BS_DEFPUSHBUTTON | WS_VISIBLE | WS_CHILD, x, y, width, height, parent->hWnd, NULL, GetModuleHandle(0), 0);
    if( !hWnd ) return NULL;

    button = wtk_alloc(sizeof(struct wtk_button));
    memset((void*)button, 0, sizeof(struct wtk_button));
    button->control.type = WTK_CONTROL_TYPE(Button);
    button->control.hWnd = hWnd;

    SetPropA(hWnd, "_wtk_old_proc", (HANDLE)SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)&wtk_button_proc));
    SetPropA(hWnd, "_wtk_ctrl_ptr", (HANDLE)button);
    PostMessage(hWnd, WM_USER + 0, 0, 0);
    return button;
}

static LRESULT CALLBACK wtk_button_proc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{

    struct wtk_button* button = (struct wtk_button*)GetPropA(hWnd, "_wtk_ctrl_ptr");
    struct wtk_control* control = button ? &button->control : NULL;
    if( !button ) return CallWindowProc((WNDPROC)GetPropA(hWnd, "_wtk_old_proc"), hWnd, uMsg, wParam, lParam);

    switch( uMsg ) {
        case WM_USER + 0: {
            if( control->on_create_callback ) control->on_create_callback(control, WTK_EVENT(OnCreate));
        } break;

        case WM_DESTROY: {
            if( control->on_destroy_callback ) control->on_destroy_callback(control, WTK_EVENT(OnDestroy));
            wtk_free(button);
        } break;

        case WM_LBUTTONDOWN: {
            if( control->on_pressed_callback ) control->on_pressed_callback(control, WTK_EVENT(OnPressed), GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
            return CallWindowProc((WNDPROC)GetPropA(hWnd, "_wtk_old_proc"), hWnd, uMsg, wParam, lParam);
        } break;

        case WM_LBUTTONUP: {
            if( control->on_release_callback ) control->on_release_callback(control, WTK_EVENT(OnRelease), GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
            return CallWindowProc((WNDPROC)GetPropA(hWnd, "_wtk_old_proc"), hWnd, uMsg, wParam, lParam);
        } break;

        default: {
            return CallWindowProc((WNDPROC)GetPropA(hWnd, "_wtk_old_proc"), hWnd, uMsg, wParam, lParam);
        } break;
    }

    return 0;
}