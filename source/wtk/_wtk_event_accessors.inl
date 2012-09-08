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

// =============================================================================
// WTK_EVENT_OnCreate
// =============================================================================

static void WTK_API wtk_event_on_create_setter( struct wtk_control* control, wtk_event_callback callback )
{
    control->on_create_callback = callback;
}

// =============================================================================
// WTK_EVENT_OnDestroy
// =============================================================================

static void WTK_API wtk_event_on_destroy_setter( struct wtk_control* control, wtk_event_callback callback )
{
    control->on_destroy_callback = callback;
}

// =============================================================================
// WTK_EVENT_OnLayoutChanged
// =============================================================================

static void WTK_API wtk_event_on_layout_changed_setter( struct wtk_control* control, wtk_event_callback callback )
{
    control->on_layout_changed_callback = callback;
}

// =============================================================================
// WTK_EVENT_OnClose
// =============================================================================

static void WTK_API wtk_event_on_close_setter( struct wtk_control* control, wtk_event_callback callback )
{
    WTK_ASSERT(control->type == WTK_CONTROL_TYPE(Window));
    ((struct wtk_window*)control)->on_close_callback = callback;
}

// =============================================================================
// WTK_EVENT_OnPaint
// =============================================================================

static void WTK_API wtk_event_on_paint_setter( struct wtk_control* control, wtk_event_callback callback )
{
    control->on_paint_callback = callback;
}

// =============================================================================
// WTK_EVENT_OnValueChanged
// =============================================================================

static void WTK_API wtk_event_on_value_changed_setter( struct wtk_control* control, wtk_event_callback callback )
{
    WTK_ASSERT(
        ( control->type == WTK_CONTROL_TYPE(CheckBox) ||
          control->type == WTK_CONTROL_TYPE(TextBox) )
    );

    switch( control->type ) {
        case WTK_CONTROL_TYPE(CheckBox): {
            ((struct wtk_checkbox*)control)->on_value_changed_callback = callback;
        } break;

        case WTK_CONTROL_TYPE(TextBox): {
            ((struct wtk_textbox*)control)->on_value_changed_callback = callback;
        } break;
    }
}

// =============================================================================
// WTK_EVENT_OnSelectionChanged
// =============================================================================

static void WTK_API wtk_event_on_selection_changed_setter( struct wtk_control* control, wtk_event_callback callback )
{
    WTK_ASSERT((
        control->type == WTK_CONTROL_TYPE(ListBox) ||
		control->type == WTK_CONTROL_TYPE(ComboBox)
    ));

    switch( control->type ) {
        case WTK_CONTROL_TYPE(ListBox): {
            ((struct wtk_listbox*)control)->on_selection_changed_callback = callback;
        } break;

        case WTK_CONTROL_TYPE(ComboBox): {
            ((struct wtk_combobox*)control)->on_selection_changed_callback = callback;
        } break;
    }
}

// =============================================================================
// WTK_EVENT_OnPressed
// =============================================================================

static void WTK_API wtk_event_on_pressed_setter( struct wtk_control* control, wtk_event_callback callback )
{
    control->on_pressed_callback = callback;
}

// =============================================================================
// WTK_EVENT_OnReleased
// =============================================================================

static void WTK_API wtk_event_on_released_setter( struct wtk_control* control, wtk_event_callback callback )
{
    control->on_released_callback = callback;
}

// =============================================================================
// WTK_EVENT_OnClicked
// =============================================================================

static void WTK_API wtk_event_on_clicked_setter( struct wtk_control* control, wtk_event_callback callback )
{
    control->on_clicked_callback = callback;
}

// =============================================================================
// WTK_EVENT_OnMouseMoved
// =============================================================================

static void WTK_API wtk_event_on_mouse_moved_setter( struct wtk_control* control, wtk_event_callback callback )
{
    control->on_mouse_moved_callback = callback;
}

// =============================================================================
// WTK_EVENT_OnKeyPressed
// =============================================================================

static void WTK_API wtk_event_on_key_pressed_setter( struct wtk_control* control, wtk_event_callback callback )
{
    control->on_key_pressed_callback = callback;
}

// =============================================================================
// WTK_EVENT_OnKeyReleased
// =============================================================================

static void WTK_API wtk_event_on_key_released_setter( struct wtk_control* control, wtk_event_callback callback )
{
    control->on_key_released_callback = callback;
}

// =============================================================================
// WTK_EVENT_OnMouseScrolled
// =============================================================================

static void WTK_API wtk_event_on_mouse_scrolled_setter( struct wtk_control* control, wtk_event_callback callback )
{
    control->on_mouse_scrolled_callback = callback;
}

// =============================================================================
// WTK_EVENT_OnMinimized
// =============================================================================

static void WTK_API wtk_event_on_minimized_setter( struct wtk_control* control, wtk_event_callback callback )
{
    WTK_ASSERT(control->type == WTK_CONTROL_TYPE(Window));
    ((struct wtk_window*)control)->on_minimized_callback = callback;
}

// =============================================================================
// WTK_EVENT_OnMaximized
// =============================================================================

static void WTK_API wtk_event_on_maximized_setter( struct wtk_control* control, wtk_event_callback callback )
{
    WTK_ASSERT(control->type == WTK_CONTROL_TYPE(Window));
    ((struct wtk_window*)control)->on_maximized_callback = callback;
}

// =============================================================================
// WTK_EVENT_OnResized
// =============================================================================

static void WTK_API wtk_event_on_resized_setter( struct wtk_control* control, wtk_event_callback callback )
{
    WTK_ASSERT(control->type == WTK_CONTROL_TYPE(Window));
    ((struct wtk_window*)control)->on_resized_callback = callback;
}