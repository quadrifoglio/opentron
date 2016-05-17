#pragma once

#include <stdbool.h>

#include "client/render.h"

#define KEY_FWD 87
#define KEY_BWD 83
#define KEY_LFT 65
#define KEY_RGT 68
#define KEY_UP 265
#define KEY_DOWN 264

typedef struct {
	Texture white;
	Texture ground;
	Texture roomWalls;
	Texture playerWall;
} TextureGroup;

typedef struct {
	bool forward, backward, left, right;
	Vec2 mousePrev, mouse;
} Input;

