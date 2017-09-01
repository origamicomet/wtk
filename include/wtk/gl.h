/*===-- wtk/gl.h --------------------------------------------*- mode: C -*-===*/
/*                                                                            */
/*                                     _   _                                  */
/*                               _ _ _| |_| |_                                */
/*                              | | | |  _| '_|                               */
/*                              |_____|_| |_,_|                               */
/*                                                                            */
/*       This file is distributed under the terms described in LICENSE.       */
/*                                                                            */
/*===----------------------------------------------------------------------===*/

#ifndef _WTK_GL_H_
#define _WTK_GL_H_

#include "wtk/foundation.h"

/*
 * General
 */

#define GL_MAJOR_VERSION                  0x821B
#define GL_MINOR_VERSION                  0x821C

#define GL_EXTENSIONS                     0x1F03
#define GL_NUM_EXTENSIONS                 0x821D

#define GL_TRUE                           1
#define GL_FALSE                          0

#define GL_NONE                           0
#define GL_FRONT                          0x0404
#define GL_BACK                           0x0405
#define GL_FRONT_AND_BACK                 0x0408

/*
 * Capabilities
 */

#define GL_CULL_FACE                      0x0B44

#define GL_BLEND                          0x0BE2

#define GL_DEPTH_TEST                     0x0B71
#define GL_STENCIL_TEST                   0x0B90
#define GL_SCISSOR_TEST                   0x0C11

#define GL_FRAMEBUFFER_SRGB               0x8DB9

/*
 * Debug
 */

#define GL_DEBUG_OUTPUT                   0x92E0
#define GL_DEBUG_OUTPUT_SYNCHRONOUS       0x8242

#define GL_DEBUG_CALLBACK_FUNCTION        0x8244
#define GL_DEBUG_CALLBACK_USER_PARAM      0x8245

#define GL_DEBUG_SOURCE_API               0x8246
#define GL_DEBUG_SOURCE_WINDOW_SYSTEM     0x8247
#define GL_DEBUG_SOURCE_SHADER_COMPILER   0x8248
#define GL_DEBUG_SOURCE_THIRD_PARTY       0x8249
#define GL_DEBUG_SOURCE_APPLICATION       0x824A
#define GL_DEBUG_SOURCE_OTHER             0x824B

#define GL_DEBUG_TYPE_ERROR               0x824C
#define GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR 0x824D
#define GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR  0x824E
#define GL_DEBUG_TYPE_PORTABILITY         0x824F
#define GL_DEBUG_TYPE_PERFORMANCE         0x8250
#define GL_DEBUG_TYPE_OTHER               0x8251
#define GL_DEBUG_TYPE_MARKER              0x8268

#define GL_DEBUG_TYPE_PUSH_GROUP          0x8269
#define GL_DEBUG_TYPE_POP_GROUP           0x826A

#define GL_DEBUG_SEVERITY_HIGH            0x9146
#define GL_DEBUG_SEVERITY_MEDIUM          0x9147
#define GL_DEBUG_SEVERITY_LOW             0x9148
#define GL_DEBUG_SEVERITY_NOTIFICATION    0x826B

/*
 * Types
 */

#define GL_BYTE                           0x1400
#define GL_UNSIGNED_BYTE                  0x1401
#define GL_SHORT                          0x1402
#define GL_UNSIGNED_SHORT                 0x1403
#define GL_INT                            0x1404
#define GL_UNSIGNED_INT                   0x1405
#define GL_HALF_FLOAT                     0x140B
#define GL_FLOAT                          0x1406
#define GL_DOUBLE                         0x140A

/*
 * Windings
 */

#define GL_CW                             0x0900
#define GL_CCW                            0x0901

/*
 * Polygon Modes
 */

#define GL_POINT                          0x1B00
#define GL_LINE                           0x1B01
#define GL_FILL                           0x1B02

/*
 * Functions
 */

#define GL_FUNC_ADD                       0x8006
#define GL_FUNC_SUBTRACT                  0x800A
#define GL_FUNC_REVERSE_SUBTRACT          0x800B
#define GL_MIN                            0x8007
#define GL_MAX                            0x8008

/*
 * Operations
 */

