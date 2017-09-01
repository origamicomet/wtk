/*===-- wtk/gl.c --------------------------------------------*- mode: C -*-===*/
/*                                                                            */
/*                                     _   _                                  */
/*                               _ _ _| |_| |_                                */
/*                              | | | |  _| '_|                               */
/*                              |_____|_| |_,_|                               */
/*                                                                            */
/*       This file is distributed under the terms described in LICENSE.       */
/*                                                                            */
/*===----------------------------------------------------------------------===*/

#include "wtk/gl.h"

WTK_BEGIN_EXTERN_C

#if WTK_PLATFORM == WTK_PLATFORM_WINDOWS
  #include "wtk/wgl.h"

  typedef wtk_wgl_context_t wtk_ogl_context_t;

  #define wtk_ogl_get_proc_address wtk_wgl_get_proc_address
#endif

GLPUSHDEBUGGROUPPROC glPushDebugGroup;
GLPOPDEBUGGROUPPROC glPopDebugGroup;

GLOBJECTLABELPROC glObjectLabel;

GLFRAMETERMINATORGREMEDYPROC glFrameTerminatorGREMEDY;

GLGETBOOLEANVPROC glGetBooleanv;
GLGETINTEGERVPROC glGetIntegerv;
GLGETFLOATVPROC glGetFloatv;
GLGETDOUBLEVPROC glGetDoublev;
GLGETSTRINGPROC glGetString;

GLENABLEPROC  glEnable;
GLDISABLEPROC glDisable;

GLPOLYGONMODEPROC glPolygonMode;

GLFRONTFACEPROC glFrontFace;
GLCULLFACEPROC glCullFace;

GLBLENDFUNCSEPARATEPROC glBlendFuncSeparate;
GLBLENDEQUATIONSEPARATEPROC glBlendEquationSeparate;
GLBLENDCOLORPROC glBlendColor;

GLCOLORMASKPROC glColorMask;

GLDEPTHFUNCPROC glDepthFunc;
GLDEPTHMASKPROC glDepthMask;

GLSTENCILOPSEPARATEPROC glStencilOpSeparate;
GLSTENCILFUNCSEPARATEPROC glStencilFuncSeparate;
GLSTENCILMASKSEPARATEPROC glStencilMaskSeparate;

GLGENBUFFERSPROC glGenBuffers;
GLGENTEXTURESPROC glGenTextures;
GLGENFRAMEBUFFERSPROC glGenFramebuffers;
GLCREATESHADERPROC glCreateShader;
GLCREATEPROGRAMPROC glCreateProgram;

GLDELETEBUFFERSPROC glDeleteBuffers;
GLDELETETEXTURESPROC glDeleteTextures;
GLDELETESHADERPROC glDeleteShader;
GLDELETEPROGRAMPROC glDeleteProgram;
GLDELETEFRAMEBUFFERSPROC glDeleteFramebuffers;

GLVIEWPORTPROC glViewport;
GLSCISSORPROC  glScissor;

GLBINDBUFFERPROC glBindBuffer;

GLBUFFERDATAPROC glBufferData;
GLBUFFERSUBDATAPROC glBufferSubData;

GLMAPBUFFERPROC glMapBuffer;

GLUNMAPBUFFERPROC glUnmapBuffer;

GLACTIVETEXTUREPROC glActiveTexture;

GLBINDTEXTUREPROC glBindTexture;

GLTEXIMAGE1DPROC glTexImage1D;
GLTEXIMAGE2DPROC glTexImage2D;
GLTEXIMAGE3DPROC glTexImage3D;

GLTEXPARAMETERFPROC glTexParameterf;
GLTEXPARAMETERIPROC glTexParameteri;

GLGENERATEMIPMAPPROC glGenerateMipmap;

GLSHADERSOURCEPROC glShaderSource;
GLCOMPILESHADERPROC glCompileShader;

GLGETSHADERIVPROC glGetShaderiv;
GLGETSHADERINFOLOGPROC glGetShaderInfoLog;

GLATTACHSHADERPROC glAttachShader;
GLDETACHSHADERPROC glDetachShader;
GLLINKPROGRAMPROC glLinkProgram;

GLGETPROGRAMIVPROC glGetProgramiv;
GLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;

GLGETUNIFORMLOCATIONPROC glGetUniformLocation;

