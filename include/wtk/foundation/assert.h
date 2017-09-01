/*===-- wtk/foundation/assert.h -----------------------------*- mode: C -*-===*/
/*                                                                            */
/*                                     _   _                                  */
/*                               _ _ _| |_| |_                                */
/*                              | | | |  _| '_|                               */
/*                              |_____|_| |_,_|                               */
/*                                                                            */
/*       This file is distributed under the terms described in LICENSE.       */
/*                                                                            */
/*===----------------------------------------------------------------------===*/

#ifndef _WTK_ASSERT_H_
#define _WTK_ASSERT_H_

#include "wtk/config.h"
#include "wtk/linkage.h"

/* TODO(mtwilliams): Custom assertions. */
#include <assert.h>

WTK_BEGIN_EXTERN_C

#if WTK_CONFIGURATION <= WTK_CONFIGURATION_RELEASE
  #define wtk_assert_release(_Predicate) \
    assert(_Predicate)
#else
  #define wtk_assert_release(...)
#endif

#if WTK_CONFIGURATION <= WTK_CONFIGURATION_DEBUG
  #define wtk_assert_debug(_Predicate) \
    assert(_Predicate)
#else
  #define wtk_assert_debug(...)
#endif

#if WTK_PARANOID
  #define wtk_assert_paranoid(_Predicate) \
    assert(_Predicate)
#else
  #define wtk_assert_paranoid(...)
#endif

WTK_END_EXTERN_C

#endif /* _WTK_ASSERT_H_ */