#define GL_CLEAR                          0x1500
#define GL_AND                            0x1501
#define GL_AND_REVERSE                    0x1502
#define GL_COPY                           0x1503
#define GL_AND_INVERTED                   0x1504
#define GL_NOOP                           0x1505
#define GL_XOR                            0x1506
#define GL_OR                             0x1507
#define GL_NOR                            0x1508
#define GL_EQUIV                          0x1509
#define GL_INVERT                         0x150A
#define GL_OR_REVERSE                     0x150B
#define GL_COPY_INVERTED                  0x150C
#define GL_OR_INVERTED                    0x150D
#define GL_NAND                           0x150E
#define GL_SET                            0x150F
#define GL_KEEP                           0x1E00
#define GL_REPLACE                        0x1E01
#define GL_INCR                           0x1E02
#define GL_DECR                           0x1E03
#define GL_INCR_WRAP                      0x8507
#define GL_DECR_WRAP                      0x8508

/*
 * Comparisons
 */

#define GL_NEVER                          0x0200
#define GL_LESS                           0x0201
#define GL_EQUAL                          0x0202
#define GL_LEQUAL                         0x0203
#define GL_GREATER                        0x0204
#define GL_NOT_EQUAL                      0x0205
#define GL_GEQUAL                         0x0206
#define GL_ALWAYS                         0x0207

/*
 * Equations
 */

#define GL_ZERO                           0x0000
#define GL_ONE                            0x0001
#define GL_SRC_COLOR                      0x0300
#define GL_ONE_MINUS_SRC_COLOR            0x0301
#define GL_SRC_ALPHA                      0x0302
#define GL_ONE_MINUS_SRC_ALPHA            0x0303
#define GL_DST_ALPHA                      0x0304
#define GL_ONE_MINUS_DST_ALPHA            0x0305
#define GL_DST_COLOR                      0x0306
#define GL_ONE_MINUS_DST_COLOR            0x0307
#define GL_SRC_ALPHA_SATURATE             0x0308
#define GL_CONSTANT_COLOR                 0x8001
#define GL_ONE_MINUS_CONSTANT_COLOR       0x8002

/*
 * Formats
 */

#define GL_RED                            0x1903
#define GL_RG                             0x8227
#define GL_RGB                            0x1907
#define GL_RGBA                           0x1908

#define GL_DEPTH_COMPONENT                0x1902
#define GL_DEPTH_STENCIL                  0x84F9

#define GL_R8                             0x8229
#define GL_R16F                           0x822D
#define GL_R32F                           0x822E
#define GL_R8I                            0x8231
#define GL_R16I                           0x8233
#define GL_R32I                           0x8235
#define GL_R8UI                           0x8232
#define GL_R16UI                          0x8234
#define GL_R32UI                          0x8236
#define GL_RG8                            0x822B
#define GL_RG16F                          0x822F
#define GL_RG32F                          0x8230
#define GL_RG8I                           0x8237
#define GL_RG16I                          0x8239
#define GL_RG32I                          0x823B
#define GL_RG8UI                          0x8238
#define GL_RG16UI                         0x823A
#define GL_RG32UI                         0x823C
#define GL_RGB16F                         0x881B
#define GL_RGB32F                         0x8815
#define GL_RGB32I                         0x8D83
#define GL_RGB32UI                        0x8D71
#define GL_RGBA8                          0x8058
#define GL_RGBA16F                        0x881A
#define GL_RGBA32F                        0x8814
#define GL_RGBA8I                         0x8D8E
#define GL_RGBA16I                        0x8D88
#define GL_RGBA32I                        0x8D82
#define GL_RGBA8UI                        0x8D7C
#define GL_RGBA16UI                       0x8D76
#define GL_RGBA32UI                       0x8D70

#define GL_RGB8                           0x8051
#define GL_SRGB8                          0x8C41
#define GL_SRGB8_ALPHA8                   0x8C43

#define GL_DEPTH_COMPONENT16              0x81A5
#define GL_DEPTH_COMPONENT24              0x81A6
#define GL_DEPTH_COMPONENT32              0x81A7

#define GL_DEPTH24_STENCIL8               0x88F0

/*
 * Buffers
 */

#define GL_BUFFER                         0x82E0

#define GL_ARRAY_BUFFER                   0x8892
#define GL_ELEMENT_ARRAY_BUFFER           0x8893
#define GL_UNIFORM_BUFFER                 0x8A11

#define GL_STATIC_DRAW                    0x88E4
#define GL_STREAM_DRAW                    0x88E0
#define GL_DYNAMIC_DRAW                   0x88E8

#define GL_MAP_READ_BIT                   0x0001
#define GL_MAP_WRITE_BIT                  0x0002

/*
 * Textures
 */

#define GL_MAX_TEXTURE_IMAGE_UNITS        0x8872

#define GL_TEXTURE                        0x1702

