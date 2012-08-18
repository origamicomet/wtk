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

#ifndef _WTK_CHECKBOX_H_
#define _WTK_CHECKBOX_H_

#include <wtk/wtk_control.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

struct wtk_checkbox;
typedef struct wtk_checkbox wtk_checkbox;

extern WTK_EXPORT struct wtk_checkbox* WTK_API wtk_checkbox_create( int x, int y, int width, int height, struct wtk_control* parent );

#define WTK_CHECKBOX_STATE( state ) WTK_CHECKBOX_STATE_##state
typedef enum {
    WTK_CHECKBOX_STATE_Checked       = 1,
    WTK_CHECKBOX_STATE_Indeterminate = 2,
    WTK_CHECKBOX_STATE_Unchecked     = 3,
} wtk_checkbox_state;

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // _WTK_CHECKBOX_H_