GLUNIFORM1FPROC glUniform1f;
GLUNIFORM2FPROC glUniform2f;
GLUNIFORM3FPROC glUniform3f;
GLUNIFORM4FPROC glUniform4f;

GLUNIFORM1IPROC glUniform1i;
GLUNIFORM2IPROC glUniform2i;
GLUNIFORM3IPROC glUniform3i;
GLUNIFORM4IPROC glUniform4i;

GLUNIFORM1UIPROC glUniform1ui;
GLUNIFORM2UIPROC glUniform2ui;
GLUNIFORM3UIPROC glUniform3ui;
GLUNIFORM4UIPROC glUniform4ui;

GLUSEPROGRAMPROC glUseProgram;

GLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
GLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;

GLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
GLVERTEXATTRIBIPOINTERPROC glVertexAttribIPointer;

GLBINDFRAMEBUFFERPROC glBindFramebuffer;

GLFRAMEBUFFERTEXTURE1DPROC glFramebufferTexture1D;
GLFRAMEBUFFERTEXTURE2DPROC glFramebufferTexture2D;
GLFRAMEBUFFERTEXTURE3DPROC glFramebufferTexture3D;

GLDRAWBUFFERPROC glDrawBuffer;
GLDRAWBUFFERSPROC glDrawBuffers;

GLCLEARCOLORPROC glClearColor;
GLCLEARDEPTHPROC glClearDepth;
GLCLEARSTENCILPROC glClearStencil;

GLCLEARPROC glClear;

typedef void (GL_ENTRY_POINT *GLGENVERTEXARRAYSPROC)(wtk_uint32_t n, wtk_uint32_t *arrays);
typedef void (GL_ENTRY_POINT *GLDELETEVERTEXARRAYSPROC)(wtk_uint32_t n, const wtk_uint32_t *arrays);
typedef void (GL_ENTRY_POINT *GLBINDVERTEXARRAYPROC)(wtk_uint32_t array);

GLGENVERTEXARRAYSPROC glGenVertexArrays;
GLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;
GLBINDVERTEXARRAYPROC glBindVertexArray;

GLDRAWARRAYSPROC glDrawArrays;
GLDRAWELEMENTSPROC glDrawElements;

GLBLITFRAMEBUFFERPROC glBlitFramebuffer;

GLFLUSHPROC  glFlush;
GLFINISHPROC glFinish;

wtk_uint32_t GL_KHR_debug = 0;
wtk_uint32_t GL_GREMEDY_frame_terminator = 0;