#define GL_TEXTURE_0                      0x84C0
#define GL_TEXTURE_1                      0x84C1
#define GL_TEXTURE_2                      0x84C2
#define GL_TEXTURE_3                      0x84C3
#define GL_TEXTURE_4                      0x84C4
#define GL_TEXTURE_5                      0x84C5
#define GL_TEXTURE_6                      0x84C6
#define GL_TEXTURE_7                      0x84C7
#define GL_TEXTURE_8                      0x84C8

#define GL_TEXTURE_1D                     0x0DE0
#define GL_TEXTURE_2D                     0x0DE1
#define GL_TEXTURE_3D                     0x806F

#define GL_TEXTURE_1D_ARRAY               0x8C18
#define GL_TEXTURE_2D_ARRAY               0x8C1A

#define GL_TEXTURE_MAG_FILTER             0x2800
#define GL_TEXTURE_MIN_FILTER             0x2801

#define GL_TEXTURE_WRAP_S                 0x2802
#define GL_TEXTURE_WRAP_T                 0x2803
#define GL_TEXTURE_WRAP_R                 0x8072

/*
 * Filters
 */

#define GL_NEAREST                        0x2600
#define GL_LINEAR                         0x2601
#define GL_NEAREST_MIPMAP_NEAREST         0x2700
#define GL_LINEAR_MIPMAP_NEAREST          0x2701
#define GL_NEAREST_MIPMAP_LINEAR          0x2702
#define GL_LINEAR_MIPMAP_LINEAR           0x2703

/*
 * Wrapping
 */

#define GL_REPEAT                         0x2901
#define GL_MIRRORED_REPEAT                0x8370
#define GL_CLAMP_TO_EDGE                  0x812F
#define GL_CLAMP_TO_BORDER                0x812D

/*
 * Shaders
 */

#define GL_SHADER                         0x82E1
#define GL_PROGRAM                        0x82E2

#define GL_VERTEX_SHADER                  0x8B31
#define GL_FRAGMENT_SHADER                0x8B30

#define GL_COMPILE_STATUS                 0x8B81
#define GL_LINK_STATUS                    0x8B82
#define GL_VALIDATE_STATUS                0x8B83
#define GL_DELETE_STATUS                  0x8B80

#define GL_INFO_LOG_LENGTH                0x8B84

/*
 * Targets
 */

#define GL_FRAMEBUFFER                    0x8D40
#define GL_READ_FRAMEBUFFER               0x8CA8
#define GL_DRAW_FRAMEBUFFER               0x8CA9

#define GL_COLOR_ATTACHMENT               0x8CE0
#define GL_DEPTH_ATTACHMENT               0x8D00
#define GL_STENCIL_ATTACHMENT             0x8D20
#define GL_DEPTH_STENCIL_ATTACHMENT       0x821A

#define GL_COLOR                          0x1800
#define GL_DEPTH                          0x1801
#define GL_STENCIL                        0x1802

#define GL_DEPTH_BUFFER_BIT               0x00000100
#define GL_STENCIL_BUFFER_BIT             0x00000400
#define GL_COLOR_BUFFER_BIT               0x00004000

#define GL_DRAW_BUFFER                    0x8825

/*
 * Topology
 */

#define GL_POINTS                         0x0000
#define GL_LINES                          0x0001
#define GL_LINE_LOOP                      0x0002
#define GL_LINE_STRIP                     0x0003
#define GL_TRIANGLES                      0x0004
#define GL_TRIANGLE_STRIP                 0x0005
#define GL_TRIANGLE_FAN                   0x0006

WTK_BEGIN_EXTERN_C

/*
 * Imports
 */

#if WTK_PLATFORM == WTK_PLATFORM_WINDOWS
  /* Decorator for dynamic imports. */
  #define GL_ENTRY_POINT __stdcall
#endif

typedef void (GL_ENTRY_POINT *GLPUSHDEBUGGROUPPROC)(wtk_uint32_t source, wtk_uint32_t id, wtk_uint32_t length, const char *label);
typedef void (GL_ENTRY_POINT *GLPOPDEBUGGROUPPROC)(void);

extern GLPUSHDEBUGGROUPPROC glPushDebugGroup;
extern GLPOPDEBUGGROUPPROC glPopDebugGroup;

typedef void (GL_ENTRY_POINT *GLOBJECTLABELPROC)(wtk_uint32_t identifier, wtk_uint32_t name, wtk_uint32_t length, const char *label);

extern GLOBJECTLABELPROC glObjectLabel;

