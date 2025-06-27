#include <stdio.h>
#include <stdbool.h>
#include <GL/gl.h>  // OpenGL
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include "global.h"
#include "time/time.h"

int main(){
    time_init(60);
    SDL_Window *window = render_init();

    bool should_quit = false;

    while (!should_quit) {
        time_update();
        
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                should_quit = true;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    input_toggle_mouse_capture();
                }
                break;
            default:
                break;
            }
        }

        input_update();
            
        render_begin();
        vec3 position = {0.0f, 0.0f, 0.0f};
        vec3 size = {1.0f, 1.0f, 1.0f};
        vec3 rotation = {global.time.now / 1000.0f, 0.0f, 0.0f}; // Rotates over time
        // vec3 rotation = {0.0f, 0.0f, 0.0f}; // Rotates over time
        vec4 color = {1.0f, 0.5f, 0.2f, 1.0f};
        render_quad(position, size, rotation, color);
        vec3 new_position = {5.0f, 5.0f, 5.0f};
        render_quad(new_position, size, rotation, color);
        render_end(window);

        time_update_late();
    }

    return 0;
}
