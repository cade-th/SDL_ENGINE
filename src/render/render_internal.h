#pragma once

#include <SDL2/SDL.h>

#include "../util/types.h"
#include "render.h"

SDL_Window *render_init_window(u32 width, u32 height);
void render_init_quad(u32 *vao, u32 *vbo, u32 *ebo);
void render_init_color_texture(u32 *texture);
void render_init_shaders(u32 *shader_default, f32 render_width, f32 render_height);
u32 render_shader_create(const char *path_vert, const char *path_frag);

