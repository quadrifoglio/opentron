#pragma once

#include <stdbool.h>

#include "client/render.h"
#include "client/entity.h"

#define KEY_FWD 87
#define KEY_BWD 83
#define KEY_LFT 65
#define KEY_RGT 68
#define KEY_UP 265
#define KEY_DOWN 264

typedef struct {
	bool forward, backward, left, right;
	Vec2 mousePrev, mouse;

	int width, height;
	Shader shader;

	Texture whiteTex;
	Texture wallsTex;
	Texture motoWallTex;

	Mesh cubeMesh;
	Camera cam;

	Room room;
	Entity moto;

	Player player;
	WallGroup walls;
} Game;

Game gameInit(int width, int height);

void gameMouseMoved(Game* g, float x, float y);
void gameKeyPressed(Game* g, int key);
void gameKeyReleased(Game* g, int key);
void gameUpdate(Game* g, double dt);
void gameRender(Game* g);
