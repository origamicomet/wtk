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

#include "_wtk_windows.h"
#include "_wtk_controls.h"

#include <wtk/wtk_mm.h>
#include <wtk/wtk_font.h>
#include <wtk/wtk_mouse.h>
#include <wtk/wtk_keyboard.h>

static LRESULT CALLBACK wtk_window_proc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

int WTK_API wtk_window_init()
{
    const WNDCLASSEX wcx = {
        sizeof(WNDCLASSEX),
        CS_HREDRAW | CS_VREDRAW,
        &wtk_window_proc,
        0, 0,
        GetModuleHandle(0),
        LoadIcon(NULL, IDI_APPLICATION),
        LoadCursor(NULL, IDC_ARROW),
        (HBRUSH)(COLOR_WINDOW),
        NULL,
        "_wtk_window",
        LoadIcon(NULL, IDI_APPLICATION)
    };

    return RegisterClassEx(&wcx) ? TRUE : FALSE;
}

static void wtk_window_adjust_size( int* width, int* height, DWORD dwExStyles, DWORD dwStyles )
{
    RECT client_area = { 0, 0, *width - 1, *height - 1 };
    AdjustWindowRectEx(&client_area, dwStyles, FALSE, dwExStyles);
    *width = client_area.right - client_area.left + 1;
    *height = client_area.bottom - client_area.top + 1;
}

struct wtk_window* WTK_API wtk_window_create( int x, int y, int width, int height, struct wtk_control* parent )
{
    struct wtk_window* window = NULL;
    HWND hWnd = NULL;

    wtk_window_adjust_size(&width, &height, WS_EX_APPWINDOW | WS_EX_OVERLAPPEDWINDOW, WS_OVERLAPPEDWINDOW | WS_VISIBLE);
    hWnd = CreateWindowExA(WS_EX_APPWINDOW | WS_EX_OVERLAPPEDWINDOW, "_wtk_window", NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, x, y, width, height, parent ? parent->hWnd : NULL, NULL, GetModuleHandle(0), 0);
    if( !hWnd ) return NULL;

    window = wtk_alloc(sizeof(struct wtk_window));
    memset((void*)window, 0, sizeof(struct wtk_window));
    window->control.type = WTK_CONTROL_TYPE(Window);
    window->control.hWnd = hWnd;
    window->control.font = wtk_font_default();

    SetPropA(hWnd, "_wtk_ctrl_ptr", (HANDLE)window);
    PostMessage(hWnd, WM_SETFONT, (WPARAM)window->control.font->hFont, TRUE);
    PostMessage(hWnd, WM_USER + 0, 0, 0);
    return window;
}

static LRESULT CALLBACK wtk_window_proc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
    struct wtk_window* window = (struct wtk_window*)GetPropA(hWnd, "_wtk_ctrl_ptr");
    struct wtk_control* control = window ? &window->control : NULL;
    if( !window ) return DefWindowProc(hWnd, uMsg, wParam, lParam);

    switch( uMsg ) {
        case WM_USER + 0: {
            if( control->on_create_callback ) control->on_create_callback(control, WTK_EVENT(OnCreate));
        } break;

        case WM_DESTROY: {
            if( control->on_destroy_callback ) control->on_destroy_callback(control, WTK_EVENT(OnDestroy));
            wtk_free(window);
        } break;

        case WM_CLOSE: {
            if( window->on_close_callback ) return window->on_close_callback(control, WTK_EVENT(OnClose));
        } break;

        case WM_COMMAND: {
            switch( HIWORD(wParam) ) {
                case BN_CLICKED: {
                    struct wtk_control* btn_control = (struct wtk_control*)GetPropA((HWND)lParam, "_wtk_ctrl_ptr");

                    switch( btn_control->type ) {
                        case WTK_CONTROL_TYPE(Button): {
                            if( btn_control->on_clicked_callback ) btn_control->on_clicked_callback(btn_control, WTK_EVENT(OnClicked));
                        } break;

                        case WTK_CONTROL_TYPE(Checkbox): {
                            struct wtk_checkbox* cb_control = ((struct wtk_checkbox*)btn_control);
                            if( cb_control->on_value_changed_callback ) cb_control->on_value_changed_callback(btn_control, WTK_EVENT(OnClicked));
                        } break;
                    }
                } break;

                case EN_CHANGE: {
                    struct wtk_textbox* textbox = (struct wtk_textbox*)GetPropA((HWND)lParam, "_wtk_ctrl_ptr");
                    struct wtk_control* tb_control = &textbox->control;
                    if( textbox->on_value_changed_callback ) textbox->on_value_changed_callback(tb_control, WTK_EVENT(OnValueChanged));
                } break;
            }
        } break;

        default: {
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
        } break;
    }

    return 0;
}