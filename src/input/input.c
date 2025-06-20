#include "input.h"
#include "../global.h"
#include "../util/types.h"
#include <SDL2/SDL.h>

static void update_key_state(u8 current_state, Key_State *key_state) {
    if (current_state) {
        if (*key_state == KS_UNPRESSED)
            *key_state = KS_PRESSED;
        else if (*key_state == KS_PRESSED)
            *key_state = KS_HELD;
    } else {
        *key_state = KS_UNPRESSED;
    }
}

void input_toggle_mouse_capture(void) {
    global.input.mouse_captured = !global.input.mouse_captured;
    if (global.input.mouse_captured) {
        SDL_SetRelativeMouseMode(SDL_TRUE);
        SDL_ShowCursor(SDL_DISABLE);
    } else {
        SDL_SetRelativeMouseMode(SDL_FALSE);
        SDL_ShowCursor(SDL_ENABLE);
    }
}

void input_update() {
    const u8 *keyboard_state = SDL_GetKeyboardState(NULL);

    update_key_state(keyboard_state[SDL_SCANCODE_ESCAPE], &global.input.escape);
    update_key_state(keyboard_state[SDL_SCANCODE_W], &global.input.w);
    update_key_state(keyboard_state[SDL_SCANCODE_A], &global.input.a);
    update_key_state(keyboard_state[SDL_SCANCODE_D], &global.input.d);
    update_key_state(keyboard_state[SDL_SCANCODE_S], &global.input.s);
    update_key_state(keyboard_state[SDL_SCANCODE_SPACE], &global.input.space);
    update_key_state(keyboard_state[SDL_SCANCODE_LSHIFT], &global.input.shift);

    // Handle mouse movement for camera control
    if (global.input.mouse_captured) {
        int mouse_x, mouse_y;
        SDL_GetRelativeMouseState(&mouse_x, &mouse_y);
        
        global.input.mouse_delta_x = (f32)mouse_x;
        global.input.mouse_delta_y = (f32)mouse_y;
        
        // Update camera rotation based on mouse movement
        f32 mouse_sensitivity = 0.002f; // Adjust this for faster/slower mouse movement
        global.camera.yaw -= global.input.mouse_delta_x * mouse_sensitivity;
        global.camera.pitch -= global.input.mouse_delta_y * mouse_sensitivity; // Inverted for natural feel
        
        // Clamp pitch to prevent over-rotation
        if (global.camera.pitch > 1.5708f) global.camera.pitch = 1.5708f;  // 90 degrees
        if (global.camera.pitch < -1.5708f) global.camera.pitch = -1.5708f; // -90 degrees
    } else {
        global.input.mouse_delta_x = 0.0f;
        global.input.mouse_delta_y = 0.0f;
    }

    // Handle camera movement (WASD + Space/Shift)
    f32 move_speed = 5.0f * global.time.delta; // 5 units per second
    
    // Calculate forward and right vectors based on camera rotation
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
    
    // Horizontal movement (WASD)
    if (global.input.w == KS_HELD || global.input.w == KS_PRESSED) {
        global.camera.position[0] += forward[0] * move_speed;
        global.camera.position[1] += forward[1] * move_speed;
        global.camera.position[2] += forward[2] * move_speed;
    }
    if (global.input.s == KS_HELD || global.input.s == KS_PRESSED) {
        global.camera.position[0] -= forward[0] * move_speed;
        global.camera.position[1] -= forward[1] * move_speed;
        global.camera.position[2] -= forward[2] * move_speed;
    }
    if (global.input.a == KS_HELD || global.input.a == KS_PRESSED) {
        global.camera.position[0] += right[0] * move_speed;
        global.camera.position[2] += right[2] * move_speed;
    }
    if (global.input.d == KS_HELD || global.input.d == KS_PRESSED) {
        global.camera.position[0] -= right[0] * move_speed;
        global.camera.position[2] -= right[2] * move_speed;
    }
    
    // Vertical movement (Space/Shift)
    if (global.input.space == KS_HELD || global.input.space == KS_PRESSED) {
        global.camera.position[1] += move_speed; // Move up
    }
    if (global.input.shift == KS_HELD || global.input.shift == KS_PRESSED) {
        global.camera.position[1] -= move_speed; // Move down
    }
}