typedef void (GL_ENTRY_POINT *GLFRAMETERMINATORGREMEDYPROC)(void);

extern GLFRAMETERMINATORGREMEDYPROC glFrameTerminatorGREMEDY;

typedef void (GL_ENTRY_POINT *GLGETBOOLEANVPROC)(wtk_uint32_t parameter, wtk_uint32_t *value);
typedef void (GL_ENTRY_POINT *GLGETINTEGERVPROC)(wtk_uint32_t parameter, wtk_int32_t *value);
typedef void (GL_ENTRY_POINT *GLGETFLOATVPROC)(wtk_uint32_t parameter, wtk_float32_t *value);
typedef void (GL_ENTRY_POINT *GLGETDOUBLEVPROC)(wtk_uint32_t parameter, wtk_float64_t *value);
typedef const char *(GL_ENTRY_POINT *GLGETSTRINGPROC)(wtk_uint32_t name);

extern GLGETBOOLEANVPROC glGetBooleanv;
extern GLGETINTEGERVPROC glGetIntegerv;
extern GLGETFLOATVPROC glGetFloatv;
extern GLGETDOUBLEVPROC glGetDoublev;
extern GLGETSTRINGPROC glGetString;

typedef void (GL_ENTRY_POINT *GLENABLEPROC)(wtk_uint32_t capability);
typedef void (GL_ENTRY_POINT *GLDISABLEPROC)(wtk_uint32_t capability);

extern GLENABLEPROC  glEnable;
extern GLDISABLEPROC glDisable;

typedef void (GL_ENTRY_POINT *GLPOLYGONMODEPROC)(wtk_uint32_t face, wtk_uint32_t mode);

extern GLPOLYGONMODEPROC glPolygonMode;

typedef void (GL_ENTRY_POINT *GLFRONTFACEPROC)(wtk_uint32_t mode);
typedef void (GL_ENTRY_POINT *GLCULLFACEPROC)(wtk_uint32_t mode);

extern GLFRONTFACEPROC glFrontFace;
extern GLCULLFACEPROC glCullFace;

typedef void (GL_ENTRY_POINT *GLBLENDFUNCSEPARATEPROC)(wtk_uint32_t src_factor_rgb, wtk_uint32_t dst_factor_rgb, wtk_uint32_t src_factor_alpha, wtk_uint32_t dst_factor_alpha);
typedef void (GL_ENTRY_POINT *GLBLENDEQUATIONSEPARATEPROC)(wtk_uint32_t rgb, wtk_uint32_t alpha);
typedef void (GL_ENTRY_POINT *GLBLENDCOLORPROC)(wtk_float32_t red, wtk_float32_t green, wtk_float32_t blue, wtk_float32_t alpha);

extern GLBLENDFUNCSEPARATEPROC glBlendFuncSeparate;
extern GLBLENDEQUATIONSEPARATEPROC glBlendEquationSeparate;
extern GLBLENDCOLORPROC glBlendColor;

typedef void (GL_ENTRY_POINT *GLCOLORMASKPROC)(wtk_uint32_t r, wtk_uint32_t g, wtk_uint32_t b, wtk_uint32_t a);

extern GLCOLORMASKPROC glColorMask;

typedef void (GL_ENTRY_POINT *GLDEPTHFUNCPROC)(wtk_uint32_t func);
typedef void (GL_ENTRY_POINT *GLDEPTHMASKPROC)(wtk_uint32_t flag);

extern GLDEPTHFUNCPROC glDepthFunc;
extern GLDEPTHMASKPROC glDepthMask;

typedef void (GL_ENTRY_POINT *GLSTENCILOPSEPARATEPROC)(wtk_uint32_t face, wtk_uint32_t sfail, wtk_uint32_t dpfail, wtk_uint32_t dppass);
typedef void (GL_ENTRY_POINT *GLSTENCILFUNCSEPARATEPROC)(wtk_uint32_t face, wtk_uint32_t func, wtk_int32_t ref, wtk_uint32_t mask);
typedef void (GL_ENTRY_POINT *GLSTENCILMASKSEPARATEPROC)(wtk_uint32_t face, wtk_uint32_t mask);

extern GLSTENCILOPSEPARATEPROC glStencilOpSeparate;
extern GLSTENCILFUNCSEPARATEPROC glStencilFuncSeparate;
extern GLSTENCILMASKSEPARATEPROC glStencilMaskSeparate;

