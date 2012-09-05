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

#include <wtk/wtk_font.h>

#include "_wtk_windows.h"
#include "_wtk_font.h"

#include <wtk/wtk_mm.h>

#include <string.h>

struct wtk_font* WTK_API wtk_font_create( const char* font_family, unsigned int font_size, unsigned int font_style )
{
    LOGFONT lf;
    HFONT hFont;
    struct wtk_font* font;   

    GetObjectA(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
    hFont = CreateFontA(font_size,
                        0,
                        lf.lfEscapement,
                        lf.lfOrientation,
                        (font_style & WTK_FONT_STYLE_BOLD) ? FW_BOLD : FW_NORMAL,
                        (font_style & WTK_FONT_STYLE_ITALIC) == WTK_FONT_STYLE_ITALIC,
                        (font_style & WTK_FONT_STYLE_UNDERLINE) == WTK_FONT_STYLE_UNDERLINE,
                        (font_style & WTK_FONT_STYLE_STRIKEOUT) == WTK_FONT_STYLE_STRIKEOUT,
                        lf.lfCharSet,
                        lf.lfOutPrecision,
                        lf.lfClipPrecision,
                        CLEARTYPE_QUALITY /*lf.lfQuality*/,
                        lf.lfPitchAndFamily,
                        &font_family[0]);

    if( !hFont ) return NULL;

    font = wtk_alloc(sizeof(wtk_font));
    memset((void*)font, 0, sizeof(struct wtk_font));
    font->hFont = hFont;

    return font;
}

struct wtk_font* WTK_API wtk_font_default()
{
    static wtk_font def_font = { NULL };
    return &def_font;
}

void WTK_API wtk_font_destroy( struct wtk_font* font )
{
    WTK_ASSERT(font);
    DeleteObject(font->hFont);
    wtk_free(font);
}

void wtk_font_set_user_ptr( struct wtk_font* font, void* user_ptr )
{
    WTK_ASSERT(font);
    font->user_ptr = user_ptr;
}

void* wtk_font_get_user_ptr( struct wtk_font* font )
{
    WTK_ASSERT(font);
    return font->user_ptr;
}