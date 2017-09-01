/*===-- wtk/frame.h -----------------------------------------*- mode: C -*-===*/
/*                                                                            */
/*                                     _   _                                  */
/*                               _ _ _| |_| |_                                */
/*                              | | | |  _| '_|                               */
/*                              |_____|_| |_,_|                               */
/*                                                                            */
/*       This file is distributed under the terms described in LICENSE.       */
/*                                                                            */
/*===----------------------------------------------------------------------===*/

#ifndef _WTK_FRAME_H_
#define _WTK_FRAME_H_

#include "wtk/foundation.h"

WTK_BEGIN_EXTERN_C

typedef struct wtk_frame {
  wtk_rectangle_t footprint;
} wtk_frame_t;

WTK_END_EXTERN_C

#endif /* _WTK_FRAME_H_ */
