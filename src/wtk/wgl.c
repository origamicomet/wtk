/*===-- wtk/wgl.c -------------------------------------------*- mode: C -*-===*/
/*                                                                            */
/*                                     _   _                                  */
/*                               _ _ _| |_| |_                                */
/*                              | | | |  _| '_|                               */
/*                              |_____|_| |_,_|                               */
/*                                                                            */
/*       This file is distributed under the terms described in LICENSE.       */
/*                                                                            */
/*===----------------------------------------------------------------------===*/

#include "wtk/wgl.h"

#if WTK_PLATFORM == WTK_PLATFORM_WINDOWS

#include <windows.h>

WTK_BEGIN_EXTERN_C

/* HACK(mtwilliams): We pun undecorated names with the preprocessor because
 * Windows headers declare functions of the same name.
 */

static HMODULE gl;
static HMODULE gdi;

#define WGL_DRAW_TO_WINDOW_ARB                    0x2001
#define WGL_DRAW_TO_BITMAP_ARB                    0x2002

#define WGL_ACCELERATION_ARB                      0x2003
#define WGL_SUPPORT_OPENGL_ARB                    0x2010
#define WGL_SUPPORT_GDI_ARB                       0x200F

#define WGL_PIXEL_TYPE_ARB                        0x2013
#define WGL_TYPE_RGBA_ARB                         0x202B

#define WGL_COLOR_BITS_ARB                        0x2014
#define WGL_RED_BITS_ARB                          0x2015
#define WGL_GREEN_BITS_ARB                        0x2017
#define WGL_BLUE_BITS_ARB                         0x2019
#define WGL_ALPHA_BITS_ARB                        0x201B
#define WGL_DEPTH_BITS_ARB                        0x2022
#define WGL_STENCIL_BITS_ARB                      0x2023

#define WGL_FRAMEBUFFER_SRGB_CAPABLE_ARB          0x20A9

#define WGL_COLORSPACE_EXT                        0x309D
#define WGL_COLORSPACE_SRGB_EXT                   0x3089
#define WGL_COLORSPACE_LINEAR_EXT                 0x308A

#define WGL_SWAP_METHOD_ARB                       0x2007
#define WGL_DOUBLE_BUFFER_ARB                     0x2011

#define WGL_STEREO_ARB                            0x2012

#define WGL_SWAP_EXCHANGE_ARB                     0x2028
#define WGL_SWAP_COPY_ARB                         0x2029
#define WGL_SWAP_UNDEFINED_ARB                    0x202A

#define WGL_NO_ACCELERATION_ARB                   0x2025
#define WGL_GENERIC_ACCELERATION_ARB              0x2026
#define WGL_FULL_ACCELERATION_ARB                 0x2027

#define WGL_CONTEXT_MAJOR_VERSION_ARB             0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB             0x2092
#define WGL_CONTEXT_PROFILE_MASK_ARB              0x9126
#define WGL_CONTEXT_LAYER_PLANE_ARB               0x2093
#define WGL_CONTEXT_FLAGS_ARB                     0x2094
#define WGL_CONTEXT_RELEASE_BEHAVIOR_ARB          0x2097

#define WGL_CONTEXT_DEBUG_BIT_ARB                 0x0001
#define WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB    0x0002

#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB          0x00000001
#define WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB 0x00000002

#define WGL_CONTEXT_RELEASE_BEHAVIOR_NONE_ARB     0x0000
#define WGL_CONTEXT_RELEASE_BEHAVIOR_FLUSH_ARB    0x2098

typedef const char *(WINAPI *WGLGETEXTENSIONSSTRINGPROC)(HDC hdc);
typedef void *(WINAPI *WGLGETPROCADDRESSPROC)(const char *name);

#define wglGetExtensionsString __wtk_wglGetExtensionsString
#define wglGetProcAddress __wtk_wglGetProcAddress

static WGLGETEXTENSIONSSTRINGPROC __wtk_wglGetExtensionsString = NULL;
static WGLGETPROCADDRESSPROC __wtk_wglGetProcAddress = NULL;

typedef HGLRC (WINAPI *WGLCREATECONTEXTPROC)(HDC hdc);
typedef BOOL (WINAPI *WGLDELETECONTEXTPROC)(HGLRC hglrc);
typedef BOOL (WINAPI *WGLMAKECURRENTPROC)(HDC hdc, HGLRC hglrc);

#define wglCreateContext __wtk_wglCreateContext
#define wglDeleteContext __wtk_wglDeleteContext
#define wglMakeCurrent __wtk_wglMakeCurrent