typedef void (GL_ENTRY_POINT *GLGENBUFFERSPROC)(wtk_uint32_t n, wtk_uint32_t *buffers);
typedef void (GL_ENTRY_POINT *GLGENTEXTURESPROC)(wtk_uint32_t n, wtk_uint32_t *textures);
typedef void (GL_ENTRY_POINT *GLGENFRAMEBUFFERSPROC)(wtk_uint32_t n, wtk_uint32_t *framebuffers);
typedef wtk_uint32_t (GL_ENTRY_POINT *GLCREATESHADERPROC)(wtk_uint32_t type);
typedef wtk_uint32_t (GL_ENTRY_POINT *GLCREATEPROGRAMPROC)(void);

extern GLGENBUFFERSPROC glGenBuffers;
extern GLGENTEXTURESPROC glGenTextures;
extern GLGENFRAMEBUFFERSPROC glGenFramebuffers;
extern GLCREATESHADERPROC glCreateShader;
extern GLCREATEPROGRAMPROC glCreateProgram;

typedef void (GL_ENTRY_POINT *GLDELETEBUFFERSPROC)(wtk_uint32_t n, const wtk_uint32_t *buffers);
typedef void (GL_ENTRY_POINT *GLDELETETEXTURESPROC)(wtk_uint32_t n, const wtk_uint32_t *textures);
typedef void (GL_ENTRY_POINT *GLDELETESHADERPROC)(wtk_uint32_t shader);
typedef void (GL_ENTRY_POINT *GLDELETEPROGRAMPROC)(wtk_uint32_t program);
typedef void (GL_ENTRY_POINT *GLDELETEFRAMEBUFFERSPROC)(wtk_uint32_t n, const wtk_uint32_t *framebuffers);

extern GLDELETEBUFFERSPROC glDeleteBuffers;
extern GLDELETETEXTURESPROC glDeleteTextures;
extern GLDELETESHADERPROC glDeleteShader;
extern GLDELETEPROGRAMPROC glDeleteProgram;
extern GLDELETEFRAMEBUFFERSPROC glDeleteFramebuffers;

typedef void (GL_ENTRY_POINT *GLVIEWPORTPROC)(wtk_int32_t x, wtk_int32_t y, wtk_int32_t w, wtk_int32_t h);
typedef void (GL_ENTRY_POINT *GLSCISSORPROC)(wtk_int32_t x, wtk_int32_t y, wtk_int32_t w, wtk_int32_t h);

extern GLVIEWPORTPROC glViewport;
extern GLSCISSORPROC  glScissor;

typedef void (GL_ENTRY_POINT *GLBINDBUFFERPROC)(wtk_uint32_t target, wtk_uint32_t buffer);

extern GLBINDBUFFERPROC glBindBuffer;

typedef void (GL_ENTRY_POINT *GLBUFFERDATAPROC)(wtk_uint32_t target, wtk_size_t size, const void *data, wtk_uint32_t usage);
typedef void (GL_ENTRY_POINT *GLBUFFERSUBDATAPROC)(wtk_uint32_t target, wtk_uintptr_t offset, wtk_size_t length, const void *data);

extern GLBUFFERDATAPROC glBufferData;
extern GLBUFFERSUBDATAPROC glBufferSubData;

typedef void *(GL_ENTRY_POINT *GLMAPBUFFERPROC)(wtk_uint32_t target, wtk_uint32_t access);

extern GLMAPBUFFERPROC glMapBuffer;

typedef void (GL_ENTRY_POINT *GLUNMAPBUFFERPROC)(wtk_uint32_t target);

extern GLUNMAPBUFFERPROC glUnmapBuffer;

typedef void (GL_ENTRY_POINT *GLACTIVETEXTUREPROC)(wtk_uint32_t slot);

extern GLACTIVETEXTUREPROC glActiveTexture;

typedef void (GL_ENTRY_POINT *GLBINDTEXTUREPROC)(wtk_uint32_t target, wtk_uint32_t texture);

extern GLBINDTEXTUREPROC glBindTexture;

typedef void (GL_ENTRY_POINT *GLTEXIMAGE1DPROC)(wtk_uint32_t target,
                                                wtk_uint32_t level,
                                                wtk_uint32_t internal_format,
                                                wtk_uint32_t width,
                                                wtk_uint32_t border,
                                                wtk_uint32_t format,
                                                wtk_uint32_t type,
                                                const void *data);

