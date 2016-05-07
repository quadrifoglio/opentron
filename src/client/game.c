#include "client/game.h"

Game gameInit(int width, int height) {
	Game g = {0};
	g.width = width;
	g.height = height;

	renderInit();
	g.shader = renderShaderLoad("res/shaders/basic.vertex", "res/shaders/basic.fragment");

	Mat4 identity = mathMat4Identity();
	Mat4 proj = mathMat4Perspective(70.f, width, height, 0.1f, 1000.f);

	renderShaderSetModel(&g.shader, &identity);
	renderShaderSetView(&g.shader, &identity);
	renderShaderSetProj(&g.shader, &proj);

	g.m = renderMeshLoad("res/models/cube.obj");
	g.t = mathTransform((Vec3){0.f, 0.f, 0.5f}, (Vec3){0.f, 0.f, 0.f}, (Vec3){0.5f, 0.5f, 0.5f});

	return g;
}

void gameKeyPressed(Game* g, int key) {

}

void gameKeyReleased(Game* g, int key) {

}

void gameUpdate(Game* g, double dt) {
	g->t.rotation.z += 0.01f * dt;
}

void gameRender(Game* g) {
	renderClear();
	renderShaderBind(&g->shader);

	Mat4 m = mathTransformMatrix(&g->t);
	renderShaderSetModel(&g->shader, &m);
	renderMeshDraw(&g->shader, &g->m);
}
