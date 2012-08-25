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

#include <wtk/wtk_image_list.h>

#include "_wtk_windows.h"
#include "_wtk_image.h"

#include <wtk/wtk_mm.h>

#include <string.h>

struct wtk_image_list* WTK_API wtk_image_list_create( int width, int height, int num_imgs )
{
    HIMAGELIST hImageList;
    struct wtk_image_list* img_list;

    hImageList = ImageList_Create(width, height, ILC_COLOR32, num_imgs, num_imgs);
    if( !hImageList ) return NULL;

    img_list = (struct wtk_image_list*)wtk_alloc(sizeof(struct wtk_image_list));
    img_list->hImageList = hImageList;
    return img_list;
}

void WTK_API wtk_image_list_destroy( struct wtk_image_list* img_list )
{
    WTK_ASSERT(img_list);

    ImageList_Destroy(img_list->hImageList);
    wtk_free(img_list);
}

wtk_image_list_id WTK_API wtk_image_list_add_image( struct wtk_image_list* img_list, struct wtk_image* image )
{
    WTK_ASSERT(img_list);
    WTK_ASSERT(image);

    return (wtk_image_list_id)(ImageList_Add(img_list->hImageList, (HBITMAP)image->hImage, NULL) + 1);
}


wtk_image_list_id WTK_API wtk_image_list_add_icon( struct wtk_image_list* img_list, struct wtk_icon* icon )
{
    WTK_ASSERT(img_list);
    WTK_ASSERT(icon);

    return (wtk_image_list_id)(ImageList_AddIcon(img_list->hImageList, icon->hIcon) + 1);
}

void wtk_image_list_replace( struct wtk_image_list* img_list, wtk_image_list_id id, struct wtk_image* image )
{
    WTK_ASSERT(img_list);
    WTK_ASSERT(id > 0);
    WTK_ASSERT(image);

    ImageList_Replace(img_list->hImageList, id - 1, image->hImage, NULL);
}

void WTK_API wtk_image_list_remove( struct wtk_image_list* img_list, wtk_image_list_id id )
{
    WTK_ASSERT(img_list);
    WTK_ASSERT(id > 0);

    ImageList_Remove(img_list->hImageList, id - 1);
}