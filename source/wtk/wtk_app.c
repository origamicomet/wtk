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

#include <wtk/wtk_app.h>

#include "_wtk_windows.h"

#include <wtk/wtk_control_types.h>
#include <wtk/wtk_mm.h>

#pragma comment(linker, "\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

typedef int (WTK_API *wtk_control_init_func)();

extern int WTK_API wtk_control_init();
extern int WTK_API wtk_window_init();
extern int WTK_API wtk_button_init();

static const wtk_control_init_func _control_init_funcs[WTK_CONTROL_TYPE_COUNT - 1] = {
    &wtk_control_init,
    &wtk_window_init,
    &wtk_button_init
};

static void WTK_API wtk_enable_visual_styles()
{
    DWORD dwVersion;
    DWORD dwMinorVersion;
    DWORD dwMajorVersion;

    dwVersion      = GetVersion();
    dwMinorVersion = (DWORD)(HIBYTE(LOWORD(dwVersion)));
    dwMajorVersion = (DWORD)(LOBYTE(LOWORD(dwVersion)));

    if( dwMajorVersion > 5 || (dwMajorVersion == 5 && dwMinorVersion >= 1) ) {
        const INITCOMMONCONTROLSEX iccx = { sizeof(INITCOMMONCONTROLSEX), ICC_STANDARD_CLASSES };
        InitCommonControlsEx(&iccx);
    }
}

int WTK_API wtk_init( const wtk_allocator* allocator )
{
    uint32_t i;

    WTK_ASSERT(allocator);

    wtk_set_allocator(allocator);
    wtk_enable_visual_styles();

    for( i = 0; i < WTK_CONTROL_TYPE_COUNT - 1; ++i ) {
        if( !_control_init_funcs[i]() ) return FALSE;
    }

    return TRUE;
}

int WTK_API wtk_run_app()
{
    MSG msg;

    while( TRUE ) {
        while( PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) ) {
            if( msg.message == WM_QUIT ) return EXIT_SUCCESS;

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return EXIT_FAILURE;
}

void WTK_API wtk_quit()
{
    PostQuitMessage(0);
}