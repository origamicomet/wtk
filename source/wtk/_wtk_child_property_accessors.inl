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

#include "_wtk_windows.h"
#include "_wtk_controls.h"
#include "_wtk_font.h"
#include "_wtk_image.h"

#include <wtk/wtk_align.h>
#include <wtk/wtk_listview.h>
#include <wtk/wtk_image_list.h>

#include <stdarg.h>

// =============================================================================
// Default
// =============================================================================

static void WTK_API wtk_child_prop_default( struct wtk_control* control, wtk_child child, va_list args )
{
    WTK_ASSERT(!"wtk_child_prop_default");
}

// =============================================================================
// WTK_CONTROL_PROP_UserPtr
// =============================================================================

static void WTK_API wtk_child_prop_user_ptr_getter( struct wtk_control* control, wtk_child child, va_list args )
{
}

static void WTK_API wtk_child_prop_user_ptr_setter( struct wtk_control* control, wtk_child child, va_list args )
{
}

// =============================================================================
// WTK_CONTROL_PROP_Icon
// =============================================================================

static void WTK_API wtk_child_prop_icon_getter( struct wtk_control* control, wtk_child child, va_list args )
{
    WTK_ASSERT(!"wtk_child_prop_icon_getter");
}

static void WTK_API wtk_child_prop_icon_setter( struct wtk_control* control, wtk_child child, va_list args )
{
    WTK_ASSERT((
        control->type == WTK_CONTROL_TYPE(ListView)
    ));

    switch( control->type ) {
        case WTK_CONTROL_TYPE(ListView): {
            struct wtk_listview* listview = ((struct wtk_listview*)control);

            WTK_ASSERT(child != 0);

            if( child > 0 ) {
                LVCOLUMN lvc;
                lvc.mask = LVCF_IMAGE;
                lvc.iImage = va_arg(args, wtk_image_list_id) - 1;
                ListView_SetColumn(control->hWnd, (int)(child - 1), &lvc);
            } else {
                LVITEM lvi;
                lvi.mask = LVIF_IMAGE;
                lvi.iItem = -((int)child) - 1;
                lvi.iSubItem = va_arg(args, wtk_listview_column) - 1;
                lvi.iImage = va_arg(args, wtk_image_list_id) - 1;
                ListView_SetItem(control->hWnd, &lvi);
            }
        } break;
    }
}

// =============================================================================
// WTK_CONTROL_PROP_Text
// =============================================================================

static void WTK_API wtk_child_prop_text_getter( struct wtk_control* control, wtk_child child, va_list args )
{
    WTK_ASSERT((
        control->type == WTK_CONTROL_TYPE(ListBox) ||
        control->type == WTK_CONTROL_TYPE(ListView) ||
        control->type == WTK_CONTROL_TYPE(ComboBox)
    ));

    switch( control->type ) {
        case WTK_CONTROL_TYPE(ListBox): {
            struct wtk_listbox* listbox = ((struct wtk_listbox*)control);
            int text_len = GetWindowTextLength(control->hWnd);

            WTK_ASSERT(child > 0);

            listbox->text_buffer = wtk_realloc(listbox->text_buffer, text_len + 1);
            memset(listbox->text_buffer, 0, text_len + 1);
            GetWindowTextA(control->hWnd, listbox->text_buffer, text_len + 1);
            *va_arg(args, const char**) = listbox->text_buffer;
        } break;

        case WTK_CONTROL_TYPE(ListView): {
            WTK_ASSERT(!"wtk_child_prop_text_getter::ListView");
        } break;

        case WTK_CONTROL_TYPE(ComboBox): {
            struct wtk_combobox* combobox = ((struct wtk_combobox*)control);
            int text_len = GetWindowTextLength(control->hWnd);

            WTK_ASSERT(child > 0);

            combobox->text_buffer = wtk_realloc(combobox->text_buffer, text_len + 1);
            memset(combobox->text_buffer, 0, text_len + 1);
            GetWindowTextA(control->hWnd, combobox->text_buffer, text_len + 1);
            *va_arg(args, const char**) = combobox->text_buffer;
        } break;
    }
}

