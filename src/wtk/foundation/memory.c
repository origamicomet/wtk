/*===-- wtk/foundation/memory.c -----------------------------*- mode: C -*-===*/
/*                                                                            */
/*                                     _   _                                  */
/*                               _ _ _| |_| |_                                */
/*                              | | | |  _| '_|                               */
/*                              |_____|_| |_,_|                               */
/*                                                                            */
/*       This file is distributed under the terms described in LICENSE.       */
/*                                                                            */
/*===----------------------------------------------------------------------===*/

#include "wtk/foundation/memory.h"

#include "wtk/foundation/utilities.h"
#include "wtk/foundation/assert.h"

/* REFACTOR(mtwilliams): Wrap `memset` et al. */
#include <string.h>

#if WTK_COMPILER == WTK_COMPILER_MSVC
  #include <malloc.h>
#endif

WTK_BEGIN_EXTERN_C

void *wtk_allocate(wtk_size_t size,
                   wtk_size_t alignment)
{
  void *ptr;

#if WTK_COMPILER == WTK_COMPILER_MSVC
  ptr = _aligned_malloc(size, alignment);
#else
  #if WTK_PLATFORM == WTK_PLATFORM_MAC || \
      WTK_PLATFORM == WTK_PLATFORM_LINUX
  #endif
#endif

  if (ptr)
    /* We always zero memory, as it prevents an entire class of errors. */
    memset(ptr, 0, size);

  return ptr;
}

void *wtk_allocate_s(wtk_size_t size,
                     wtk_size_t alignment)
{
  void *ptr = wtk_allocate(size, alignment);

  /* Will return `NULL` if out of memory. */
  wtk_assert_release(ptr != NULL);

  return ptr;
}

void wtk_free(void *ptr)
{
  wtk_assert_paranoid(ptr != NULL);

#if WTK_COMPILER == WTK_COMPILER_MSVC
  _aligned_free(ptr);
#else
  #if WTK_PLATFORM == WTK_PLATFORM_MAC || \
      WTK_PLATFORM == WTK_PLATFORM_LINUX
  #endif
#endif
}

void *wtk_block_allocate(wtk_block_t *block,
                         wtk_size_t size)
{
  void *ptr;

  wtk_assert_paranoid(block != NULL);

  /* Allocations are rounded up to the closest multiple of 16, thereby
     ensuring 16-byte alignment. */
  size = WTK_ALIGN_TO_BOUNDARY(size, 16);

  /* May have been given poorly aligned memory... */
  wtk_assert_paranoid(((block->base + block->offset) % 16) == 0);

  if ((block->offset + size) > block->size)
    /* Not enough space. */
    return NULL;

  ptr = (void *)(block->base + block->offset);
  block->offset += size;
  return ptr;
}

void *wtk_block_allocate_s(wtk_block_t *block,
                           wtk_size_t size)
{
  void *ptr;

  wtk_assert_paranoid(block != NULL);

  ptr = wtk_block_allocate(block, size);

  /* Will return `NULL` if out of space. */
  wtk_assert_release(ptr != NULL);

  return ptr;
}

void wtk_block_deallocate(wtk_block_t *block,
                          void *ptr)
{
  wtk_assert_paranoid(block != NULL);
  wtk_assert_paranoid(ptr != NULL);

  wtk_assert_debug((wtk_uintptr_t)ptr >= (block->base));
  wtk_assert_debug((wtk_uintptr_t)ptr <= (block->base + block->offset));

  /* We can't actually free memory. */
}

void wtk_block_reset(wtk_block_t *block)
{
  wtk_assert_paranoid(block != NULL);

  block->offset = 0;

  /* Rezero. Again, to prevent an entire class of errors. */
  memset((void *)block->base, 0, block->size);
}

WTK_END_EXTERN_C
