#include "time.h"
#include "../global.h"

void time_init(u32 frame_rate) {
    global.time.frame_rate = frame_rate;
    global.time.frame_delay = 1000.f / frame_rate;
    global.time.now = (f32)SDL_GetTicks();
    global.time.last = global.time.now;
    global.time.frame_last = global.time.now;
    global.time.last_tick_time = 0.0f;
}

void time_update(void) {
    global.time.now = (f32)SDL_GetTicks();
    global.time.delta = (global.time.now - global.time.last) / 1000.f;
    global.time.last = global.time.now;
    ++global.time.frame_count;

    if (global.time.now - global.time.frame_last >= 1000.f) {
        global.time.frame_rate = global.time.frame_count;
        global.time.frame_count = 0;
        global.time.frame_last = global.time.now;
    }

    
    // Print "tick" every second
    if (global.time.now - global.time.last_tick_time >= 1000.0f) {
        printf("tick\n");
        global.time.last_tick_time = global.time.now;
    }
}

void time_update_late(void) {
    global.time.frame_time = (f32)SDL_GetTicks() - global.time.now;

    if (global.time.frame_delay > global.time.frame_time) {
        SDL_Delay(global.time.frame_delay - global.time.frame_time);
    }
}