typedef void (GL_ENTRY_POINT *GLTEXIMAGE2DPROC)(wtk_uint32_t target,
                                                wtk_uint32_t level,
                                                wtk_uint32_t internal_format,
                                                wtk_uint32_t width,
                                                wtk_uint32_t height,
                                                wtk_uint32_t border,
                                                wtk_uint32_t format,
                                                wtk_uint32_t type,
                                                const void *data);

typedef void (GL_ENTRY_POINT *GLTEXIMAGE3DPROC)(wtk_uint32_t target,
                                                wtk_uint32_t level,
                                                wtk_uint32_t internal_format,
                                                wtk_uint32_t width,
                                                wtk_uint32_t height,
                                                wtk_uint32_t depth,
                                                wtk_uint32_t border,
                                                wtk_uint32_t format,
                                                wtk_uint32_t type,
                                                const void *data);

extern GLTEXIMAGE1DPROC glTexImage1D;
extern GLTEXIMAGE2DPROC glTexImage2D;
extern GLTEXIMAGE3DPROC glTexImage3D;

typedef void (GL_ENTRY_POINT *GLTEXPARAMETERFPROC)(wtk_uint32_t target, wtk_uint32_t name, wtk_float32_t value);
typedef void (GL_ENTRY_POINT *GLTEXPARAMETERIPROC)(wtk_uint32_t target, wtk_uint32_t name, wtk_int32_t value);

extern GLTEXPARAMETERFPROC glTexParameterf;
extern GLTEXPARAMETERIPROC glTexParameteri;

typedef void (GL_ENTRY_POINT *GLGENERATEMIPMAPPROC)(wtk_uint32_t target);

/* PERF(mtwilliams): Generate manually. Drivers can be really bad at generating mipmaps. */
extern GLGENERATEMIPMAPPROC glGenerateMipmap;

typedef void (GL_ENTRY_POINT *GLSHADERSOURCEPROC)(wtk_uint32_t shader, wtk_uint32_t count, const char * const *sources, const wtk_uint32_t *lengths);
typedef void (GL_ENTRY_POINT *GLCOMPILESHADERPROC)(wtk_uint32_t shader);

extern GLSHADERSOURCEPROC glShaderSource;
extern GLCOMPILESHADERPROC glCompileShader;

typedef void (GL_ENTRY_POINT *GLGETSHADERIVPROC)(wtk_uint32_t shader, wtk_uint32_t pname, wtk_int32_t *params);
typedef void (GL_ENTRY_POINT *GLGETSHADERINFOLOGPROC)(wtk_uint32_t shader, wtk_int32_t size, wtk_int32_t *length, char *buffer);

extern GLGETSHADERIVPROC glGetShaderiv;
extern GLGETSHADERINFOLOGPROC glGetShaderInfoLog;

typedef void (GL_ENTRY_POINT *GLATTACHSHADERPROC)(wtk_uint32_t program, wtk_uint32_t shader);
typedef void (GL_ENTRY_POINT *GLDETACHSHADERPROC)(wtk_uint32_t program, wtk_uint32_t shader);
typedef void (GL_ENTRY_POINT *GLLINKPROGRAMPROC)(wtk_uint32_t program);

extern GLATTACHSHADERPROC glAttachShader;
extern GLDETACHSHADERPROC glDetachShader;
extern GLLINKPROGRAMPROC glLinkProgram;

typedef void (GL_ENTRY_POINT *GLGETPROGRAMIVPROC)(wtk_uint32_t program, wtk_uint32_t pname, wtk_int32_t *params);
typedef void (GL_ENTRY_POINT *GLGETPROGRAMINFOLOGPROC)(wtk_uint32_t program, wtk_int32_t size, wtk_int32_t *length, char *buffer);

extern GLGETPROGRAMIVPROC glGetProgramiv;
extern GLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;

typedef wtk_uint32_t (GL_ENTRY_POINT *GLGETUNIFORMLOCATIONPROC)(wtk_uint32_t program, const char *name);

extern GLGETUNIFORMLOCATIONPROC glGetUniformLocation;

typedef void (GL_ENTRY_POINT *GLUNIFORM1FPROC)(wtk_uint32_t location, wtk_float32_t v0);
typedef void (GL_ENTRY_POINT *GLUNIFORM2FPROC)(wtk_uint32_t location, wtk_float32_t v0, wtk_float32_t v1);
typedef void (GL_ENTRY_POINT *GLUNIFORM3FPROC)(wtk_uint32_t location, wtk_float32_t v0, wtk_float32_t v1, wtk_float32_t v2);
typedef void (GL_ENTRY_POINT *GLUNIFORM4FPROC)(wtk_uint32_t location, wtk_float32_t v0, wtk_float32_t v1, wtk_float32_t v2, wtk_float32_t v3);

