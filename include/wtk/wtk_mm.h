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

#ifndef _WTK_MM_H_
#define _WTK_MM_H_

#include <wtk/wtk_config.h>
#include <wtk/wtk_compat.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct wtk_allocator {
    void* (WTK_API *alloc_callback)( size_t num_bytes );
    void* (WTK_API *realloc_callback)( void* ptr, size_t num_bytes );
    void (WTK_API *free_callback)( void* ptr );
} wtk_allocator;

extern WTK_EXPORT void WTK_API wtk_set_allocator( const struct wtk_allocator* allocator );
extern WTK_EXPORT const struct wtk_allocator* wtk_get_allocator();

extern WTK_EXPORT void* WTK_API wtk_alloc( size_t num_bytes );
extern WTK_EXPORT void* WTK_API wtk_realloc( void* ptr, size_t num_bytes );
extern WTK_EXPORT void WTK_API wtk_free( void* ptr );

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // _WTK_MM_H_