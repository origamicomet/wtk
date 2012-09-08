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
#include "_wtk_msgs.h"

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

static void wtk_window_center( int* x, int* y, int width, int height )
{
    *x = (GetSystemMetrics(SM_CXSCREEN) - width) / 2;
    *y = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;
}

struct wtk_window* WTK_API wtk_window_create( int x, int y, int width, int height, struct wtk_control* parent )
{
    struct wtk_window* window = NULL;
    HWND hWnd = NULL;

    // TODO: Fix WS_CLIPCHILDREN rendering/drawing artifacts.

    wtk_window_adjust_size(&width, &height, WS_EX_APPWINDOW | WS_EX_OVERLAPPEDWINDOW, /*WS_CLIPCHILDREN |*/ WS_OVERLAPPEDWINDOW);
    if( x == WTK_WINDOW_CENTER && y == WTK_WINDOW_CENTER ) wtk_window_center(&x, &y, width, height);
    hWnd = CreateWindowExA(WS_EX_APPWINDOW | WS_EX_OVERLAPPEDWINDOW, "_wtk_window", NULL, /*WS_CLIPCHILDREN |*/ WS_OVERLAPPEDWINDOW, x, y, width, height, parent ? parent->hWnd : NULL, NULL, GetModuleHandle(0), 0);
    if( !hWnd ) return NULL;

    window = wtk_alloc(sizeof(struct wtk_window));
    memset((void*)window, 0, sizeof(struct wtk_window));
    window->control.type = WTK_CONTROL_TYPE(Window);
    window->control.hWnd = hWnd;
    window->control.font = wtk_font_default();
    window->control.resizable = TRUE;

    SetPropA(hWnd, "_wtk_ctrl_ptr", (HANDLE)window);
    PostMessage(hWnd, WM_SETFONT, (WPARAM)window->control.font->hFont, TRUE);
    PostMessage(hWnd, WTK_ON_CREATE, 0, 0);
    return window;
}

static BOOL CALLBACK wtk_on_layout_change_proc( HWND hWnd, LPARAM lParam ) {
    SendMessage(hWnd, WTK_ON_LAYOUT_CHANGED, 0, 0);
    return TRUE;
}

static LRESULT CALLBACK wtk_window_proc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
    struct wtk_control* control = (struct wtk_control*)GetPropA(hWnd, "_wtk_ctrl_ptr");
    struct wtk_window* window = (struct wtk_window*)control;
    if( !control ) return DefWindowProc(hWnd, uMsg, wParam, lParam);

    switch( uMsg ) {
        case WTK_ON_CREATE: {
            HWND hWndParent = GetParent(hWnd);
            if( control->on_create_callback ) control->on_create_callback(control, WTK_EVENT(OnCreate));
            if( hWndParent ) SendMessage(hWndParent, WTK_ON_LAYOUT_CHANGED, 0, 0);
        } break;

        case WTK_ON_LAYOUT_CHANGED: {
            EnumChildWindows(hWnd, &wtk_on_layout_change_proc, 0);
            if( control->on_layout_changed_callback ) control->on_layout_changed_callback(control, WTK_EVENT(OnLayoutChanged));
        } break;

        case WM_DESTROY: {
            if( control->on_destroy_callback ) control->on_destroy_callback(control, WTK_EVENT(OnDestroy));
            if( window->menu ) wtk_control_destroy((struct wtk_control*)window->menu);
            wtk_free(window);
        } break;

        case WM_SIZE: {
            RECT client_rect;
            int width, height;
            GetClientRect(hWnd, &client_rect);
            width = client_rect.right;
            height = client_rect.bottom;

            switch( wParam ) {
                case SIZE_MINIMIZED: {
                    if( window->on_minimized_callback ) window->on_minimized_callback(control, WTK_EVENT(OnMinimized), width, height);
                    SendMessage(hWnd, WTK_ON_LAYOUT_CHANGED, 0, 0);
                } break;

                case SIZE_MAXIMIZED: {
                    if( window->on_maximized_callback ) window->on_maximized_callback(control, WTK_EVENT(OnMaximized), width, height);
                    SendMessage(hWnd, WTK_ON_LAYOUT_CHANGED, 0, 0);
                } break;

                case SIZE_RESTORED: {
                    if( window->on_resized_callback ) window->on_resized_callback(control, WTK_EVENT(OnResized), width, height);
                    SendMessage(hWnd, WTK_ON_LAYOUT_CHANGED, 0, 0);
                } break;
            }
        } break;

        case WM_CLOSE: {
            if( window->on_close_callback ) if( window->on_close_callback(control, WTK_EVENT(OnClose)) ) DestroyWindow(hWnd);
        } break;

        case WM_MENUCOMMAND: {
            struct wtk_control* child_control;
            MENUITEMINFO menu_item_info = { sizeof(MENUITEMINFO), MIIM_ID, 0, };
            GetMenuItemInfo((HMENU)lParam, (UINT)wParam, TRUE, &menu_item_info);
            child_control = ((struct wtk_control*)menu_item_info.wID);
            if( child_control->on_clicked_callback ) child_control->on_clicked_callback(child_control, WTK_EVENT(OnClicked));
        } break;

        case WM_COMMAND: {
            switch( HIWORD(wParam) ) {
                case BN_CLICKED: {
                    struct wtk_control* child_control = (struct wtk_control*)GetPropA((HWND)lParam, "_wtk_ctrl_ptr");

                    switch( child_control->type ) {
                        case WTK_CONTROL_TYPE(Button): {
                            if( child_control->on_clicked_callback ) child_control->on_clicked_callback(child_control, WTK_EVENT(OnClicked));
                        } break;

                        case WTK_CONTROL_TYPE(CheckBox): {
                            struct wtk_checkbox* cb_control = ((struct wtk_checkbox*)child_control);
                            if( cb_control->on_value_changed_callback ) cb_control->on_value_changed_callback(child_control, WTK_EVENT(OnClicked));
                        } break;
                    }
                } break;

                case EN_CHANGE: {
                    struct wtk_control* child_control = (struct wtk_control*)GetPropA((HWND)lParam, "_wtk_ctrl_ptr");
                    struct wtk_textbox* textbox = (struct wtk_textbox*)child_control;
                    if( textbox->on_value_changed_callback ) textbox->on_value_changed_callback(child_control, WTK_EVENT(OnValueChanged));
                } break;

                case LBN_SELCHANGE: { // CBN_SELCHANGE
                    struct wtk_control* child_control = (struct wtk_control*)GetPropA((HWND)lParam, "_wtk_ctrl_ptr");

                    switch( child_control->type ) {
                        case WTK_CONTROL_TYPE(ListBox): {
                            struct wtk_listbox* listbox = (struct wtk_listbox*)child_control;
                            if( listbox->on_selection_changed_callback ) {
                                const unsigned int num_selections = (unsigned int)SendMessage(child_control->hWnd, LB_GETSELCOUNT, 0, 0);
                                listbox->on_selection_changed_callback(child_control, WTK_EVENT(OnSelectionChanged), num_selections);
                            }
                        } break;

                        case WTK_CONTROL_TYPE(ComboBox): {
                            struct wtk_combobox* combobox = (struct wtk_combobox*)child_control;
                            if( combobox->on_selection_changed_callback ) {
                                combobox->on_selection_changed_callback(child_control, WTK_EVENT(OnSelectionChanged), 1);
                            }
                        } break;
                    }


                } break;
            }
        } break;

        default: {
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
        } break;
    }

    return 0;
}
