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

#ifndef _WTK_CONTROL_TYPES_H_
#define _WTK_CONTROL_TYPES_H_

#define WTK_CONTROL_TYPE( type ) WTK_CONTROL_TYPE_##type

typedef enum {
    WTK_CONTROL_TYPE_Invalid = 0,
    WTK_CONTROL_TYPE_Base,
    WTK_CONTROL_TYPE_Window,
    WTK_CONTROL_TYPE_Menu,
    WTK_CONTROL_TYPE_MenuItem,
    WTK_CONTROL_TYPE_Label,
    WTK_CONTROL_TYPE_Frame,
    WTK_CONTROL_TYPE_Button,
    WTK_CONTROL_TYPE_CheckBox,
    WTK_CONTROL_TYPE_TextBox,
    WTK_CONTROL_TYPE_ListBox,
    WTK_CONTROL_TYPE_ListView,
	WTK_CONTROL_TYPE_ComboBox,
    WTK_CONTROL_TYPE_COUNT
} wtk_control_type;

#endif // _WTK_CONTROL_TYPES_H_