static WGLCREATECONTEXTPROC __wtk_wglCreateContext = NULL;
static WGLDELETECONTEXTPROC __wtk_wglDeleteContext = NULL;
static WGLMAKECURRENTPROC __wtk_wglMakeCurrent = NULL;

typedef BOOL (WINAPI *WGLCHOOSEPIXELFORMATPROC)(HDC hdc, const UINT *piAttribIList, const FLOAT *pfAttribFList, UINT nMaxFormats, int *piFormats, UINT *nNumFormats);
typedef HGLRC (WINAPI *WGLCREATECONTEXTATTRIBSPROC)(HDC hDC, HGLRC hShareContext, const UINT *attribList);

#define wglChoosePixelFormat __wtk_wglChoosePixelFormat
#define wglCreateContextAttribs __wtk_wglCreateContextAttribs

static WGLCHOOSEPIXELFORMATPROC __wtk_wglChoosePixelFormat = NULL;
static WGLCREATECONTEXTATTRIBSPROC __wtk_wglCreateContextAttribs = NULL;

typedef BOOL (WINAPI *WGLSWAPINTERVALPROC)(int interval);
typedef BOOL (WINAPI *SWAPBUFFERSPROC)(HDC hdc);

#define wglSwapInterval __wtk_wglSwapInterval
#define SwapBuffers __wtk_SwapBuffers

static WGLSWAPINTERVALPROC __wtk_wglSwapInterval = NULL;
static SWAPBUFFERSPROC __wtk_SwapBuffers = NULL;

static const char *WGL_ACTUAL_CONTEXT_CLASS    = "27fd51f3-b7f6-4ccf-87b0-94458ea50410";
static const char *WGL_BOOTSTRAP_CONTEXT_CLASS = "a5b92a99-4f06-41c2-a0db-a46f908eaed1";

static void wtk_wgl_register_context_classes(void)
{
  /* We register two distinct window classes to aid differentiation of context
   * types. One is for our bootstrap context and the other for the contexts we
   * use.
   */

  WNDCLASSEXA actual_context_class;
  WNDCLASSEXA bootstrap_context_class;

  memset((void *)&actual_context_class, 0, sizeof(WNDCLASSEXA));
  memset((void *)&bootstrap_context_class, 0, sizeof(WNDCLASSEXA));

  actual_context_class.cbSize        = sizeof(WNDCLASSEXA);
  actual_context_class.style         = CS_VREDRAW | CS_HREDRAW | CS_OWNDC;
  actual_context_class.lpfnWndProc   = DefWindowProc;
  actual_context_class.hInstance     = GetModuleHandle(NULL);
  actual_context_class.hCursor       = LoadCursor(NULL, IDC_ARROW);
  actual_context_class.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
  actual_context_class.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);
  actual_context_class.lpszClassName = WGL_ACTUAL_CONTEXT_CLASS;

  static const BOOL registered_actual_context_class_succesfully =
    RegisterClassExA(&actual_context_class);

  wtk_assert_release(registered_actual_context_class_succesfully);

  bootstrap_context_class.cbSize        = sizeof(WNDCLASSEXA);
  bootstrap_context_class.style         = CS_VREDRAW | CS_HREDRAW | CS_OWNDC;
  bootstrap_context_class.lpfnWndProc   = DefWindowProc;
  bootstrap_context_class.hInstance     = GetModuleHandle(NULL);
  bootstrap_context_class.hCursor       = LoadCursor(NULL, IDC_ARROW);
  bootstrap_context_class.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
  bootstrap_context_class.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);
  bootstrap_context_class.lpszClassName = WGL_BOOTSTRAP_CONTEXT_CLASS;

  static const BOOL registered_boostrap_context_class_succesfully =
    RegisterClassExA(&bootstrap_context_class);

  wtk_assert_release(registered_boostrap_context_class_succesfully);
}

static void wtk_wgl_check_for_required_extensions(HWND hwnd, HDC hdc, HGLRC hglrc)
{
  (void)hwnd;
  (void)hglrc;

  const char *extensions = wglGetExtensionsString(hdc);
  wtk_assert_release(extensions != NULL);

  /* TODO(mtwilliams): Should we require WGL_ARB_context_flush_control? */
  static const char *required[] = {
    "WGL_ARB_pixel_format",
    "WGL_ARB_create_context",
    "WGL_ARB_create_context_profile",
    "WGL_EXT_swap_control"
  };

  static const unsigned count = sizeof(required) / sizeof(required[0]);

  for (unsigned i = 0; i < count; ++i) {
    /* TODO(mtwilliams): Replace `strstr` with a custom implementation to
     * remove dependence on standard library?
     */
    const unsigned advertised = (strstr(extensions, required[i]) != 0);

  #if 1
    wtk_assert_release(advertised);
  #else
    wtk_assertf_release(advertised, "Required extension `%s` is not available!", required[i]);
  #endif
  }
}

