#include "client/game.h"

Game gameInit(int width, int height) {
	Game g = {0};
	g.width = width;
	g.height = height;

	renderInit();
	g.shader = renderShaderLoad("res/shaders/basic.vertex", "res/shaders/basic.fragment");

	Mat4 identity = mathMat4Identity();
	renderShaderSetModel(&g.shader, &identity);
	renderShaderSetView(&g.shader, &identity);
	renderShaderSetProj(&g.shader, &identity);

	Vec3 ps[4] = {
		{-1.f, -1.f, 0.f},
		{-1.f, 1.f, 0.f},
		{1.f, 1.f, 0.f},
		{1.f, -1.f, 0.f},
	};

	Color cs[4] = {
		{1.f, 0.f, 0.f, 1.f},
		{0.f, 1.f, 0.f, 1.f},
		{0.f, 0.f, 1.f, 1.f},
		{1.f, 1.f, 1.f, 1.f}
	};

	Vec2 ts[4] = {
		{0.f, 0.f},
		{0.f, 0.f},
		{0.f, 0.f},
		{0.f, 0.f}
	};

	int is[6] = {
		0, 1, 3, 1, 2, 3
	};

	g.m = renderMeshNew(4, ps, cs, ts, 6, is);
	g.t = mathTransform((Vec3){0.f, 0.f, 0.f}, (Vec3){0.f, 0.f, 0.f}, (Vec3){1.f, 1.f, 1.f});

	return g;
}

void gameKeyPressed(Game* g, int key) {

}

void gameKeyReleased(Game* g, int key) {

}

void gameUpdate(Game* g, double dt) {

}

void gameRender(Game* g) {
	renderClear();
	renderShaderBind(&g->shader);

	Mat4 m = mathTransformMatrix(&g->t);
	renderShaderSetModel(&g->shader, &m);
	renderMeshDraw(&g->shader, &g->m);
}
