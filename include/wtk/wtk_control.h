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

#ifndef _WTK_CONTROL_H_
#define _WTK_CONTROL_H_

#include <wtk/wtk_config.h>
#include <wtk/wtk_compat.h>
#include <wtk/wtk_event.h>
#include <wtk/wtk_control_types.h>
#include <wtk/wtk_control_properties.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

struct wtk_control;
typedef struct wtk_control wtk_control;

extern WTK_EXPORT struct wtk_control* WTK_API wtk_control_create( int x, int y, unsigned int width, unsigned int height, struct wtk_control* parent );
extern WTK_EXPORT void WTK_API wtk_control_destroy( struct wtk_control* control );

extern WTK_EXPORT void* WTK_API wtk_control_get_user_ptr( struct wtk_control* control );
extern WTK_EXPORT void WTK_API wtk_control_set_user_ptr( struct wtk_control* control, void* user_ptr );

extern WTK_EXPORT void WTK_API wtk_control_get_position( struct wtk_control* control, int* x, int* y );
extern WTK_EXPORT void WTK_API wtk_control_set_position( struct wtk_control* control, int x, int y );

extern WTK_EXPORT void WTK_API wtk_control_get_size( struct wtk_control* control, unsigned int* width, unsigned int* height );
extern WTK_EXPORT void WTK_API wtk_control_set_size( struct wtk_control* control, unsigned int width, unsigned int height );

typedef void* wtk_property;

extern WTK_EXPORT void WTK_API wtk_control_get_property( struct wtk_control* control, wtk_control_property property, ... );
extern WTK_EXPORT void WTK_API wtk_control_set_property( struct wtk_control* control, wtk_control_property property, ... );

extern WTK_EXPORT void WTK_API wtk_control_set_callback( struct wtk_control* control, wtk_event event, wtk_event_callback callback );

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // _WTK_CONTROL_H_