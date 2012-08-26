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

#ifndef _WTK_IMAGE_H_
#define _WTK_IMAGE_H_

#include <wtk/wtk_config.h>
#include <wtk/wtk_compat.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

struct wtk_image;
typedef struct wtk_image wtk_image;

struct wtk_icon;
typedef struct wtk_icon wtk_icon;

#define WTK_IMAGE_SIZE_DEFAULT -1
#define WTK_ICON_SIZE_DEFAULT -1

extern WTK_EXPORT struct wtk_image* WTK_API wtk_image_create_from_file( const char* file_path, int width, int height );
extern WTK_EXPORT void WTK_API wtk_image_destroy( struct wtk_image* image );

extern WTK_EXPORT void WTK_API wtk_image_set_user_ptr( struct wtk_image* image, void* user_ptr );
extern WTK_EXPORT void* WTK_API wtk_image_get_user_ptr( struct wtk_image* image );

extern WTK_EXPORT struct wtk_icon* WTK_API wtk_icon_create_from_file( const char* file_path, int width, int height );
extern WTK_EXPORT void WTK_API wtk_icon_destroy( struct wtk_icon* icon );

extern WTK_EXPORT void WTK_API wtk_icon_set_user_ptr( struct wtk_icon* icon, void* user_ptr );
extern WTK_EXPORT void* WTK_API wtk_icon_get_user_ptr( struct wtk_icon* icon );

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // _WTK_IMAGE_H_