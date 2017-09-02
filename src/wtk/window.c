/*===-- wtk/window.c ----------------------------------------*- mode: C -*-===*/
/*                                                                            */
/*                                     _   _                                  */
/*                               _ _ _| |_| |_                                */
/*                              | | | |  _| '_|                               */
/*                              |_____|_| |_,_|                               */
/*                                                                            */
/*       This file is distributed under the terms described in LICENSE.       */
/*                                                                            */
/*===----------------------------------------------------------------------===*/

#include "wtk/window.h"

#if WTK_PLATFORM == WTK_PLATFORM_WINDOWS
  #include <windows.h>
#elif WTK_PLATFORM == WTK_PLATFORM_MAC
#elif WTK_PLATFORM == WTK_PLATFORM_LINUX
#endif

/* For creating an associated renderable surface. */
#include "wtk/gl.h"

/* For drawing. */
#include "wtk/canvas.h"

/* To mark dirty areas. */
#include "wtk/render.h"

WTK_BEGIN_EXTERN_C

#if WTK_PLATFORM == WTK_PLATFORM_WINDOWS
  static void wtk_register_window_class();
#endif

typedef struct wtk_window {
#if WTK_PLATFORM == WTK_PLATFORM_WINDOWS
  HWND handle;
#elif WTK_PLATFORM == WTK_PLATFORM_MAC
#elif WTK_PLATFORM == WTK_PLATFORM_LINUX
#endif

  wtk_uint32_t x;
  wtk_uint32_t y;
  wtk_uint32_t width;
  wtk_uint32_t height;

  unsigned minimized;
  unsigned maximized;

  unsigned resizeable;
  unsigned closable;

  /* Destroy window when closed. */
  unsigned destroy_on_close;

  /* User-specified handler for various events. */
  wtk_window_event_handler_t event_handler;
  void *event_handler_context;

  wtk_ogl_surface_t *surface;
  wtk_canvas_t *canvas;
} wtk_window_t;

wtk_window_t *handle_to_window(const wtk_handle_t handle)
{
  wtk_assert_paranoid(handle != WTK_INVALID_HANDLE);
  wtk_assert_debug((handle & WTK_HANDLE_TYPE_MASK) == WTK_WINDOW_HANDLE);
  return (wtk_window_t *)(handle & WTK_HANDLE_ID_MASK);
}

wtk_handle_t window_to_handle(wtk_window_t *window)
{
  if (window)
    return (wtk_handle_t)((wtk_handle_t)window | WTK_WINDOW_HANDLE);
  return WTK_INVALID_HANDLE;
}

wtk_ogl_surface_t *window_to_surface(wtk_handle_t window)
{
  return handle_to_window(window)->surface;
}

static wtk_uint32_t default_window_event_handler(wtk_handle_t handle,
                                                 const wtk_window_event_t *event,
                                                 void *context)
{
  (void)handle;
  (void)event;
  (void)context;

  return 0;
}

#if WTK_PLATFORM == WTK_PLATFORM_WINDOWS
  static void compensate_for_chrome(const DWORD styles,
                                    const DWORD ex_styles,
                                    wtk_uint32_t *width,
                                    wtk_uint32_t *height)
  {
    RECT area = { 0, 0, *width, *height };

    AdjustWindowRectEx(&area, styles, FALSE, ex_styles);

    *width  = area.right - area.left;
    *height = area.bottom - area.top;
  }
#endif