static void WTK_API wtk_child_prop_text_setter( struct wtk_control* control, wtk_child child, va_list args )
{
    WTK_ASSERT((
        control->type == WTK_CONTROL_TYPE(ListBox) ||
        control->type == WTK_CONTROL_TYPE(ListView) ||
        control->type == WTK_CONTROL_TYPE(ComboBox)
    ));

    switch( control->type ) {
        case WTK_CONTROL_TYPE(ListBox): {
            struct wtk_listbox* listbox = ((struct wtk_listbox*)control);
            WTK_ASSERT(child > 0);

            // HACK: Have to LB_DELETESTRING then LB_INSERTSTRING to update an item's text.
            SendMessage(control->hWnd, LB_DELETESTRING, (WPARAM)(child - 1), 0);
            SendMessage(control->hWnd, LB_INSERTSTRING, (WPARAM)(child - 1), (LPARAM)va_arg(args, const char*));
        } break;

        case WTK_CONTROL_TYPE(ListView): {
            struct wtk_listview* listview = ((struct wtk_listview*)control);
            WTK_ASSERT(child != 0);

            if( child > 0 ) {
                LVCOLUMN lvc;
                lvc.mask = LVCF_TEXT;
                lvc.pszText = va_arg(args, const char*);
                ListView_SetColumn(control->hWnd, (int)(child - 1), &lvc);
            } else {
                LVITEM lvi;
                lvi.mask = LVIF_TEXT;
                lvi.iItem = -((int)child) - 1;
                lvi.iSubItem = va_arg(args, wtk_listview_column) - 1;
                lvi.pszText = va_arg(args, const char*);
                ListView_SetItem(control->hWnd, &lvi);
            }
        } break;

        case WTK_CONTROL_TYPE(ComboBox): {
            struct wtk_combobox* combobox = ((struct wtk_combobox*)control);
            WTK_ASSERT(child > 0);

            // HACK: Have to LB_DELETESTRING then LB_INSERTSTRING to update an item's text.
            SendMessage(control->hWnd, CB_DELETESTRING, (WPARAM)(child - 1), 0);
            SendMessage(control->hWnd, CB_INSERTSTRING, (WPARAM)(child - 1), (LPARAM)va_arg(args, const char*));
        } break;
    }
}

// =============================================================================
// WTK_CONTROL_PROP_TextAlignment
// =============================================================================

static void WTK_API wtk_child_prop_text_align_getter( struct wtk_control* control, wtk_child child, va_list args )
{
    WTK_ASSERT(!"wtk_child_prop_text_align_getter");
}

static void WTK_API wtk_child_prop_text_align_setter( struct wtk_control* control, wtk_child child, va_list args )
{
    WTK_ASSERT(!"wtk_child_prop_text_align_setter");
}

// =============================================================================
// WTK_CONTROL_PROP_Value
// =============================================================================

static void WTK_API wtk_child_prop_value_getter( struct wtk_control* control, wtk_child child, va_list args )
{
    WTK_ASSERT(!"wtk_child_prop_value_getter");
}

static void WTK_API wtk_child_prop_value_setter( struct wtk_control* control, wtk_child child, va_list args )
{
    WTK_ASSERT(!"wtk_child_prop_value_setter");
}

// =============================================================================
// WTK_CONTROL_PROP_Column
// =============================================================================

static void WTK_API wtk_child_prop_column_getter( struct wtk_control* control, wtk_child child, va_list args )
{
    WTK_ASSERT(!"wtk_child_prop_column_getter");
}

static void WTK_API wtk_child_prop_column_setter( struct wtk_control* control, wtk_child child, va_list args )
{
    WTK_ASSERT(!"wtk_child_prop_column_setter");
}

// =============================================================================
// WTK_CONTROL_PROP_ImageList
// =============================================================================

static void WTK_API wtk_child_prop_image_list_getter( struct wtk_control* control, wtk_child child, va_list args )
{
    WTK_ASSERT(!"wtk_child_prop_image_list_getter");
}

static void WTK_API wtk_child_prop_image_list_setter( struct wtk_control* control, wtk_child child, va_list args )
{
    WTK_ASSERT(!"wtk_child_prop_image_list_setter");
}
