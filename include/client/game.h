#pragma once

#include "client/render.h"
#include "client/entity.h"

#define KEY_FWD 87
#define KEY_BWD 83
#define KEY_LFT 65
#define KEY_RGT 68

typedef struct {
	int width, height;
	Shader shader;

	Mesh cubeMesh;
	Camera cam;

	Room room;
	Entity moto;
} Game;

Game gameInit(int width, int height);

void gameKeyPressed(Game* g, int key);
void gameKeyReleased(Game* g, int key);
void gameUpdate(Game* g, double dt);
void gameRender(Game* g);