wtk_handle_t wtk_window_open(const wtk_window_desc_t *desc)
{
  wtk_window_t *window;

  wtk_assert_paranoid(desc != NULL);
  wtk_assert_paranoid(desc->title != NULL);
  wtk_assert_paranoid(desc->width > 0);
  wtk_assert_paranoid(desc->height > 0);

  window =
    (wtk_window_t *)wtk_allocate_s(sizeof(wtk_window_t), 16);

  window->x = desc->x;
  window->y = desc->y;
  window->width = desc->width;
  window->height = desc->height;

  window->resizeable = desc->resizeable;

  window->closable = desc->closable;

  /* Only destroy when explicitly closed. */
  window->destroy_on_close = 0;

  window->minimized = 0;
  window->maximized = 0;

  if (desc->event_handler) {
    window->event_handler = desc->event_handler;
    window->event_handler_context = desc->event_handler_context;
  } else {
    /* We specify a default handler rather than checking if one was specified
     * each invocation.
     */
    window->event_handler = &default_window_event_handler;
    window->event_handler_context = NULL;
  }

  /* Created asynchronously. */
  window->surface = NULL;
  window->canvas = NULL;

#if WTK_PLATFORM == WTK_PLATFORM_WINDOWS
  wtk_register_window_class();

  DWORD styles = WS_CAPTION
               | WS_BORDER
               | WS_CLIPCHILDREN
               | WS_CLIPSIBLINGS
               | WS_VISIBLE;

  if (window->resizeable)
    styles |= (WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SIZEBOX);
  else
    styles |= (WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX);

  /* TODO(mtwilliams): Drag 'n' drop. */
  const DWORD ex_styles = WS_EX_APPWINDOW;

  WCHAR title[256];
  MultiByteToWideChar(CP_UTF8, 0, desc->title, -1, &title[0], 256);

  wtk_uint32_t width = desc->width;
  wtk_uint32_t height = desc->height;

  compensate_for_chrome(styles, ex_styles, &width, &height);

  const HWND handle =
    CreateWindowExW(ex_styles,
                    L"6bdf53a8-2d8f-4372-894e-08e28a8f0ad7",
                    &title[0],
                    styles,
                    window->x, window->y, width, height,
                    NULL,
                    NULL,
                    GetModuleHandle(NULL),
                    (LPVOID)window);

  wtk_assert_release(handle != NULL);

  window->handle = handle;
#elif WTK_PLATFORM == WTK_PLATFORM_MAC
#elif WTK_PLATFORM == WTK_PLATFORM_LINUX
#endif

  return window_to_handle(window);
}

void wtk_window_close(wtk_handle_t handle)
{
  wtk_window_t *window = handle_to_window(handle);

  /* Implied. */
  window->closable = 1;
  window->destroy_on_close = 1;

#if WTK_PLATFORM == WTK_PLATFORM_WINDOWS
  /* We destroy the window in WM_CLOSE (and always free resources associated
   * with a window in WM_NCDESTROY) so that we don't have to handle
   * programmatic window closes differently from user requests. This trades
   * some complexity on our end to make library users' lives easier.
   */
  CloseWindow(window->handle);
#elif WTK_PLATFORM == WTK_PLATFORM_MAC
#elif WTK_PLATFORM == WTK_PLATFORM_LINUX
#endif
}

unsigned wtk_window_is_resizeable(wtk_handle_t handle)
{
  const wtk_window_t *window = handle_to_window(handle);
  return window->resizeable;
}

unsigned wtk_window_is_closable(wtk_handle_t handle)
{
  const wtk_window_t *window = handle_to_window(handle);
  return window->closable;
}

wtk_uintptr_t wtk_window_to_native(wtk_handle_t handle)
{
  const wtk_window_t *window = handle_to_window(handle);
#if WTK_PLATFORM == WTK_PLATFORM_WINDOWS
  return (wtk_uintptr_t)window->handle;
#elif WTK_PLATFORM == WTK_PLATFORM_MAC
#elif WTK_PLATFORM == WTK_PLATFORM_LINUX
#endif
}

wtk_canvas_t *wtk_window_to_canvas(wtk_handle_t handle)
{
  wtk_window_t *window = handle_to_window(handle);
  return window->canvas;
}

