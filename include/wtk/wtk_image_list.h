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

#ifndef _WTK_IMAGE_LIST_H_
#define _WTK_IMAGE_LIST_H_

#include <wtk/wtk_config.h>
#include <wtk/wtk_compat.h>
#include <wtk/wtk_image.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

struct wtk_image_list;
typedef struct wtk_image_list wtk_image_list;

extern WTK_EXPORT struct wtk_image_list* WTK_API wtk_image_list_create( int width, int height, int num_imgs );
extern WTK_EXPORT void WTK_API wtk_image_list_destroy( struct wtk_image_list* img_list );

typedef unsigned int wtk_image_list_id;

extern WTK_EXPORT wtk_image_list_id WTK_API wtk_image_list_add_image( struct wtk_image_list* img_list, struct wtk_image* image );
extern WTK_EXPORT wtk_image_list_id WTK_API wtk_image_list_add_icon( struct wtk_image_list* img_list, struct wtk_icon* icon );
extern WTK_EXPORT void wtk_image_list_replace( struct wtk_image_list* img_list, wtk_image_list_id id, struct wtk_image* image );
extern WTK_EXPORT void WTK_API wtk_image_list_remove( struct wtk_image_list* img_list, wtk_image_list_id id );

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // _WTK_IMAGE_LIST_H_