typedef void (GL_ENTRY_POINT *GLUNIFORM1IPROC)(wtk_uint32_t location, wtk_uint32_t v0);
typedef void (GL_ENTRY_POINT *GLUNIFORM2IPROC)(wtk_uint32_t location, wtk_int32_t v0, wtk_int32_t v1);
typedef void (GL_ENTRY_POINT *GLUNIFORM3IPROC)(wtk_uint32_t location, wtk_int32_t v0, wtk_int32_t v1, wtk_int32_t v2);
typedef void (GL_ENTRY_POINT *GLUNIFORM4IPROC)(wtk_uint32_t location, wtk_int32_t v0, wtk_int32_t v1, wtk_int32_t v2, wtk_int32_t v3);

typedef void (GL_ENTRY_POINT *GLUNIFORM1UIPROC)(wtk_uint32_t location, wtk_uint32_t v0);
typedef void (GL_ENTRY_POINT *GLUNIFORM2UIPROC)(wtk_uint32_t location, wtk_uint32_t v0, wtk_uint32_t v1);
typedef void (GL_ENTRY_POINT *GLUNIFORM3UIPROC)(wtk_uint32_t location, wtk_uint32_t v0, wtk_uint32_t v1, wtk_uint32_t v2);
typedef void (GL_ENTRY_POINT *GLUNIFORM4UIPROC)(wtk_uint32_t location, wtk_uint32_t v0, wtk_uint32_t v1, wtk_uint32_t v2, wtk_uint32_t v3);

extern GLUNIFORM1FPROC glUniform1f;
extern GLUNIFORM2FPROC glUniform2f;
extern GLUNIFORM3FPROC glUniform3f;
extern GLUNIFORM4FPROC glUniform4f;

extern GLUNIFORM1IPROC glUniform1i;
extern GLUNIFORM2IPROC glUniform2i;
extern GLUNIFORM3IPROC glUniform3i;
extern GLUNIFORM4IPROC glUniform4i;

extern GLUNIFORM1UIPROC glUniform1ui;
extern GLUNIFORM2UIPROC glUniform2ui;
extern GLUNIFORM3UIPROC glUniform3ui;
extern GLUNIFORM4UIPROC glUniform4ui;

typedef void (GL_ENTRY_POINT *GLUSEPROGRAMPROC)(wtk_uint32_t program);

extern GLUSEPROGRAMPROC glUseProgram;

typedef void (GL_ENTRY_POINT *GLENABLEVERTEXATTRIBARRAYPROC)(wtk_uint32_t index);
typedef void (GL_ENTRY_POINT *GLDISABLEVERTEXATTRIBARRAYPROC)(wtk_uint32_t index);

extern GLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
extern GLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;

typedef void (GL_ENTRY_POINT *GLVERTEXATTRIBPOINTERPROC)(wtk_uint32_t index, wtk_uint32_t size, wtk_uint32_t type, wtk_uint32_t normalized, wtk_uint32_t stride, const void *pointer);
typedef void (GL_ENTRY_POINT *GLVERTEXATTRIBIPOINTERPROC)(wtk_uint32_t index, wtk_uint32_t size, wtk_uint32_t type, wtk_uint32_t stride, const void *pointer);
typedef void (GL_ENTRY_POINT *GLVERTEXATTRIBDIVISORPROC)(wtk_uint32_t index, wtk_uint32_t divisor);

extern GLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
extern GLVERTEXATTRIBIPOINTERPROC glVertexAttribIPointer;

typedef void (GL_ENTRY_POINT *GLBINDFRAMEBUFFERPROC)(wtk_uint32_t target, wtk_uint32_t framebuffer);

extern GLBINDFRAMEBUFFERPROC glBindFramebuffer;

typedef void (GL_ENTRY_POINT *GLFRAMEBUFFERTEXTURE1DPROC)(wtk_uint32_t target,
                                                          wtk_uint32_t attachment,
                                                          wtk_uint32_t textarget,
                                                          wtk_uint32_t texture,
                                                          wtk_uint32_t level);

typedef void (GL_ENTRY_POINT *GLFRAMEBUFFERTEXTURE2DPROC)(wtk_uint32_t target,
                                                          wtk_uint32_t attachment,
                                                          wtk_uint32_t textarget,
                                                          wtk_uint32_t texture,
                                                          wtk_uint32_t level);

