/*===-- wtk/render.c ----------------------------------------*- mode: C -*-===*/
/*                                                                            */
/*                                     _   _                                  */
/*                               _ _ _| |_| |_                                */
/*                              | | | |  _| '_|                               */
/*                              |_____|_| |_,_|                               */
/*                                                                            */
/*       This file is distributed under the terms described in LICENSE.       */
/*                                                                            */
/*===----------------------------------------------------------------------===*/

#include "wtk/render.h"

/* For batches. */
#include "wtk/draw.h"

#include "wtk/gl.h"

WTK_BEGIN_EXTERN_C

typedef struct wtk_renderer {
  /*! Monotonically increasing count of frames rendered. */
  wtk_uint32_t frames;

  /* Simple shader for rendering a bunch of `wtk_vertex_t`. */
  wtk_uint32_t program;

  wtk_uint32_t batch_uniform_loc;
  wtk_uint32_t dimensions_uniform_loc;
  wtk_uint32_t debug_uniform_loc;

  /*! Allocations for lifetime of renderer. */
  wtk_block_t permanent;

  /*! Allocations for lifetime of a frame. */
  wtk_block_t transient;
} wtk_renderer_t;

static wtk_renderer_t *r = NULL;

/* Evenly distributed colors. Useful for debug visualization. */
static const wtk_uint32_t COLORS[32] = {
  0x7f7e3fff, 0x3faf7fff, 0x7f3f1dff, 0x097f3fff, 0x483f7fff, 0x7f5b3fff,
  0x3f7fedff, 0x7f3f40ff, 0x2b7f3fff, 0x3f9a7fff, 0x7f3f08ff, 0x3f7fcbff,
  0x5d3f7fff, 0x7f713fff, 0x3fbd7fff, 0x7f3f2bff, 0x167f3fff, 0x3f857fff,
  0x7f4e3fff, 0x3f7fe0ff, 0x723f7fff, 0x387f3fff, 0x3fa77fff, 0x7f3f15ff,
  0x017f3fff, 0x503f7fff, 0x7f633fff, 0x3f7ff5ff, 0x7f3f38ff, 0x237f3fff,
  0x3f927fff, 0x7f413fff
};

static const char *VERTEX_SHADER_SOURCE =
  "#version 140                                                           \n" \
  "                                                                       \n" \
  "#extension GL_ARB_explicit_attrib_location : enable                    \n" \
  "                                                                       \n" \
  "// Toggles visualization of primitives.                                \n" \
  "uniform bool debug;                                                    \n" \
  "                                                                       \n" \
  "// Globally unique identifier assigned to batch.                       \n" \
  "uniform uint batch;                                                    \n" \
  "                                                                       \n" \
  "// Canvas dimensions.                                                  \n" \
  "uniform uvec2 dimensions;                                              \n" \
  "                                                                       \n" \
  "// Input.                                                              \n" \
  "layout(location = 0) in vec2 vs_position;                              \n" \
  "layout(location = 1) in vec2 vs_uv;                                    \n" \
  "layout(location = 2) in vec4 vs_color;                                 \n" \
  "layout(location = 3) in uint vs_texture;                               \n" \
  "                                                                       \n" \
  "// Output.                                                             \n" \
  "out vec2 fs_uv;                                                        \n" \
  "out vec4 fs_color;                                                     \n" \
  "flat out uint fs_texture;                                              \n" \
  "                                                                       \n" \
  "const vec3 colors[32] = vec3[](                                        \n" \
  "  vec3(0.800f, 0.400f, 0.722f), vec3(0.192f, 0.800f, 0.400f),          \n" \
  "  vec3(0.400f, 0.282f, 0.800f), vec3(0.800f, 0.435f, 0.400f),          \n" \
  "  vec3(0.400f, 0.800f, 0.349f), vec3(0.263f, 0.400f, 0.800f),          \n" \
  "  vec3(0.800f, 0.788f, 0.400f), vec3(0.400f, 0.498f, 0.800f),          \n" \
  "  vec3(0.800f, 0.400f, 0.588f), vec3(0.059f, 0.800f, 0.400f),          \n" \
  "  vec3(0.047f, 0.400f, 0.800f), vec3(0.800f, 0.573f, 0.400f),          \n" \
  "  vec3(0.400f, 0.800f, 0.482f), vec3(0.800f, 0.400f, 0.804f),          \n" \
  "  vec3(0.275f, 0.800f, 0.400f), vec3(0.400f, 0.365f, 0.800f),          \n" \
  "  vec3(0.800f, 0.400f, 0.455f), vec3(0.400f, 0.800f, 0.267f),          \n" \
  "  vec3(0.180f, 0.400f, 0.800f), vec3(0.800f, 0.706f, 0.400f),          \n" \
  "  vec3(0.400f, 0.584f, 0.800f), vec3(0.800f, 0.400f, 0.671f),          \n" \
  "  vec3(0.141f, 0.800f, 0.400f), vec3(0.400f, 0.231f, 0.800f),          \n" \
  "  vec3(0.800f, 0.486f, 0.400f), vec3(0.400f, 0.800f, 0.400f),          \n" \
  "  vec3(0.314f, 0.400f, 0.800f), vec3(0.357f, 0.800f, 0.400f),          \n" \
  "  vec3(0.400f, 0.447f, 0.800f), vec3(0.800f, 0.400f, 0.537f),          \n" \
  "  vec3(0.008f, 0.800f, 0.400f), vec3(0.098f, 0.400f, 0.800f)           \n" \
  ");                                                                     \n" \
  "                                                                       \n" \
  "void main() {                                                          \n" \
  "  vec2 position = vs_position / vec2(dimensions);                      \n" \
  "                                                                       \n" \
  "  // Origin is upper left, but OpenGL uses lower left convention.      \n" \
  "  position.y = 1.0f - position.y;                                      \n" \
  "                                                                       \n" \
  "  // Map to normalized device coordinates.                             \n" \
  "  gl_Position = vec4(position * 2.0f - 1.0f, 0.5f, 1.0f);              \n" \
  "                                                                       \n" \
  "  if (debug) {                                                         \n" \
  "    // Assign a color per triangle.                                    \n" \
  "    fs_uv = vec2(0.0f, 0.0f);                                          \n" \
  "    fs_color = vec4(colors[(gl_VertexID / 3) % 32], 1.0f);             \n" \
  "    fs_texture = 0u;                                                   \n" \
  "  } else {                                                             \n" \
  "    fs_uv = vs_uv;                                                     \n" \
  "    fs_color = vs_color;                                               \n" \
  "    fs_texture = vs_texture;                                           \n" \
  "  }                                                                    \n" \
  "}";

