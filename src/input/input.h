#pragma once
#include "../util/types.h"
#include <stdbool.h>

typedef enum input_key {
	INPUT_KEY_ESCAPE,
	INPUT_KEY_W,
	INPUT_KEY_A,
	INPUT_KEY_D,
	INPUT_KEY_S,
	INPUT_KEY_SPACE,
	INPUT_KEY_SHIFT
} Input_Key;

typedef enum key_state {
	KS_UNPRESSED,
	KS_PRESSED,
	KS_HELD,
} Key_State;

typedef struct input_state {
	Key_State escape;
	Key_State w;
	Key_State a;
	Key_State d;
	Key_State s;
	Key_State space;
	Key_State shift;
	
	// Mouse input
	f32 mouse_x;
	f32 mouse_y;
	f32 mouse_delta_x;
	f32 mouse_delta_y;
	bool mouse_captured;
} Input_State;

void input_update(void);
void input_toggle_mouse_capture(void);