static void wtk_ogl_wrangle(void)
{
  static wtk_uint32_t wrangled = 0;

  if (wrangled)
    return;

  wrangled = 1;

  glGetBooleanv = (GLGETBOOLEANVPROC)wtk_ogl_get_proc_address("glGetBooleanv");
  glGetIntegerv = (GLGETINTEGERVPROC)wtk_ogl_get_proc_address("glGetIntegerv");
  glGetFloatv = (GLGETFLOATVPROC)wtk_ogl_get_proc_address("glGetFloatv");
  glGetDoublev = (GLGETDOUBLEVPROC)wtk_ogl_get_proc_address("glGetDoublev");
  glGetString = (GLGETSTRINGPROC)wtk_ogl_get_proc_address("glGetString");

  glEnable = (GLENABLEPROC)wtk_ogl_get_proc_address("glEnable");
  glDisable = (GLDISABLEPROC)wtk_ogl_get_proc_address("glDisable");

  glPolygonMode = (GLPOLYGONMODEPROC)wtk_ogl_get_proc_address("glPolygonMode");

  glFrontFace = (GLFRONTFACEPROC)wtk_ogl_get_proc_address("glFrontFace");
  glCullFace = (GLCULLFACEPROC)wtk_ogl_get_proc_address("glCullFace");

  glBlendFuncSeparate = (GLBLENDFUNCSEPARATEPROC)wtk_ogl_get_proc_address("glBlendFuncSeparate");
  glBlendEquationSeparate = (GLBLENDEQUATIONSEPARATEPROC)wtk_ogl_get_proc_address("glBlendEquationSeparate");
  glBlendColor = (GLBLENDCOLORPROC)wtk_ogl_get_proc_address("glBlendColor");

  glColorMask = (GLCOLORMASKPROC)wtk_ogl_get_proc_address("glColorMask");

  glDepthFunc = (GLDEPTHFUNCPROC)wtk_ogl_get_proc_address("glDepthFunc");
  glDepthMask = (GLDEPTHMASKPROC)wtk_ogl_get_proc_address("glDepthMask");

  glStencilOpSeparate = (GLSTENCILOPSEPARATEPROC)wtk_ogl_get_proc_address("glStencilOpSeparate");
  glStencilFuncSeparate = (GLSTENCILFUNCSEPARATEPROC)wtk_ogl_get_proc_address("glStencilFuncSeparate");
  glStencilMaskSeparate = (GLSTENCILMASKSEPARATEPROC)wtk_ogl_get_proc_address("glStencilMaskSeparate");

  glGenBuffers = (GLGENBUFFERSPROC)wtk_ogl_get_proc_address("glGenBuffers");
  glGenTextures = (GLGENTEXTURESPROC)wtk_ogl_get_proc_address("glGenTextures");
  glCreateShader = (GLCREATESHADERPROC)wtk_ogl_get_proc_address("glCreateShader");
  glCreateProgram = (GLCREATEPROGRAMPROC)wtk_ogl_get_proc_address("glCreateProgram");
  glGenFramebuffers = (GLGENFRAMEBUFFERSPROC)wtk_ogl_get_proc_address("glGenFramebuffers");

  glDeleteBuffers = (GLDELETEBUFFERSPROC)wtk_ogl_get_proc_address("glDeleteBuffers");
  glDeleteTextures = (GLDELETETEXTURESPROC)wtk_ogl_get_proc_address("glDeleteTextures");
  glDeleteShader = (GLDELETESHADERPROC)wtk_ogl_get_proc_address("glDeleteShader");
  glDeleteProgram = (GLDELETEPROGRAMPROC)wtk_ogl_get_proc_address("glDeleteProgram");
  glDeleteFramebuffers = (GLDELETEFRAMEBUFFERSPROC)wtk_ogl_get_proc_address("glDeleteFramebuffers");

  glViewport = (GLVIEWPORTPROC)wtk_ogl_get_proc_address("glViewport");
  glScissor = (GLSCISSORPROC)wtk_ogl_get_proc_address("glScissor");

  glBindBuffer = (GLBINDBUFFERPROC)wtk_ogl_get_proc_address("glBindBuffer");

  glBufferData = (GLBUFFERDATAPROC)wtk_ogl_get_proc_address("glBufferData");
  glBufferSubData = (GLBUFFERSUBDATAPROC)wtk_ogl_get_proc_address("glBufferSubData");

  glMapBuffer = (GLMAPBUFFERPROC)wtk_ogl_get_proc_address("glMapBuffer");
  glUnmapBuffer = (GLUNMAPBUFFERPROC)wtk_ogl_get_proc_address("glUnmapBuffer");

  glActiveTexture = (GLACTIVETEXTUREPROC)wtk_ogl_get_proc_address("glActiveTexture");

  glBindTexture = (GLBINDTEXTUREPROC)wtk_ogl_get_proc_address("glBindTexture");

  glTexImage1D = (GLTEXIMAGE1DPROC)wtk_ogl_get_proc_address("glTexImage1D");
  glTexImage2D = (GLTEXIMAGE2DPROC)wtk_ogl_get_proc_address("glTexImage2D");
  glTexImage3D = (GLTEXIMAGE3DPROC)wtk_ogl_get_proc_address("glTexImage3D");

  glTexParameterf = (GLTEXPARAMETERFPROC)wtk_ogl_get_proc_address("glTexParameterf");
  glTexParameteri = (GLTEXPARAMETERIPROC)wtk_ogl_get_proc_address("glTexParameteri");

  glGenerateMipmap = (GLGENERATEMIPMAPPROC)wtk_ogl_get_proc_address("glGenerateMipmap");

  glShaderSource = (GLSHADERSOURCEPROC)wtk_ogl_get_proc_address("glShaderSource");
  glCompileShader = (GLCOMPILESHADERPROC)wtk_ogl_get_proc_address("glCompileShader");

  glGetShaderiv = (GLGETSHADERIVPROC)wtk_ogl_get_proc_address("glGetShaderiv");
  glGetShaderInfoLog = (GLGETSHADERINFOLOGPROC)wtk_ogl_get_proc_address("glGetShaderInfoLog");

  glAttachShader = (GLATTACHSHADERPROC)wtk_ogl_get_proc_address("glAttachShader");
  glDetachShader = (GLDETACHSHADERPROC)wtk_ogl_get_proc_address("glDetachShader");
  glLinkProgram = (GLLINKPROGRAMPROC)wtk_ogl_get_proc_address("glLinkProgram");

  glGetProgramiv = (GLGETPROGRAMIVPROC)wtk_ogl_get_proc_address("glGetProgramiv");
  glGetProgramInfoLog = (GLGETPROGRAMINFOLOGPROC)wtk_ogl_get_proc_address("glGetProgramInfoLog");

  glGetUniformLocation = (GLGETUNIFORMLOCATIONPROC)wtk_ogl_get_proc_address("glGetUniformLocation");

  glUniform1f = (GLUNIFORM1FPROC)wtk_ogl_get_proc_address("glUniform1f");
  glUniform2f = (GLUNIFORM2FPROC)wtk_ogl_get_proc_address("glUniform2f");
  glUniform3f = (GLUNIFORM3FPROC)wtk_ogl_get_proc_address("glUniform3f");
  glUniform4f = (GLUNIFORM4FPROC)wtk_ogl_get_proc_address("glUniform4f");

  glUniform1i = (GLUNIFORM1IPROC)wtk_ogl_get_proc_address("glUniform1i");
  glUniform2i = (GLUNIFORM2IPROC)wtk_ogl_get_proc_address("glUniform2i");
  glUniform3i = (GLUNIFORM3IPROC)wtk_ogl_get_proc_address("glUniform3i");
  glUniform4i = (GLUNIFORM4IPROC)wtk_ogl_get_proc_address("glUniform4i");

  glUniform1ui = (GLUNIFORM1UIPROC)wtk_ogl_get_proc_address("glUniform1ui");
  glUniform2ui = (GLUNIFORM2UIPROC)wtk_ogl_get_proc_address("glUniform2ui");
  glUniform3ui = (GLUNIFORM3UIPROC)wtk_ogl_get_proc_address("glUniform3ui");
  glUniform4ui = (GLUNIFORM4UIPROC)wtk_ogl_get_proc_address("glUniform4ui");

  glUseProgram = (GLUSEPROGRAMPROC)wtk_ogl_get_proc_address("glUseProgram");

  glEnableVertexAttribArray = (GLENABLEVERTEXATTRIBARRAYPROC)wtk_ogl_get_proc_address("glEnableVertexAttribArray");
  glDisableVertexAttribArray = (GLDISABLEVERTEXATTRIBARRAYPROC)wtk_ogl_get_proc_address("glDisableVertexAttribArray");

  glVertexAttribPointer = (GLVERTEXATTRIBPOINTERPROC)wtk_ogl_get_proc_address("glVertexAttribPointer");
  glVertexAttribIPointer = (GLVERTEXATTRIBIPOINTERPROC)wtk_ogl_get_proc_address("glVertexAttribIPointer");

  glBindFramebuffer = (GLBINDFRAMEBUFFERPROC)wtk_ogl_get_proc_address("glBindFramebuffer");

  glFramebufferTexture1D = (GLFRAMEBUFFERTEXTURE1DPROC)wtk_ogl_get_proc_address("glFramebufferTexture1D");
  glFramebufferTexture2D = (GLFRAMEBUFFERTEXTURE2DPROC)wtk_ogl_get_proc_address("glFramebufferTexture2D");
  glFramebufferTexture3D = (GLFRAMEBUFFERTEXTURE3DPROC)wtk_ogl_get_proc_address("glFramebufferTexture3D");

  glDrawBuffer = (GLDRAWBUFFERPROC)wtk_ogl_get_proc_address("glDrawBuffer");
  glDrawBuffers = (GLDRAWBUFFERSPROC)wtk_ogl_get_proc_address("glDrawBuffers");

  glClearColor = (GLCLEARCOLORPROC)wtk_ogl_get_proc_address("glClearColor");
  glClearDepth = (GLCLEARDEPTHPROC)wtk_ogl_get_proc_address("glClearDepth");
  glClearStencil = (GLCLEARSTENCILPROC)wtk_ogl_get_proc_address("glClearStencil");

  glClear = (GLCLEARPROC)wtk_ogl_get_proc_address("glClear");

  glGenVertexArrays = (GLGENVERTEXARRAYSPROC)wtk_ogl_get_proc_address("glGenVertexArrays");
  glDeleteVertexArrays = (GLDELETEVERTEXARRAYSPROC)wtk_ogl_get_proc_address("glDeleteVertexArrays");
  glBindVertexArray = (GLBINDVERTEXARRAYPROC)wtk_ogl_get_proc_address("glBindVertexArray");

  glDrawArrays = (GLDRAWARRAYSPROC)wtk_ogl_get_proc_address("glDrawArrays");
  glDrawElements = (GLDRAWELEMENTSPROC)wtk_ogl_get_proc_address("glDrawElements");

  glBlitFramebuffer = (GLBLITFRAMEBUFFERPROC)wtk_ogl_get_proc_address("glBlitFramebuffer");

  glFlush = (GLFLUSHPROC)wtk_ogl_get_proc_address("glFlush");
  glFinish = (GLFINISHPROC)wtk_ogl_get_proc_address("glFinish");

  /* TODO(mtwilliams): Check for extensions. */
#if 0
  wtk_ogl_check_for_extensions();
#endif

  if (GL_KHR_debug) {
    glPushDebugGroup = (GLPUSHDEBUGGROUPPROC)wtk_ogl_get_proc_address("glPushDebugGroup");
    glPopDebugGroup  = (GLPOPDEBUGGROUPPROC)wtk_ogl_get_proc_address("glPopDebugGroup");
    glObjectLabel    = (GLOBJECTLABELPROC)wtk_ogl_get_proc_address("glObjectLabel");
  } else {
    glPushDebugGroup = NULL;
    glPopDebugGroup  = NULL;
    glObjectLabel    = NULL;
  }

  if (GL_GREMEDY_frame_terminator) {
    glFrameTerminatorGREMEDY = (GLFRAMETERMINATORGREMEDYPROC)wtk_ogl_get_proc_address("glFrameTerminatorGREMEDY");
  } else {
    glFrameTerminatorGREMEDY = NULL;
  }
}

