/*===-- wtk/app.h -------------------------------------------*- mode: C -*-===*/
/*                                                                            */
/*                                     _   _                                  */
/*                               _ _ _| |_| |_                                */
/*                              | | | |  _| '_|                               */
/*                              |_____|_| |_,_|                               */
/*                                                                            */
/*       This file is distributed under the terms described in LICENSE.       */
/*                                                                            */
/*===----------------------------------------------------------------------===*/

#ifndef _WTK_APP_H_
#define _WTK_APP_H_

#include "wtk/foundation.h"

WTK_BEGIN_EXTERN_C

extern WTK_PUBLIC
  void wtk_app_init(void);

extern WTK_PUBLIC
  void wtk_app_shutdown(void);

extern WTK_PUBLIC
  void wtk_app_pump(void);

WTK_END_EXTERN_C

#endif /* _WTK_APP_H_ */
