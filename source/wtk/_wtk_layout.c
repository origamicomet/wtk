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
#include "_wtk_layout.h"

void WTK_API wtk_on_layout_changed( struct wtk_control* control )
{
    WTK_ASSERT(control);

    if( control->auto_fill && control->type != WTK_CONTROL_TYPE(Window) ) {
        struct wtk_control* parent_control;
        int parent_width, parent_height;

        wtk_control_get_property(control, WTK_CONTROL_PROP(Parent), &parent_control);
        if( !parent_control ) return;

        // TODO: Take into account menu on windows?

        wtk_control_get_property(parent_control, WTK_CONTROL_PROP(Size), &parent_width, &parent_height);
        wtk_control_set_property(control, WTK_CONTROL_PROP(Position), control->margin_left, control->margin_top);
        wtk_control_set_property(control, WTK_CONTROL_PROP(Size), parent_width - control->margin_right - control->margin_left, parent_height - control->margin_bottom - control->margin_top);
    }
}