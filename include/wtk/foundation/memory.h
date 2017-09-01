/*===-- wtk/foundation/memory.h -----------------------------*- mode: C -*-===*/
/*                                                                            */
/*                                     _   _                                  */
/*                               _ _ _| |_| |_                                */
/*                              | | | |  _| '_|                               */
/*                              |_____|_| |_,_|                               */
/*                                                                            */
/*       This file is distributed under the terms described in LICENSE.       */
/*                                                                            */
/*===----------------------------------------------------------------------===*/

#ifndef _WTK_FOUNDATION_MEMORY_H_
#define _WTK_FOUNDATION_MEMORY_H_

#include "wtk/config.h"
#include "wtk/linkage.h"

#include "wtk/foundation/types.h"

WTK_BEGIN_EXTERN_C

/*! Tries to allocate @size bytes aligned to @alignment boundary. */
extern WTK_PRIVATE
  void *wtk_allocate(
    wtk_size_t size,
    wtk_size_t alignment);

/*! Allocates @size bytes aligned to @alignment boundary. */
extern WTK_PRIVATE
 void *wtk_allocate_s(
  wtk_size_t size,
  wtk_size_t alignment);

/*! Frees memory allocated through `wtk_allocate` or `wtk_allocate_s`. */
extern WTK_PRIVATE
  void wtk_free(
    void *ptr);

/* TODO(mtwilliams): Bookmarking. Maintain a linked list of positions that can
 * be rewound to. If rewinding to bookmark prior to the last bookmark, remove
 * it from the list to let rewinds cascade. */

/* A simple bump allocator. */
typedef struct wtk_block {
  wtk_uintptr_t base;
  wtk_size_t    offset;
  wtk_size_t    size;
} wtk_block_t;

extern WTK_PRIVATE
  void *wtk_block_allocate(
    wtk_block_t *block,
    wtk_size_t size);

extern WTK_PRIVATE
  void *wtk_block_allocate_s(
    wtk_block_t *block,
    wtk_size_t size);

extern WTK_PRIVATE
  void wtk_block_deallocate(
    wtk_block_t *block,
    void *ptr);

extern WTK_PRIVATE
  void wtk_block_reset(
    wtk_block_t *block);

WTK_END_EXTERN_C

#endif /* _WTK_FOUNDATION_MEMORY_H_ */
