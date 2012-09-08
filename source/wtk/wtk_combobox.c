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

#include <wtk/wtk_combobox.h>

#include "_wtk_windows.h"
#include "_wtk_controls.h"
#include "_wtk_msgs.h"
#include "_wtk_layout.h"

#include <wtk/wtk_mm.h>
#include <wtk/wtk_align.h>
#include <wtk/wtk_font.h>

static LRESULT CALLBACK wtk_combobox_proc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

int WTK_API wtk_combobox_init()
{
    return TRUE;
}

struct wtk_combobox* WTK_API wtk_combobox_create( int x, int y, int width, int height, struct wtk_control* parent )
{
    struct wtk_combobox* combobox = NULL;
    HWND hWnd;

    WTK_ASSERT(parent);

    hWnd = CreateWindowExA(0, "COMBOBOX", NULL, CBS_HASSTRINGS | CBS_DROPDOWNLIST | WS_VISIBLE | WS_CHILD, x, y, width, height, parent->hWnd, NULL, GetModuleHandle(0), 0);
    if( !hWnd ) return NULL;

    combobox = wtk_alloc(sizeof(struct wtk_combobox));
    memset((void*)combobox, 0, sizeof(struct wtk_combobox));
    combobox->control.type = WTK_CONTROL_TYPE(ComboBox);
    combobox->control.hWnd = hWnd;
    combobox->control.font = wtk_font_default();

    SetPropA(hWnd, "_wtk_old_proc", (HANDLE)SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)&wtk_combobox_proc));
    SetPropA(hWnd, "_wtk_ctrl_ptr", (HANDLE)combobox);
    PostMessage(hWnd, WM_SETFONT, (WPARAM)combobox->control.font->hFont, TRUE);
    PostMessage(hWnd, WTK_ON_CREATE, 0, 0);
    return combobox;
}

wtk_combobox_item WTK_API wtk_combobox_insert( struct wtk_combobox* combobox, const char* text, void* user_ptr )
{
    LRESULT result;

    WTK_ASSERT(combobox);

    result = SendMessage(combobox->control.hWnd, CB_ADDSTRING, 0, (LPARAM)text);
    if( result == CB_ERR || result == CB_ERRSPACE ) return 0;
    SendMessage(combobox->control.hWnd, CB_SETITEMDATA, (WPARAM)result, (LPARAM)user_ptr);
    return (wtk_combobox_item)(result + 1);
}

void WTK_API wtk_combobox_remove( struct wtk_combobox* combobox, wtk_combobox_item id )
{
    WTK_ASSERT(combobox);
    WTK_ASSERT(id != 0);

    SendMessage(combobox->control.hWnd, CB_DELETESTRING, (WPARAM)(id - 1), 0);
}

static BOOL CALLBACK wtk_on_layout_change_proc( HWND hWnd, LPARAM lParam ) {
    SendMessage(hWnd, WTK_ON_LAYOUT_CHANGED, 0, 0);
    return TRUE;
}

static LRESULT CALLBACK wtk_combobox_proc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
    struct wtk_control* control = (struct wtk_control*)GetPropA(hWnd, "_wtk_ctrl_ptr");
    struct wtk_combobox* combobox = (struct wtk_combobox*)control;
    if( !control ) return DefWindowProc(hWnd, uMsg, wParam, lParam);

    switch( uMsg ) {
        case WTK_ON_CREATE: {
            HWND hWndParent = GetParent(hWnd);
            if( control->on_create_callback ) control->on_create_callback(control, WTK_EVENT(OnCreate));
            if( hWndParent ) SendMessage(hWndParent, WTK_ON_LAYOUT_CHANGED, 0, 0);
        } break;

        case WTK_ON_LAYOUT_CHANGED: {
            wtk_on_layout_changed(control);
            EnumChildWindows(hWnd, &wtk_on_layout_change_proc, 0);
            if( control->on_layout_changed_callback ) control->on_layout_changed_callback(control, WTK_EVENT(OnLayoutChanged));
        } break;

        case WM_DESTROY: {
            if( control->on_destroy_callback ) control->on_destroy_callback(control, WTK_EVENT(OnDestroy));
            wtk_free(combobox);
        } break;

        default: {
            return CallWindowProc((WNDPROC)GetPropA(hWnd, "_wtk_old_proc"), hWnd, uMsg, wParam, lParam);
        } break;
    }

    return 0;
}
