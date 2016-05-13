#include "client/game.h"

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

	g.cam = entityCameraNew();
	g.cam.position = (Vec3){0.f, 1.f, 0.f};
	g.cam.target = (Vec3){0.f, 1.f, -1.f};

	g.moto = entityNew(renderMeshLoad("res/models/cube.obj"));
	g.room = entityRoomNew(50.f, 15.f);

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
	}
}

void gameMouseMoved(Game* g, float x, float y) {
	g->mousePrev = g->mouse;
	g->mouse.x = x;
	g->mouse.y = y;
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
	}
}

void gameUpdate(Game* g, double dt) {
	float dx = 0.f;
	float dz = 0.f;

	if(g->forward) {
		dz = -3.f * dt;
	}
	else if(g->backward) {
		dz = 3.f * dt;
	}

	if(g->left) {
		dx = -3.f * dt;
	}
	else if(g->right) {
		dx = 3.f * dt;
	}

	g->cam.position.x += dx;
	g->cam.position.z += dz;
	g->cam.target.x += dx;
	g->cam.target.z += dz;

	//g->cam.target = mathVec3Norm(mathVec3SubV(g->cam.position, g->cam.target));

	// TODO: Fix mouse-based camera rotation
	/*Vec2 mouseDelta = mathVec2SubV(g->mouse, g->mousePrev);
	Vec4 t = mathMat4MulV(mathMat4RotationV(mouseDelta.x / 2.f, (Vec3){0.f, 1.f, 0.f}), (Vec4){g->cam.target.x, g->cam.target.y, g->cam.target.z, 0.f});

	g->cam.target.x = t.x;
	g->cam.target.y = t.y;
	g->cam.target.z = t.z;*/
}

void gameRender(Game* g) {
	renderClear();
	renderShaderBind(&g->shader);

	Mat4 identity = mathMat4Identity();
	renderShaderSetModel(&g->shader, &identity);
	entityCameraUse(&g->cam, &g->shader);

	renderMeshDraw(&g->shader, &g->room.groundMesh, g->room.groundTex);
	renderMeshDraw(&g->shader, &g->room.wallsMesh, g->room.wallsTex);

	/*renderShaderSetTransform(&g->shader, g->moto.transform);
	renderMeshDraw(&g->shader, &g->moto.mesh, 0);*/
}