static const char *FRAGMENT_SHADER_SOURCE =
  "#version 140                                                           \n" \
  "                                                                       \n" \
  "#extension GL_ARB_explicit_attrib_location : enable                    \n" \
  "                                                                       \n" \
  "// Toggles visualization of primitives.                                \n" \
  "uniform bool debug;                                                    \n" \
  "                                                                       \n" \
  "// Globally unique identifier assigned to batch.                       \n" \
  "uniform uint batch;                                                    \n" \
  "                                                                       \n" \
  "// Canvas dimensions.                                                  \n" \
  "uniform uvec2 dimensions;                                              \n" \
  "                                                                       \n" \
  "#if 0                                                                  \n" \
  "uniform sampler2D textures[8];                                         \n" \
  "#endif                                                                 \n" \
  "                                                                       \n" \
  "// Input.                                                              \n" \
  "in vec2 fs_uv;                                                         \n" \
  "in vec4 fs_color;                                                      \n" \
  "in uint fs_texture;                                                    \n" \
  "                                                                       \n" \
  "// Output.                                                             \n" \
  "layout(location = 0) out vec4 gl_FragColor;                            \n" \
  "                                                                       \n" \
  "void main() {                                                          \n" \
  "  vec4 base = vec4(1.0f, 1.0f, 1.0f, 1.0f);                            \n" \
  "                                                                       \n" \
  "#if 0                                                                  \n" \
  "  /* Non-uniform control flow. Can't rely on mipmaps? */               \n" \
  "  if (texture != 0)                                                    \n" \
  "    base = texture(textures[fs_texture],                               \n" \
  "                   vec2(fs_uv.x, 1.0f - fs_uv));                       \n" \
  "#endif                                                                 \n" \
  "                                                                       \n" \
  "  gl_FragColor = base * fs_color;                                      \n" \
  "};";

