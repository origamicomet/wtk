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

#ifndef _WTK_EVENT_H_
#define _WTK_EVENT_H_

#include <wtk/wtk_config.h>
#include <wtk/wtk_compat.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

struct wtk_control;

#define WTK_EVENT( event ) WTK_EVENT_##event
typedef enum {
    WTK_EVENT_Invalid = 0,
    WTK_EVENT_OnCreate,
    WTK_EVENT_OnDestroy,
    WTK_EVENT_OnLayoutChanged,
    WTK_EVENT_OnClose,
    WTK_EVENT_OnPaint,
    WTK_EVENT_OnValueChanged,
    WTK_EVENT_OnSelectionChanged,
    WTK_EVENT_OnPressed,
    WTK_EVENT_OnReleased,
    WTK_EVENT_OnClicked,
    WTK_EVENT_OnMouseMoved,
    WTK_EVENT_OnMouseScrolled,
    WTK_EVENT_OnKeyPressed,
    WTK_EVENT_OnKeyReleased,
    WTK_EVENT_OnMinimized,
    WTK_EVENT_OnMaximized,
    WTK_EVENT_OnResized,
    WTK_EVENT_COUNT
} wtk_event;

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // _WTK_EVENT_H_