static void wtk_wgl_create_bootstrap_context_window(HWND *bootstrap_context_window)
{
  *bootstrap_context_window =
    CreateWindowA(WGL_BOOTSTRAP_CONTEXT_CLASS,
                  WGL_BOOTSTRAP_CONTEXT_CLASS,
                  WS_POPUP | WS_DISABLED,
                  0, 0, 1, 1,
                  NULL,
                  NULL,
                  GetModuleHandle(NULL),
                  NULL);

  wtk_assert_release(*bootstrap_context_window != NULL);
}

static void wtk_wgl_create_bootstrap_context(HWND bootstrap_context_window,
                                             HDC *bootstrap_context_hdc,
                                             HGLRC *bootstrap_context_hglrc)
{
  *bootstrap_context_hdc = GetDC(bootstrap_context_window);
  wtk_assert_release(*bootstrap_context_hdc != NULL);

  PIXELFORMATDESCRIPTOR pixel_format_desc;
  memset((void *)&pixel_format_desc, 0, sizeof(PIXELFORMATDESCRIPTOR));

  pixel_format_desc.nSize        = sizeof(PIXELFORMATDESCRIPTOR);
  pixel_format_desc.nVersion     = 1;
  pixel_format_desc.dwFlags      = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
  pixel_format_desc.iPixelType   = PFD_TYPE_RGBA;
  pixel_format_desc.cColorBits   = 24;
  pixel_format_desc.cAlphaBits   = 0;
  pixel_format_desc.cDepthBits   = 0;
  pixel_format_desc.cStencilBits = 0;
  pixel_format_desc.iLayerType   = PFD_MAIN_PLANE;

  const int pixel_format = ChoosePixelFormat(*bootstrap_context_hdc,
                                             &pixel_format_desc);
  wtk_assert_release(pixel_format != 0);

  const BOOL set_pixel_format_succesfully = !!SetPixelFormat(*bootstrap_context_hdc,
                                                             pixel_format,
                                                             &pixel_format_desc);
  wtk_assert_release(set_pixel_format_succesfully);

  *bootstrap_context_hglrc = wglCreateContext(*bootstrap_context_hdc);
  wtk_assert_release(*bootstrap_context_hglrc != NULL);
}

void wtk_wgl_init(void)
{
  gl = LoadLibraryA("opengl32.dll");
  wtk_assert_release(gl != NULL);

  wglGetProcAddress = (WGLGETPROCADDRESSPROC)GetProcAddress(gl, "wglGetProcAddress");
  wglCreateContext  = (WGLCREATECONTEXTPROC)GetProcAddress(gl, "wglCreateContext");
  wglDeleteContext  = (WGLDELETECONTEXTPROC)GetProcAddress(gl, "wglDeleteContext");
  wglMakeCurrent    = (WGLMAKECURRENTPROC)GetProcAddress(gl, "wglMakeCurrent");

  wtk_wgl_register_context_classes();

  HWND bootstrap_context_window;
  HDC bootstrap_context_hdc;
  HGLRC bootstrap_context_hglrc;

  wtk_wgl_create_bootstrap_context_window(&bootstrap_context_window);

  wtk_wgl_create_bootstrap_context(bootstrap_context_window,
                                   &bootstrap_context_hdc,
                                   &bootstrap_context_hglrc);

  wglMakeCurrent(bootstrap_context_hdc, bootstrap_context_hglrc);

  /* NOTE(mtwilliams): We assume that `WGL_ARB_extensions_string` is available. */
  wglGetExtensionsString = (WGLGETEXTENSIONSSTRINGPROC)wglGetProcAddress("wglGetExtensionsStringARB");

  wtk_wgl_check_for_required_extensions(bootstrap_context_window,
                                        bootstrap_context_hdc,
                                        bootstrap_context_hglrc);

  wglCreateContext        = (WGLCREATECONTEXTPROC)wtk_wgl_get_proc_address("wglCreateContext");
  wglDeleteContext        = (WGLDELETECONTEXTPROC)wtk_wgl_get_proc_address("wglDeleteContext");
  wglMakeCurrent          = (WGLMAKECURRENTPROC)wtk_wgl_get_proc_address("wglMakeCurrent");
  wglChoosePixelFormat    = (WGLCHOOSEPIXELFORMATPROC)wtk_wgl_get_proc_address("wglChoosePixelFormatARB");
  wglCreateContextAttribs = (WGLCREATECONTEXTATTRIBSPROC)wtk_wgl_get_proc_address("wglCreateContextAttribsARB");
  wglSwapInterval         = (WGLSWAPINTERVALPROC)wtk_wgl_get_proc_address("wglSwapIntervalEXT");

  wglMakeCurrent(NULL, NULL);

  /* TODO(mtwilliams): Determine if we should keep the bootstrap context around
   * until shutdown. Probably not.
   */
  wglDeleteContext(bootstrap_context_hglrc);
  ReleaseDC(bootstrap_context_window, bootstrap_context_hdc);
  DestroyWindow(bootstrap_context_window);

  gdi = LoadLibraryA("gdi32.dll");
  wtk_assert_release(gdi != NULL);

  SwapBuffers = (SWAPBUFFERSPROC)GetProcAddress(gdi, "SwapBuffers");
}

