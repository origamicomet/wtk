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

static void WTK_API wtk_prop_title_getter( struct wtk_control* control, void* out )
{
    WTK_ASSERT(out);
    WTK_ASSERT(control->type == WTK_CONTROL_TYPE(Window));
    *((const char**)out) = ((struct wtk_window*)control)->title;
}

static void WTK_API wtk_prop_title_setter( struct wtk_control* control, void* value )
{
    WTK_ASSERT(control->type == WTK_CONTROL_TYPE(Window));
    SetWindowTextA(control->hWnd, (const char*)value);
    ((struct wtk_window*)control)->title = *((const char**)value);
}