typedef void (GL_ENTRY_POINT *GLFRAMEBUFFERTEXTURE3DPROC)(wtk_uint32_t target,
                                                          wtk_uint32_t attachment,
                                                          wtk_uint32_t textarget,
                                                          wtk_uint32_t texture,
                                                          wtk_uint32_t level,
                                                          wtk_uint32_t layer);

extern GLFRAMEBUFFERTEXTURE1DPROC glFramebufferTexture1D;
extern GLFRAMEBUFFERTEXTURE2DPROC glFramebufferTexture2D;
extern GLFRAMEBUFFERTEXTURE3DPROC glFramebufferTexture3D;

typedef void (GL_ENTRY_POINT *GLDRAWBUFFERPROC)(wtk_uint32_t buffer);
typedef void (GL_ENTRY_POINT *GLDRAWBUFFERSPROC)(wtk_uint32_t n, const wtk_uint32_t *buffers);

extern GLDRAWBUFFERPROC glDrawBuffer;
extern GLDRAWBUFFERSPROC glDrawBuffers;

typedef void (GL_ENTRY_POINT *GLCLEARCOLORPROC)(wtk_float32_t r, wtk_float32_t g, wtk_float32_t b, wtk_float32_t a);
typedef void (GL_ENTRY_POINT *GLCLEARDEPTHPROC)(wtk_float64_t depth);
typedef void (GL_ENTRY_POINT *GLCLEARSTENCILPROC)(wtk_uint32_t stencil);

extern GLCLEARCOLORPROC glClearColor;
extern GLCLEARDEPTHPROC glClearDepth;
extern GLCLEARSTENCILPROC glClearStencil;

typedef void (GL_ENTRY_POINT *GLCLEARPROC)(wtk_uint32_t mask);

extern GLCLEARPROC glClear;

typedef void (GL_ENTRY_POINT *GLDRAWARRAYSPROC)(wtk_uint32_t mode, wtk_uint32_t first, wtk_uint32_t count);
typedef void (GL_ENTRY_POINT *GLDRAWELEMENTSPROC)(wtk_uint32_t mode, wtk_uint32_t count, wtk_uint32_t type, const void *indices);

extern GLDRAWARRAYSPROC glDrawArrays;
extern GLDRAWELEMENTSPROC glDrawElements;

typedef void (GL_ENTRY_POINT *GLBLITFRAMEBUFFERPROC)(wtk_int32_t src_x0,
                                                     wtk_int32_t src_y0,
                                                     wtk_int32_t src_x1,
                                                     wtk_int32_t src_y1,
                                                     wtk_int32_t dst_x0,
                                                     wtk_int32_t dst_y0,
                                                     wtk_int32_t dst_x1,
                                                     wtk_int32_t dst_y1,
                                                     wtk_uint32_t mask,
                                                     wtk_uint32_t filter);

extern GLBLITFRAMEBUFFERPROC glBlitFramebuffer;

typedef void (GL_ENTRY_POINT *GLFLUSHPROC)(void);
typedef void (GL_ENTRY_POINT *GLFINISHPROC)(void);

extern GLFLUSHPROC  glFlush;
extern GLFINISHPROC glFinish;

extern WTK_PRIVATE wtk_uint32_t GL_KHR_debug;
extern WTK_PRIVATE wtk_uint32_t GL_GREMEDY_frame_terminator;

/*
 * Management
 */

extern WTK_PRIVATE
  void wtk_ogl_init(void);

extern WTK_PRIVATE
  void wtk_ogl_shutdown(void);

typedef struct wtk_ogl_surface wtk_ogl_surface_t;

extern WTK_PRIVATE
  wtk_ogl_surface_t *wtk_ogl_create_surface(
    wtk_uintptr_t window);

extern WTK_PRIVATE
  void wtk_ogl_destroy_surface(
    wtk_ogl_surface_t *surface);

extern WTK_PRIVATE
  void wtk_ogl_resize_surface(
    wtk_ogl_surface_t *surface,
    wtk_uint32_t width,
    wtk_uint32_t height);

extern WTK_PRIVATE
  void wtk_ogl_dimensions_of_surface(
    const wtk_ogl_surface_t *surface,
    wtk_uint32_t *width,
    wtk_uint32_t *height);

extern WTK_PRIVATE
  void wtk_ogl_bind(
    wtk_ogl_surface_t *surface);

extern WTK_PRIVATE
  void wtk_ogl_present(
    wtk_ogl_surface_t *surface);

WTK_END_EXTERN_C

#endif /* _WTK_GL_H_ */