void wtk_wgl_shutdown(void)
{
  wglGetExtensionsString  = NULL;
  wglGetProcAddress       = NULL;
  wglCreateContext        = NULL;
  wglDeleteContext        = NULL;
  wglMakeCurrent          = NULL;
  wglChoosePixelFormat    = NULL;
  wglCreateContextAttribs = NULL;
  wglSwapInterval         = NULL;

  SwapBuffers             = NULL;

  FreeLibrary(gl);
  FreeLibrary(gdi);

  gl = NULL;
  gdi = NULL;
}

void *wtk_wgl_get_proc_address(const char *name)
{
  wtk_assert_debug(name != NULL);

  if (void *addr = wglGetProcAddress(name))
    return addr;

  return GetProcAddress(gl, name);
}

struct wtk_wgl_context {
  HWND window;

  /* Indicates if we own `window` and should destroy it. */
  unsigned owner_of_window;

  /* Drawing and resource contexts. */
  HDC hdc;
  HGLRC hglrc;

  /* Cached for surfaces. */
  int pixel_format;
  PIXELFORMATDESCRIPTOR pixel_format_desc;
};

static void wtk_wgl_create_context_window(HWND *actual_context_window)
{
  *actual_context_window =
    CreateWindowA(WGL_ACTUAL_CONTEXT_CLASS,
                  WGL_ACTUAL_CONTEXT_CLASS,
                  WS_POPUP | WS_DISABLED,
                  0, 0, 1, 1,
                  NULL,
                  NULL,
                  GetModuleHandle(NULL),
                  NULL);

  wtk_assert_release(*actual_context_window != NULL);
}

