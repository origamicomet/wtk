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

#ifndef _WTK_COMBOBOX_H_
#define _WTK_COMBOBOX_H_

#include <wtk/wtk_control.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

struct wtk_combobox;
typedef struct wtk_combobox wtk_combobox;

extern WTK_EXPORT struct wtk_combobox* WTK_API wtk_combobox_create( int x, int y, int width, int height, struct wtk_control* parent );

typedef int wtk_combobox_item;

extern WTK_EXPORT wtk_combobox_item WTK_API wtk_combobox_insert( struct wtk_combobox* combobox, const char* text, void* user_ptr );
extern WTK_EXPORT void WTK_API wtk_combobox_remove( struct wtk_combobox* combobox, wtk_combobox_item id );

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // _WTK_COMBOBOX_H_
