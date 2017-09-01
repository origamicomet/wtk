/*===-- wtk/handle.h ----------------------------------------*- mode: C -*-===*/
/*                                                                            */
/*                                     _   _                                  */
/*                               _ _ _| |_| |_                                */
/*                              | | | |  _| '_|                               */
/*                              |_____|_| |_,_|                               */
/*                                                                            */
/*       This file is distributed under the terms described in LICENSE.       */
/*                                                                            */
/*===----------------------------------------------------------------------===*/

#ifndef _WTK_HANDLE_H_
#define _WTK_HANDLE_H_

#include "wtk/foundation.h"

WTK_BEGIN_EXTERN_C

#if WTK_ARCHITECTURE == WTK_ARCHITECTURE_X86
  typedef wtk_uint32_t wtk_handle_t;

  #define WTK_INVALID_HANDLE ((wtk_handle_t)0)

  #define WTK_HANDLE_TYPE_MASK ((wtk_handle_t)0x0000000Ful)
  #define WTK_HANDLE_ID_MASK ((wtk_handle_t)0xFFFFFFF0ul)
#elif WTK_ARCHITECTURE == WTK_ARCHITECTURE_X86_64
  typedef wtk_uint64_t wtk_handle_t;

  #define WTK_INVALID_HANDLE ((wtk_handle_t)0)

  #define WTK_HANDLE_TYPE_MASK ((wtk_handle_t)0x000000000000000Full)
  #define WTK_HANDLE_ID_MASK ((wtk_handle_t)0xFFFFFFFFFFFFFFF0ull)
#endif

typedef enum wtk_handle_type {
  WTK_WINDOW_HANDLE = 1,
  WTK_FRAME_HANDLE  = 2
} wtk_handle_type_t;

WTK_END_EXTERN_C

#endif /* _WTK_HANDLE_H_ */