wtk_wgl_context_t *wtk_wgl_create_context(const wtk_wgl_context_creation_params_t *ccp)
{
  wtk_assert_debug(ccp != NULL);

  wtk_wgl_context_t *context =
    (wtk_wgl_context_t *)wtk_allocate_s(sizeof(wtk_wgl_context_t), 16);

  wtk_wgl_create_context_window(&context->window);

  context->hdc = GetDC(context->window);
  wtk_assert_release(context->hdc != NULL);

  context->owner_of_window = 1;

  const UINT pixel_format_attributes[] = {
    /* Goes without saying... */
    WGL_DRAW_TO_WINDOW_ARB, TRUE,
    WGL_SUPPORT_OPENGL_ARB, TRUE,
    WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,

    WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
    WGL_COLOR_BITS_ARB, 24,
    WGL_RED_BITS_ARB, 8,
    WGL_GREEN_BITS_ARB, 8,
    WGL_BLUE_BITS_ARB, 8,
    WGL_ALPHA_BITS_ARB, 0,

    /* PERF(mtwilliams): Determine if `WGL_SWAP_EXCHANGE_ARB` is fast path, as
     * some say it is. It should be as it's just exchanging pointers rather
     * than copying contents like `WGL_SWAP_COPY_ARB`. Except,
     * `WGL_SWAP_COPY_ARB` is analogous to `DXGI_SWAP_EFFECT_DISCARD` which is
     * the fast path for D3D11...
     */
    WGL_SWAP_METHOD_ARB, WGL_SWAP_EXCHANGE_ARB,
    WGL_DOUBLE_BUFFER_ARB, TRUE,

    0
  };

  /* TODO(mtwilliams): Determine if we can pass `NULL`. */
  UINT unused;

  const BOOL chose_pixel_format_succesfully =
    wglChoosePixelFormat(context->hdc,
                         &pixel_format_attributes[0], NULL, 1,
                         &context->pixel_format,
                         &unused);

  wtk_assert_release(chose_pixel_format_succesfully);

  /* As GDI expects the older style descriptor, we grab that. */
  DescribePixelFormat(context->hdc,
                      context->pixel_format,
                      sizeof(PIXELFORMATDESCRIPTOR),
                      &context->pixel_format_desc);

  /* Set traditionally. Windows will use the identifier to dig up the extended
   * attributes requested by `wglChoosePixelFormatARB`.
   */
  SetPixelFormat(context->hdc,
                 context->pixel_format,
                 &context->pixel_format_desc);

  UINT flags = 0x00000000;

  if (ccp->flags & WTK_WGL_CONTEXT_DEBUG)
    flags |= WGL_CONTEXT_DEBUG_BIT_ARB;

  UINT profile;

  if (ccp->version.major >= 3)
    profile = WGL_CONTEXT_CORE_PROFILE_BIT_ARB;
  else
    profile = WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB;

  const UINT context_attributes[] = {
    WGL_CONTEXT_MAJOR_VERSION_ARB, ccp->version.major,
    WGL_CONTEXT_MINOR_VERSION_ARB, ccp->version.minor,

    WGL_CONTEXT_PROFILE_MASK_ARB, profile,

    /* We don't seem to incur a context release and corresponding flush when
     * only rebinding `hdc` and not `hglrc`. Still, relying on the implicit
     * synchronization of `SwapBuffers` offers greater potential for
     * performance.
     */
    WGL_CONTEXT_RELEASE_BEHAVIOR_ARB, WGL_CONTEXT_RELEASE_BEHAVIOR_NONE_ARB,

    WGL_CONTEXT_FLAGS_ARB, flags,

    0
  };

  context->hglrc = wglCreateContextAttribs(context->hdc,
                                           ccp->share ?
                                             ccp->share->hglrc : NULL,
                                           &context_attributes[0]);

#if 1
  wtk_assert_release(context->hglrc != NULL);
#else
  wtk_assertf_release(context->hglrc, "Unable to create context!");
#endif

  return context;
}

void wtk_wgl_destroy_context(wtk_wgl_context_t *context)
{
  wtk_assert_debug(context != NULL);

  wglDeleteContext(context->hglrc);
  ReleaseDC(context->window, context->hdc);

  if (context->owner_of_window)
    DestroyWindow(context->window);

  wtk_free((void *)context);
}

struct wtk_wgl_surface {
  HWND window;
  HDC hdc;
};

wtk_wgl_surface_t *wtk_wgl_create_surface(wtk_wgl_context_t *context,
                                          HWND window)
{
  wtk_assert_debug(IsWindow(window));

  wtk_wgl_surface_t *surface =
    (wtk_wgl_surface_t *)wtk_allocate_s(sizeof(wtk_wgl_surface_t), 16);

  surface->window = (HWND)window;
  surface->hdc = GetDC(surface->window);

  SetPixelFormat(surface->hdc,
                 context->pixel_format,
                 &context->pixel_format_desc);

  return surface;
}

void wtk_wgl_destroy_surface(wtk_wgl_surface_t *surface)
{
  wtk_assert_debug(surface != NULL);

  /* TODO(mtwilliams): Make sure `surface->hdc` is not current. */
  ReleaseDC(surface->window, surface->hdc);

  wtk_free((void *)surface);
}

void wtk_wgl_dimensions_of_surface(wtk_wgl_surface_t *surface,
                                   wtk_uint32_t *width,
                                   wtk_uint32_t *height)
{
  wtk_assert_debug(surface != NULL);
  wtk_assert_debug(width != NULL);
  wtk_assert_debug(height != NULL);

  RECT area = { 0, };
  ::GetClientRect(surface->window, &area);

  *width = area.right - area.left;
  *height = area.bottom - area.top;
}

void wtk_wgl_bind(wtk_wgl_context_t *context,
                  wtk_wgl_surface_t *surface)
{
  if (context) {
    wglMakeCurrent(surface ? surface->hdc : context->hdc, context->hglrc);
  } else {
    wglMakeCurrent(NULL, NULL);
  }
}

void wtk_wgl_present(wtk_wgl_surface_t *surface,
                     wtk_uint32_t flags)
{
  wtk_assert_debug(surface != NULL);

  if (flags & WTK_WGL_PRESENT_SYNCHRONIZE)
    wglSwapInterval(1);
  else
    wglSwapInterval(0);

  SwapBuffers(surface->hdc);
}

WTK_END_EXTERN_C

#endif
