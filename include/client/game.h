#pragma once

#include "client/render.h"

typedef struct {
	int width, height;

	Shader shader;
	Mesh m;
	Transform t;
} Game;

Game gameInit(int width, int height);

void gameKeyPressed(Game* g, int key);
void gameKeyReleased(Game* g, int key);
void gameUpdate(Game* g, double dt);
void gameRender(Game* g);
