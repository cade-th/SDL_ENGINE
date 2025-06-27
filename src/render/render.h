#pragma once

#include <SDL2/SDL.h>
#include "../linmath.h"

#include "../util/types.h"

typedef struct {
	vec3 position;
	f32 yaw;
	f32 pitch;
	f32 roll;

	f32 fov;
	f32 aspect_ratio;
	f32 nearplane;
	f32 farplane;

	mat4x4 projection;
	mat4x4 view;
} Camera;

typedef struct {} batch_vertex;

SDL_Window *render_init(void);
void render_begin(void);
void render_end(SDL_Window *window);
void render_quad(vec3 pos, vec3 size, vec3 rotation, vec4 color);
// call in render_end()
void render_batch(batch_vertex *vertices, u32 count);
