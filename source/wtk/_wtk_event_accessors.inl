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

static void WTK_API wtk_event_on_create_setter( struct wtk_control* control, wtk_event_callback callback )
{
    control->on_create_callback = callback;
}

static void WTK_API wtk_event_on_destroy_setter( struct wtk_control* control, wtk_event_callback callback )
{
    control->on_destroy_callback = callback;
}

static void WTK_API wtk_event_on_close_setter( struct wtk_control* control, wtk_event_callback callback )
{
    WTK_ASSERT(control->type == WTK_CONTROL_TYPE(Window));
    ((struct wtk_window*)control)->on_close_callback = callback;
}