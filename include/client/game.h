#pragma once

#include "client/global.h"
#include "client/entity.h"

typedef struct {
	int width, height;
	Shader shader;

	Input input;
	TextureGroup textures;

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
