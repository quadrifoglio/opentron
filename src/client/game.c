#include "client/game.h"

#include <stdlib.h>

Game gameInit(int width, int height) {
	Game g = {0};
	g.width = width;
	g.height = height;

	renderInit();
	g.shader = renderShaderLoad("res/shaders/basic.vertex", "res/shaders/basic.fragment");

	Mat4 identity = mathMat4Identity();
	Mat4 proj = mathMat4Perspective(60.f, (float)width / (float)height, 0.1f, 51.f);

	renderShaderSetModel(&g.shader, &identity);
	renderShaderSetView(&g.shader, &identity);
	renderShaderSetProj(&g.shader, &proj);

	g.textures.white = renderTextureWhite();
	g.textures.ground = renderTextureLoad("res/textures/ground.png");
	g.textures.roomWalls = renderTextureLoad("res/textures/walls.png");
	g.textures.playerWall = renderTextureLoad("res/textures/wall.png");

	g.room = entityRoomNew(50.f, 20.f);

	g.cam = entityCameraNew();
	g.cam.position = (Vec3){0.f, 1.f, 20.f};
	g.cam.target = (Vec3){0.f, 1.f, -1.f};

	g.player = entityPlayerNew((Vec3){0.5f, 0.3f, 0.5f});

	g.walls.xWallCount = 1;
	g.walls.zWallCount = 1;
	g.walls.xWalls = malloc(sizeof(Wall));
	g.walls.zWalls = malloc(sizeof(Wall));
	g.walls.xWalls[0] = entityWallNew((Vec3){-25.f, 0.f, -5.f}, (Vec3){25.f, 0.f, -5.f});
	g.walls.zWalls[0] = entityWallNew((Vec3){-5.f, 0.f, 25.f}, (Vec3){-5.f, 0.f, -25.f});

	return g;
}

void gameMouseMoved(Game* g, float x, float y) {
	g->input.mousePrev = g->input.mouse;
	g->input.mouse.x = x;
	g->input.mouse.y = y;

	Vec2 mouseDelta = mathVec2SubV(g->input.mouse, g->input.mousePrev);
	Vec4 t = mathMat4MulV(mathMat4RotationV(mouseDelta.x / 4.f, (Vec3){0.f, 1.f, 0.f}), (Vec4){g->cam.target.x, g->cam.target.y, g->cam.target.z, 0.f});

	g->cam.target.x = t.x;
	g->cam.target.y = t.y;
	g->cam.target.z = t.z;
}

void gameKeyPressed(Game* g, int key) {
	switch(key) {
		case KEY_FWD:
			g->input.forward = 1;
			break;
		case KEY_BWD:
			g->input.backward = 1;
			break;
		case KEY_LFT:
			g->input.left = 1;
			break;
		case KEY_RGT:
			g->input.right = 1;
			break;
	}

	entityPlayerKeyPressed(&g->player, key);
}

void gameKeyReleased(Game* g, int key) {
	switch(key) {
		case KEY_FWD:
			g->input.forward = 0;
			break;
		case KEY_BWD:
			g->input.backward = 0;
			break;
		case KEY_LFT:
			g->input.left = 0;
			break;
		case KEY_RGT:
			g->input.right = 0;
			break;
	}
}

void gameUpdate(Game* g, double dt) {
	float dx = 0.f;
	float dz = 0.f;

	if(g->input.forward) {
		dz = -3.f * dt;
	}
	else if(g->input.backward) {
		dz = 3.f * dt;
	}

	if(g->input.left) {
		dx = -3.f * dt;
	}
	else if(g->input.right) {
		dx = 3.f * dt;
	}

	/*g->cam.position.x += dx;
	g->cam.position.z += dz;
	g->cam.target.x += dx;
	g->cam.target.z += dz;*/

	entityPlayerUpdate(dt, &g->player, &g->room, &g->walls);

	g->cam.position.x = g->player.pos.x - (3.f * g->player.dir.x);
	g->cam.position.y = 1.5f;
	g->cam.position.z = g->player.pos.z - (3.f * g->player.dir.z);

	g->cam.target.x = g->player.pos.x;
	g->cam.target.z = g->player.pos.z;
}

void gameRender(Game* g) {
	renderClear();
	renderShaderBind(&g->shader);

	Mat4 identity = mathMat4Identity();
	renderShaderSetModel(&g->shader, &identity);
	entityCameraUse(&g->cam, &g->shader);

	entityRoomRender(&g->shader, &g->room, &g->textures);

	renderShaderSetTransform(&g->shader, g->player.e.tr);
	renderMeshDraw(&g->shader, &g->player.e.mesh, g->textures.white);

	for(int i = 0; i < g->walls.xWallCount; ++i) {
		entityWallRender(&g->shader, &g->walls.xWalls[i], g->textures.playerWall);
	}

	for(int i = 0; i < g->walls.zWallCount; ++i) {
		entityWallRender(&g->shader, &g->walls.zWalls[i], g->textures.playerWall);
	}
}