#if WTK_PLATFORM == WTK_PLATFORM_WINDOWS
  /* See `WM_CREATE` handler for reasoning. */
  #define WM_CREATED (WM_USER + 0x0001)

  static LRESULT WINAPI wtk_window_callback(HWND hWnd,
                                            UINT uMsg,
                                            WPARAM wParam,
                                            LPARAM lParam)
  {
    wtk_window_t *window = (wtk_window_t *)GetPropA(hWnd, "wtk");
    wtk_handle_t handle = window_to_handle(window);

    switch (uMsg) {
      case WM_CREATE: {
        const CREATESTRUCT *cs = (CREATESTRUCT *)lParam;

        window = (wtk_window_t *)cs->lpCreateParams;

        /* Store property so we can recover `wtk_window_t *` from handle. */
        SetPropA(hWnd, "wtk", (HANDLE)window);

        if (!window->closable) {
          EnableMenuItem(GetSystemMenu(hWnd, FALSE),
                         SC_CLOSE,
                         MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
        }

        window->surface =
          wtk_ogl_create_surface((wtk_uintptr_t)hWnd);

        window->canvas =
          wtk_canvas_create(window->width, window->height, 0x00000000);

        /* Defer event delivery since our structures aren't fully initialized yet. */
        PostMessage(hWnd, WM_CREATED, 0, 0);
      } return 0;

      case WM_CREATED: {
        wtk_window_event_t event;
        event.type = WTK_WINDOW_EVENT_OPENED;

        window->event_handler(handle, &event, window->event_handler_context);
      } return 0;

      case WM_CLOSE: {
        if (!window->closable) {
          return 0;
        }

        /* TODO(mtwilliams): Defer delivery? What guarantee do we make about
         * lifetime then? */
        wtk_window_event_t event;
        event.type = WTK_WINDOW_EVENT_CLOSED;
        event.closed.destroying = window->destroy_on_close;

        window->event_handler(handle, &event, window->event_handler_context);

        if (window->destroy_on_close) {
          /* See `wtk_window_close` for reasoning. */
          DestroyWindow(hWnd);
        }
      } return 0;

      case WM_NCDESTROY: {
        wtk_ogl_destroy_surface(window->surface);

        wtk_canvas_destroy(window->canvas);

        /* According to MSDN, all entires in the property list of a window must
         * be removed (via RemoveProp) before it is destroyed. In practice,
         * this doesn't make any material difference. Still, we try to be good
         * citizens.
         */
        RemovePropA(hWnd, "wtk");

        /* Finally, we clean up after ourselves. */
        wtk_free((void *)window);
      } return 0;

      case WM_MOVING: {
        /* TODO(mtwilliams): Convert coordinate space? */
        const RECT *drag = (const RECT *)lParam;

        window->x = drag->left;
        window->y = drag->top;

        wtk_window_event_t event;
        event.type = WTK_WINDOW_EVENT_MOVING;

        window->event_handler(handle, &event, window->event_handler_context);
      } return TRUE;

      case WM_MOVE: {
        window->x = LOWORD(lParam);
        window->y = HIWORD(lParam);

        wtk_window_event_t event;
        event.type = WTK_WINDOW_EVENT_MOVED;

        window->event_handler(handle, &event, window->event_handler_context);
      } return 0;

      case WM_SIZING: {
        /* TODO(mtwilliams): Convert coordinate space? */
        const RECT *drag = (const RECT *)lParam;

        window->x = drag->left;
        window->y = drag->top;
        window->width = drag->right - drag->left;
        window->height = drag->bottom - drag->top;

        wtk_window_event_t event;
        event.type = WTK_WINDOW_EVENT_RESIZING;

        window->event_handler(handle, &event, window->event_handler_context);
      } return TRUE;

      case WM_SIZE: {
        switch (wParam) {
          case SIZE_MAXIMIZED:
            /* Maximized. */
            break;
          case SIZE_MINIMIZED:
            /* Minimized. */
            break;
        }

        window->width = LOWORD(lParam);
        window->height = HIWORD(lParam);

        wtk_ogl_resize_surface(window->surface, window->width, window->height);

        window->canvas->width = window->width;
        window->canvas->height = window->height;

        wtk_window_event_t event;
        event.type = WTK_WINDOW_EVENT_RESIZED;

        window->event_handler(handle, &event, window->event_handler_context);
      } return 0;

      case WM_ERASEBKGND: {
        /* Prevent flickering. */
      } return TRUE;

      case WM_PAINT: {
        PAINTSTRUCT ps;

        if (BeginPaint(hWnd, &ps)) {
          /* TODO(mtwilliams): Respect `ps.fErase`? */
          wtk_rectangle_t dirty;

          dirty.x = ps.rcPaint.left;
          dirty.y = ps.rcPaint.top;
          dirty.w = ps.rcPaint.right - ps.rcPaint.left;
          dirty.h = ps.rcPaint.bottom - ps.rcPaint.top;

          wtk_renderer_invalidate(handle, &dirty);

          EndPaint(hWnd, &ps);
        }
      } return 0;
    }

    return DefWindowProcW(hWnd, uMsg, wParam, lParam);
  }

  /* PERF(mtwilliams): Skip entire function, not just registration. */
  static void wtk_register_window_class()
  {
    WNDCLASSEXW common_window_class;
    ZeroMemory((void *)&common_window_class, sizeof(WNDCLASSEXW));

    common_window_class.cbSize        = sizeof(WNDCLASSEXW);
    common_window_class.style         = CS_VREDRAW | CS_HREDRAW | CS_OWNDC;
    common_window_class.lpfnWndProc   = &wtk_window_callback;
    common_window_class.hInstance     = GetModuleHandle(NULL);
    common_window_class.hCursor       = LoadCursor(NULL, IDC_ARROW);
    common_window_class.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    common_window_class.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);
    common_window_class.lpszClassName = L"6bdf53a8-2d8f-4372-894e-08e28a8f0ad7";

    static const BOOL registered_class_succesfully =
      RegisterClassExW(&common_window_class);

    /* Should rarely, if ever fail. */
    wtk_assert_release(registered_class_succesfully);
  }
#elif WTK_PLATFORM == WTK_PLATFORM_MAC
#elif WTK_PLATFORM == WTK_PLATFORM_LINUX
#endif

WTK_END_EXTERN_C
