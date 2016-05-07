#include "client/game.h"

Game gameInit(int width, int height) {
	Game g = {0};
	g.width = width;
	g.height = height;

	renderInit();
	g.shader = renderShaderLoad("res/shaders/basic.vertex", "res/shaders/basic.fragment");

	Mat4 identity = mathMat4Identity();
	Mat4 proj = mathMat4Perspective(70.f, width, height, 0.f, 1000.f);

	renderShaderSetModel(&g.shader, &identity);
	renderShaderSetView(&g.shader, &identity);
	renderShaderSetProj(&g.shader, &proj);

	g.cam = entityCameraNew();
	g.cam.position = (Vec3){0.f, 0.f, 1.f};
	g.cam.target = (Vec3){0.f, 0.f, 0.f};

	g.moto = entityNew(renderMeshLoad("res/models/light_cycle.obj"));
	g.moto.transform.translation.z = 10.f;

	g.room = entityRoomNew(50.f);

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

	entityCameraUse(&g->cam, &g->shader);

	Mat4 identity = mathMat4Identity();
	renderShaderSetModel(&g->shader, &identity);
	renderMeshDraw(&g->shader, &g->room.mesh);

	entityDraw(&g->moto, &g->shader);
}
