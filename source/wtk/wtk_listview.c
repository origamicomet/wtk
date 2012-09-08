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

#include <wtk/wtk_listview.h>

#include "_wtk_windows.h"
#include "_wtk_controls.h"
#include "_wtk_msgs.h"
#include "_wtk_layout.h"

#include <wtk/wtk_mm.h>
#include <wtk/wtk_align.h>
#include <wtk/wtk_font.h>

#include <stdarg.h>

static LRESULT CALLBACK wtk_listview_proc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

int WTK_API wtk_listview_init()
{
    return TRUE;
}

struct wtk_listview* WTK_API wtk_listview_create( int x, int y, int width, int height, struct wtk_control* parent )
{
    struct wtk_listview* listview = NULL;
    HWND hWnd;

    WTK_ASSERT(parent);

    hWnd = CreateWindowExA(0, WC_LISTVIEWA, NULL, LVS_REPORT | LVS_SINGLESEL | WS_BORDER | WS_VSCROLL | WS_HSCROLL | WS_VISIBLE | WS_CHILD, x, y, width, height, parent->hWnd, NULL, GetModuleHandle(0), 0);
    if( !hWnd ) return NULL;

    listview = wtk_alloc(sizeof(struct wtk_listview));
    memset((void*)listview, 0, sizeof(struct wtk_listview));
    listview->control.type = WTK_CONTROL_TYPE(ListView);
    listview->control.hWnd = hWnd;
    listview->control.font = wtk_font_default();

    SetPropA(hWnd, "_wtk_old_proc", (HANDLE)SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)&wtk_listview_proc));
    SetPropA(hWnd, "_wtk_ctrl_ptr", (HANDLE)listview);
    PostMessage(hWnd, WM_SETFONT, (WPARAM)listview->control.font->hFont, TRUE);
    PostMessage(hWnd, WTK_ON_CREATE, 0, 0);
    ListView_SetExtendedListViewStyle(hWnd, LVS_EX_GRIDLINES | LVS_EX_SUBITEMIMAGES | LVS_EX_FULLROWSELECT);

    return listview;
}

wtk_listview_column WTK_API wtk_listview_insert_column( struct wtk_listview* listview, const char* text, unsigned width )
{
    LVCOLUMN lvc = { 0, };

    WTK_ASSERT(listview);
    WTK_ASSERT(text);

    lvc.mask     = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
    lvc.pszText  = text;
    lvc.cx       = width;
    lvc.iSubItem = listview->num_columns;

    return (wtk_listview_column)(ListView_InsertColumn(listview->control.hWnd, listview->num_columns++, &lvc) + 1);
}

void WTK_API wtk_listview_remove_column( struct wtk_listview* listview, wtk_listview_column column )
{
    WTK_ASSERT(listview);
    WTK_ASSERT(column > 0);

    ListView_DeleteColumn(listview->control.hWnd, column - 1);
    --listview->num_columns;
}

wtk_listview_row WTK_API wtk_listview_insert_row( struct wtk_listview* listview )
{
    LVITEM lvi;

    WTK_ASSERT(listview);

    lvi.mask     = LVIF_STATE;
    lvi.iItem    = listview->num_rows++;
    lvi.iSubItem = 0;
    lvi.state    = 0;
    lvi.pszText  = NULL;

    return -ListView_InsertItem(listview->control.hWnd, &lvi) - 1;
}

void WTK_API wtk_listview_remove_row( struct wtk_listview* listview, wtk_listview_row row )
{
    WTK_ASSERT(listview);
    WTK_ASSERT(row < 0);

    ListView_DeleteItem(listview->control.hWnd, -(row + 1));
    --listview->num_rows;
}

static BOOL CALLBACK wtk_on_layout_change_proc( HWND hWnd, LPARAM lParam ) {
    SendMessage(hWnd, WTK_ON_LAYOUT_CHANGED, 0, 0);
    return TRUE;
}

static LRESULT CALLBACK wtk_listview_proc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
    struct wtk_control* control = (struct wtk_control*)GetPropA(hWnd, "_wtk_ctrl_ptr");
    struct wtk_listview* listview = (struct wtk_listview*)control;
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
            wtk_free(listview);
        } break;

        default: {
            return CallWindowProc((WNDPROC)GetPropA(hWnd, "_wtk_old_proc"), hWnd, uMsg, wParam, lParam);
        } break;
    }

    return 0;
}