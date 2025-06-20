#pragma once

#include "render/render.h"
#include "util/types.h"
#include "time/time.h"
#include "input/input.h"

typedef struct global {
	Input_State input;
	Time_State time;
	Camera camera;
} Global;

extern Global global;
