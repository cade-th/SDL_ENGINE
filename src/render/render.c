#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "render.h"
#include "render_internal.h"
#include "../global.h"

static u32 vao_quad;
static u32 vbo_quad;
static u32 ebo_quad;
static u32 shader_default;
static u32 texture_color;
static f32 window_width = 800;
static f32 window_height = 600;
static f32 render_width = 800;
static f32 render_height = 600;

static void camera_init() {
    global.camera.fov = 45.0f * (3.14159 / 180.0f);
    global.camera.aspect_ratio = render_width / render_height;
    global.camera.nearplane = 0.1f;
    global.camera.farplane = 100.0f;
    
    // Initialize camera position and rotation
    global.camera.position[0] = 0.0f;
    global.camera.position[1] = 0.0f;
    global.camera.position[2] = 3.0f;
    global.camera.yaw = 0.0f;
    global.camera.pitch = 0.0f;
    global.camera.roll = 0.0f;
}

SDL_Window *render_init(void) {
    SDL_Window *render_window = render_init_window(window_width, window_height);

    camera_init();
    render_init_quad(&vao_quad, &vbo_quad, &ebo_quad);
    render_init_shaders(&shader_default, render_width, render_height);
    render_init_color_texture(&texture_color);

    return render_window;
    
}

void render_begin(void) {
    glClearColor(0.08f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Calculate camera direction vectors
    vec3 forward = {
        sinf(global.camera.yaw) * cosf(global.camera.pitch),
        sinf(global.camera.pitch),
        cosf(global.camera.yaw) * cosf(global.camera.pitch)
    };
    
    vec3 right = {
        cosf(global.camera.yaw),
        0.0f,
        -sinf(global.camera.yaw)
    };
    
    vec3 up = {
        -sinf(global.camera.yaw) * sinf(global.camera.pitch),
        cosf(global.camera.pitch),
        -cosf(global.camera.yaw) * sinf(global.camera.pitch)
    };
    
    // Calculate look-at target (where camera is looking)
    vec3 target = {
        global.camera.position[0] + forward[0],
        global.camera.position[1] + forward[1],
        global.camera.position[2] + forward[2]
    };
    
    // Create view matrix using camera position and target
    mat4x4_look_at(global.camera.view, global.camera.position, target, (vec3){0.0f, 1.0f, 0.0f});
    
    mat4x4_perspective(global.camera.projection, global.camera.fov, global.camera.aspect_ratio, global.camera.nearplane, global.camera.farplane);
    glUseProgram(shader_default);
    glUniformMatrix4fv(glGetUniformLocation(shader_default, "projection"), 1, GL_FALSE, &global.camera.projection[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(shader_default, "view"), 1, GL_FALSE, &global.camera.view[0][0]);
}


void render_end(SDL_Window *window) {
    SDL_GL_SwapWindow(window);
}

void render_quad(vec3 pos, vec3 size, vec3 rotation, vec4 color) {
    mat4x4 model;
    mat4x4_identity(model);

    mat4x4_translate(model, pos[0], pos[1], pos[2]);

    mat4x4 temp;
    mat4x4_rotate_X(temp, model, rotation[0]);
    mat4x4_rotate_Y(model, temp, rotation[1]);
    mat4x4_rotate_Z(temp, model, rotation[2]);
    mat4x4_scale_aniso(model, temp, size[0], size[1], size[2]);

    glUniformMatrix4fv(glGetUniformLocation(shader_default, "model"), 1, GL_FALSE, &model[0][0]);
    glUniform4fv(glGetUniformLocation(shader_default, "color"), 1, color); 
    glBindVertexArray(vao_quad);
    glBindTexture(GL_TEXTURE_2D, texture_color);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
    glBindVertexArray(0);
}

