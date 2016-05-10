#include "client/game.h"

Game gameInit(int width, int height) {
	Game g = {0};
	g.width = width;
	g.height = height;

	renderInit();
	g.shader = renderShaderLoad("res/shaders/basic.vertex", "res/shaders/basic.fragment");

	Mat4 identity = mathMat4Identity();
	Mat4 proj = mathMat4Perspective(60.f, width, height, 0.1f, 10.f);

	renderShaderSetModel(&g.shader, &identity);
	renderShaderSetView(&g.shader, &identity);
	renderShaderSetProj(&g.shader, &proj);

	g.cam = entityCameraNew();
	g.cam.position = (Vec3){0.f, 0.f, 0.0f};
	g.cam.target = (Vec3){0.f, 0.f, -1.f};

	g.moto = entityNew(renderMeshLoad("res/models/cube.obj"));
	g.moto.transform.translation.z = 10.f;
	g.moto.transform.rotation.x = 0.f;

	g.room = entityRoomNew(10.f);

	return g;
}

void gameKeyPressed(Game* g, int key) {
	switch(key) {
		case KEY_FWD:
			g->forward = 1;
			break;
		case KEY_BWD:
			g->backward = 1;
			break;
		case KEY_LFT:
			g->left = 1;
			break;
		case KEY_RGT:
			g->right = 1;
			break;
		case KEY_UP:
			g->up = 1;
			break;
		case KEY_DOWN:
			g->down = 1;
			break;
	}
}

void gameKeyReleased(Game* g, int key) {
	switch(key) {
		case KEY_FWD:
			g->forward = 0;
			break;
		case KEY_BWD:
			g->backward = 0;
			break;
		case KEY_LFT:
			g->left = 0;
			break;
		case KEY_RGT:
			g->right = 0;
			break;
		case KEY_UP:
			g->up = 0;
			break;
		case KEY_DOWN:
			g->down = 0;
			break;
	}
}

void gameUpdate(Game* g, double dt) {
	float dx = 0.f;
	float dy = 0.f;
	float dz = 0.f;

	if(g->forward) {
		dz = 3.f * dt;
	}
	else if(g->backward) {
		dz = -3.f * dt;
	}

	if(g->left) {
		dx = 3.f * dt;
	}
	else if(g->right) {
		dx = -3.f * dt;
	}

	if(g->up) {
		dy = 1.f * dt;
	}
	else if(g->down) {
		dy = -1.f * dt;
	}

	g->cam.position.x += dx;
	g->cam.position.y += dy;
	g->cam.position.z += dz;

	g->cam.target.x += dx;
	g->cam.target.y += dy;
}

void gameRender(Game* g) {
	renderClear();
	renderShaderBind(&g->shader);

	entityCameraUse(&g->cam, &g->shader);

	Mat4 identity = mathMat4Identity();
	renderShaderSetModel(&g->shader, &identity);
	renderMeshDraw(&g->shader, &g->room.mesh);

	entityDraw(&g->moto, &g->shader);
}
