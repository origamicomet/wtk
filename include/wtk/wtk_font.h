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

#ifndef _WTK_FONT_H_
#define _WTK_FONT_H_

#include <wtk/wtk_config.h>
#include <wtk/wtk_compat.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

struct wtk_font;
typedef struct wtk_font wtk_font;

typedef enum wtk_font_style {
    WTK_FONT_STYLE_DEFAULT   = 0,
    WTK_FONT_STYLE_BOLD      = (1 << 0),
    WTK_FONT_STYLE_UNDERLINE = (1 << 1),
    WTK_FONT_STYLE_ITALIC    = (1 << 2),
    WTK_FONT_STYLE_STRIKEOUT = (1 << 3)
} wtk_font_style;

extern WTK_EXPORT struct wtk_font* WTK_API wtk_font_create( const char* font_family, unsigned int font_size, unsigned int font_style );
extern WTK_EXPORT struct wtk_font* WTK_API wtk_font_default();
extern WTK_EXPORT void WTK_API wtk_font_destroy( struct wtk_font* font );

extern WTK_EXPORT void wtk_font_set_user_ptr( struct wtk_font* font, void* user_ptr );
extern WTK_EXPORT void* wtk_font_get_user_ptr( struct wtk_font* font );

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // _WTK_FONT_H_