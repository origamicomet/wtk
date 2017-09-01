/*===-- wtk/wgl.h -------------------------------------------*- mode: C -*-===*/
/*                                                                            */
/*                                     _   _                                  */
/*                               _ _ _| |_| |_                                */
/*                              | | | |  _| '_|                               */
/*                              |_____|_| |_,_|                               */
/*                                                                            */
/*       This file is distributed under the terms described in LICENSE.       */
/*                                                                            */
/*===----------------------------------------------------------------------===*/

#ifndef _WTK_WGL_H_
#define _WTK_WGL_H_

#include "wtk/foundation.h"

#if WTK_PLATFORM == WTK_PLATFORM_WINDOWS

#include <windows.h>

WTK_BEGIN_EXTERN_C

extern WTK_PRIVATE
  void wtk_wgl_init(void);

extern WTK_PRIVATE
  void wtk_wgl_shutdown(void);

extern WTK_PRIVATE
  void *wtk_wgl_get_proc_address(const char *name);

typedef struct wtk_wgl_context wtk_wgl_context_t;

typedef enum wtk_wgl_context_flags {
  /*! Request debug context and enable debugging functionality. */
  WTK_WGL_CONTEXT_DEBUG = (1 << 0)
} wtk_wgl_context_flags_t;

typedef struct wtk_wgl_context_creation_params {
  /*! Minimum required context version. */
  struct {
    wtk_uint32_t major;
    wtk_uint32_t minor;
  } version;

  /*! \copydoc wtk_wgl_context_flags_t */
  wtk_uint32_t flags;

  /*! Context to share resources with. */
  wtk_wgl_context_t *share;
} wtk_wgl_context_creation_params_t;

extern WTK_PRIVATE
  wtk_wgl_context_t *wtk_wgl_create_context(
    const wtk_wgl_context_creation_params_t *ccp);

extern WTK_PRIVATE
  void wtk_wgl_destroy_context(
    wtk_wgl_context_t *context);

typedef struct wtk_wgl_surface wtk_wgl_surface_t;

extern WTK_PRIVATE
  wtk_wgl_surface_t *wtk_wgl_create_surface(
    wtk_wgl_context_t *context,
    HWND window);

extern WTK_PRIVATE
  void wtk_wgl_destroy_surface(
    wtk_wgl_surface_t *surface);

extern WTK_PRIVATE
  void wtk_wgl_dimensions_of_surface(
    wtk_wgl_surface_t *surface,
    wtk_uint32_t *width,
    wtk_uint32_t *height);

extern WTK_PRIVATE
  void wtk_wgl_bind(
    wtk_wgl_context_t *context,
    wtk_wgl_surface_t *surface);

typedef enum wtk_wgl_present_flags {
  /*! Synchronize to vertical blanks. */
  WTK_WGL_PRESENT_SYNCHRONIZE = (1 << 0)
} wtk_wgl_present_flags_t;

extern WTK_PRIVATE
  void wtk_wgl_present(
    wtk_wgl_surface_t *surface,
    wtk_uint32_t flags);

WTK_END_EXTERN_C

#endif

#endif /* _WTK_WGL_H_ */