void wtk_renderer_init(void)
{
  r = (wtk_renderer_t *)wtk_allocate_s(sizeof(wtk_renderer_t), 16);

  r->frames = 0;

  r->permanent.base   = (wtk_uintptr_t)wtk_allocate_s(65535, 16);
  r->permanent.offset = 0;
  r->permanent.size   = 65535;

  r->transient.base   = (wtk_uintptr_t)wtk_allocate_s(65535, 16);
  r->transient.offset = 0;
  r->transient.size   = 65535;

  wtk_ogl_init();

  r->program = glCreateProgram(); {
    wtk_uint32_t vs = glCreateShader(GL_VERTEX_SHADER),
                 fs = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vs, 1, &VERTEX_SHADER_SOURCE, NULL);
    glShaderSource(fs, 1, &FRAGMENT_SHADER_SOURCE, NULL);

    glCompileShader(vs);
    glCompileShader(fs);

    wtk_int32_t vs_compiled_successfully;
    wtk_int32_t fs_compiled_successfully;

    const char *vs_compile_log = NULL;
    const char *fs_compile_log = NULL;

    glGetShaderiv(vs, GL_COMPILE_STATUS, &vs_compiled_successfully);
    glGetShaderiv(fs, GL_COMPILE_STATUS, &fs_compiled_successfully);

    if (!vs_compiled_successfully) {
      wtk_int32_t length;
      glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &length);

      char *log = (char *)wtk_block_allocate_s(&r->transient, length + 1);
      glGetShaderInfoLog(vs, length, NULL, log);

      vs_compile_log = (const char *)log;
    }

    if (!fs_compiled_successfully) {
      wtk_int32_t length;
      glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &length);

      char *log = (char *)wtk_block_allocate_s(&r->transient, length + 1);
      glGetShaderInfoLog(fs, length, NULL, log);

      fs_compile_log = (const char *)log;
    }

    wtk_assert_release(vs_compiled_successfully && fs_compiled_successfully);

    glAttachShader(r->program, vs);
    glAttachShader(r->program, fs);

    glLinkProgram(r->program);

    wtk_int32_t program_linked_successfully;
    const char *program_link_log = NULL;

    glGetProgramiv(r->program, GL_LINK_STATUS, &program_linked_successfully);

    if (!program_linked_successfully) {
      wtk_int32_t length;
      glGetProgramiv(r->program, GL_INFO_LOG_LENGTH, &length);

      char *log = (char *)wtk_block_allocate_s(&r->transient, length + 1);
      glGetProgramInfoLog(r->program, length, NULL, log);

      program_link_log = (const char *)log;
    }

    wtk_assert_debug(program_linked_successfully);

    glDetachShader(r->program, vs);
    glDetachShader(r->program, fs);

    glDeleteShader(vs);
    glDeleteShader(fs);

    glUseProgram(r->program);
    glUseProgram(0);
  }

  r->batch_uniform_loc = glGetUniformLocation(r->program, "batch");
  r->dimensions_uniform_loc = glGetUniformLocation(r->program, "dimensions");
  r->debug_uniform_loc = glGetUniformLocation(r->program, "debug");

#if 0
  glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &r->textures);

  if (r->textures > 8)
    /* Hard-limit to 8. Shouldn't need more because we use atlases. */
    r->textures = 8;

  /* HACK(mtwilliams): Limit batches to one texture to reduce impact of lookup
   * for each primitive, until a cheap (branchless?) lookup is implemented. */
  r->textures = 1;
#endif
}

void wtk_renderer_shutdown(void)
{
  glDeleteProgram(r->program);

  wtk_ogl_shutdown();

  wtk_free((void *)r->permanent.base);
  wtk_free((void *)r->transient.base);

  wtk_free((void *)r);

  r = NULL;
}

void wtk_renderer_begin(void)
{
  /* Blow away allocations from previous frame. */
  wtk_block_reset(&r->transient);
}

void wtk_renderer_end(void)
{
  r->frames += 1;
}

void wtk_renderer_render(const wtk_canvas_t *canvas)
{
  wtk_renderer_begin();

  glEnable(GL_SCISSOR_TEST);

  glEnable(GL_BLEND);

  glEnable(GL_CULL_FACE);
  glFrontFace(GL_CW);
  glCullFace(GL_BACK);

  glViewport(0, 0, canvas->width, canvas->height);
  glScissor(0, 0, canvas->width, canvas->height);

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glUseProgram(r->program);

  /* Debug visualization is done by our shader. */
  glUniform1ui(r->debug_uniform_loc, 0);

  /* TODO(mtwilliams): Use rectangle texture? */
  glUniform2ui(r->dimensions_uniform_loc, canvas->width, canvas->height);

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);

#if 0
  glEnableVertexAttribArray(3);
#endif

  /* Submit all batches. */
  for (const wtk_batch_t *batch = canvas->batches; batch; batch = batch->next) {
    glUniform1ui(r->batch_uniform_loc, batch->id);

    glScissor(batch->clip.x,
              canvas->height - (batch->clip.h + batch->clip.y),
              batch->clip.w,
              batch->clip.h);

  #if 0
    for (unsigned slot = 0; slot < r->textures; ++slot) {
      glActiveTexture(GL_TEXTURE_0 + slot);
      glBindTexture(GL_TEXTURE_2D, batch->textures[slot] ? batch->textures[slot]->id : 0);
    }
  #endif

    wtk_uint32_t buffer;

    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, batch->count * sizeof(wtk_vertex_t), &batch->verticies[0], GL_STREAM_DRAW);

    glVertexAttribPointer(0, 2, GL_UNSIGNED_SHORT, GL_FALSE, sizeof(wtk_vertex_t), (const void *)offsetof(wtk_vertex_t, x));
    glVertexAttribPointer(1, 2, GL_UNSIGNED_SHORT, GL_TRUE, sizeof(wtk_vertex_t), (const void *)offsetof(wtk_vertex_t, u));
    glVertexAttribPointer(2, GL_BGRA, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(wtk_vertex_t), (const void *)offsetof(wtk_vertex_t, color));

  #if 0
    glVertexAttribIPointer(4, 1, GL_UNSIGNED_BYTE, sizeof(wtk_vertex_t), (const void *)offsetof(wtk_vertex_t, texture));
  #endif

    glDrawArrays(GL_TRIANGLES, 0, batch->count);

    glDeleteBuffers(1, &buffer);
  }

  wtk_renderer_end();
}

WTK_END_EXTERN_C