/* We share a context rather than creating one per surface. */
static wtk_ogl_context_t *context = NULL;

void wtk_ogl_init(void)
{
#if WTK_PLATFORM == WTK_PLATFORM_WINDOWS
  wtk_wgl_init();

  wtk_wgl_context_creation_params_t context_creation_params; {
    context_creation_params.version.major = 3;

  #if WTK_CONFIGURATION == WTK_CONFIGURATION_DEBUG
    /* Tools, like RenderDoc, require 3.2+. */
    context_creation_params.version.minor = 2;
  #else
    context_creation_params.version.minor = 1;
  #endif

    context_creation_params.flags = 0x00000000;

  #if WTK_CONFIGURATION == WTK_CONFIGURATION_DEBUG
    context_creation_params.flags |= WTK_WGL_CONTEXT_DEBUG;
  #endif

    context_creation_params.share = NULL;
  }

  context = wtk_wgl_create_context(&context_creation_params);

  wtk_wgl_bind(context, NULL);
#elif WTK_PLATFORM == WTK_PLATFORM_MAC
  wtk_agl_init();
#elif WTK_PLATFORM == WTK_PLATFORM_LINUX
  wtk_glx_init();
#endif

  wtk_ogl_wrangle();

  /* We draw to the backbuffer for the currently bound surface unless otherwise
   * specified. Don't change this without understanding how presentation works.
   * See `wtk_ogl_present` for details.
   */
  glDrawBuffer(GL_BACK);

  /* HACK(mtwilliams): OpenGL 3.2 onwards no longer provides an implicit vertex
   * array object, but requires a vertex array object for vertex specification,
   * so we mimic that behavior by generating our own implict vertex array
   * object.
   */
  wtk_uint32_t vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  /* Insert a frame terminator to prevent "junk" from showing up in the first frame. */
  if (GL_GREMEDY_frame_terminator)
    glFrameTerminatorGREMEDY();
}

