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

#ifndef _WTK_CONTROL_PROPERTIES_H_
#define _WTK_CONTROL_PROPERTIES_H_

#define WTK_CONTROL_PROP( property ) WTK_CONTROL_PROP_##property
typedef enum {
    WTK_CONTROL_PROP_Invalid = 0,
    WTK_CONTROL_PROP_UserPtr,
    WTK_CONTROL_PROP_Position,
    WTK_CONTROL_PROP_Size,
    WTK_CONTROL_PROP_Font,
    WTK_CONTROL_PROP_Icon,
    WTK_CONTROL_PROP_Icons,
    WTK_CONTROL_PROP_Title,
    WTK_CONTROL_PROP_Text,
    WTK_CONTROL_PROP_TextAlign,
    WTK_CONTROL_PROP_Value,
    WTK_CONTROL_PROP_COUNT
} wtk_control_property;

#endif // _WTK_CONTROL_PROPERTIES_H_