void wtk_ogl_shutdown(void)
{
  /* NOTE(mtwilliams): Unbind context to prevent crashes on some drivers by
   * making sure no context is current prior to its deletion.
   */
#if WTK_PLATFORM == WTK_PLATFORM_WINDOWS
  wtk_wgl_bind(NULL, NULL);
  wtk_wgl_destroy_context(context);
  wtk_wgl_shutdown();
#elif WTK_PLATFORM == WTK_PLATFORM_MAC
  wtk_agl_bind(NULL, NULL);
  wtk_agl_shutdown();
#elif WTK_PLATFORM == WTK_PLATFORM_LINUX
  wtk_glx_bind(NULL, NULL);
  wtk_glx_shutdown();
#endif
}

struct wtk_ogl_surface {
  wtk_uint32_t width;
  wtk_uint32_t height;

  /* We actually render to an texture and copy its contents to the surface
   * prior to presentation.
   */
  wtk_uint32_t fbo;
  wtk_uint32_t offscreen;

#if WTK_PLATFORM == WTK_PLATFORM_WINDOWS
  wtk_wgl_surface_t *underlying;
#endif
};

wtk_ogl_surface_t *wtk_ogl_create_surface(wtk_uintptr_t window)
{
  wtk_ogl_surface_t *surface =
    (wtk_ogl_surface_t *)wtk_allocate_s(sizeof(wtk_ogl_surface_t), 16);

#if WTK_PLATFORM == WTK_PLATFORM_WINDOWS
  surface->underlying = wtk_wgl_create_surface(context, (HWND)window);

  wtk_wgl_dimensions_of_surface(surface->underlying,
                                &surface->width,
                                &surface->height);
#endif

  glGenTextures(1, &surface->offscreen);
  glBindTexture(GL_TEXTURE_2D, surface->offscreen);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, surface->width, surface->height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
  glBindTexture(GL_TEXTURE_2D, 0);

  glGenFramebuffers(1, &surface->fbo);
  glBindFramebuffer(GL_FRAMEBUFFER, surface->fbo);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT + 0, GL_TEXTURE_2D, surface->offscreen, 0);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  return surface;
}

void wtk_ogl_destroy_surface(wtk_ogl_surface_t *surface) {
  glDeleteFramebuffers(1, &surface->fbo);
  glDeleteTextures(1, &surface->offscreen);

#if WTK_PLATFORM == WTK_PLATFORM_WINDOWS
  wtk_wgl_destroy_surface(surface->underlying);
#endif

  wtk_free((void *)surface);
}

void wtk_ogl_resize_surface(wtk_ogl_surface_t *surface,
                            wtk_uint32_t width,
                            wtk_uint32_t height)
{
  surface->width = width;
  surface->height = height;

  /* PERF(mtwilliams): Allegedly slow on some drivers. Should recreate the
   * framebuffer object?
   */
  glBindTexture(GL_TEXTURE_2D, surface->offscreen);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
}

void wtk_ogl_dimensions_of_surface(const wtk_ogl_surface_t *surface,
                                   wtk_uint32_t *width,
                                   wtk_uint32_t *height)
{
  *width = surface->width;
  *height = surface->height;
}

void wtk_ogl_bind(wtk_ogl_surface_t *surface)
{
  glBindFramebuffer(GL_FRAMEBUFFER, surface ? surface->fbo : 0);
}

void wtk_ogl_present(wtk_ogl_surface_t *surface)
{
  /* TODO(mtwilliams): Resolve swap chain if multisampling. */

#if WTK_PLATFORM == WTK_PLATFORM_WINDOWS
  wtk_uint32_t width, height;
  wtk_wgl_dimensions_of_surface(surface->underlying, &width, &height);

  /* Bind to appropriate surface. */
  wtk_wgl_bind(context, surface->underlying);
#endif

  glViewport(0, 0, width, height);
  glScissor(0, 0, width, height);

  /* Resolve and scale into backbuffer. */
  glBindFramebuffer(GL_READ_FRAMEBUFFER, surface->fbo);
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
  glBlitFramebuffer(0, 0, surface->width, surface->height, 0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_LINEAR);

#if WTK_PLATFORM == WTK_PLATFORM_WINDOWS
  /* Swap. */
  wtk_wgl_present(surface->underlying, WTK_WGL_PRESENT_SYNCHRONIZE);

  /* Unbind. */
  wtk_wgl_bind(context, NULL);
#endif
}

WTK_END_EXTERN_C
