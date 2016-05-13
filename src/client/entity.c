#include "client/entity.h"

Entity entityNew(Mesh mesh) {
	Entity e;
	e.mesh = mesh;
	e.transform = mathTransform((Vec3){0.f, 0.f, 0.f}, (Vec3){0.f, 0.f, 0.f}, (Vec3){1.f, 1.f, 1.f});

	return e;
}

Camera entityCameraNew() {
	Camera c;
	c.position = (Vec3){0.f, 0.f, 0.f};
	c.target = (Vec3){0.f, 0.f, 0.f};
	c.pitch = 0.f;
	c.yaw = 0.f;

	return c;
}

void entityCameraUse(Camera* c, Shader* s) {
	Mat4 m = entityCameraMatrix(c);
	renderShaderSetView(s, &m);
}

Mat4 entityCameraMatrix(Camera* c) {
	return mathMat4LookAt(c->position, c->target, (Vec3){0.f, 1.f, 0.f});
}

Room entityRoomNew(float size, float height) {
	Room r;
	r.size = size;

	unsigned int groundIs[6] = {
		0, 3, 1, 3, 2, 1
	};

	Vec3 groundPs[4];
	Color groundCs[4];
	Vec2 groundTs[4];

	groundPs[0] = (Vec3){-size / 2.f, 0.f,  size / 2.f};
	groundPs[1] = (Vec3){-size / 2.f, 0.f, -size / 2.f};
	groundPs[2] = (Vec3){ size / 2.f, 0.f, -size / 2.f};
	groundPs[3] = (Vec3){ size / 2.f, 0.f,  size / 2.f};

	groundCs[0] = (Color){1.f, 1.f, 1.f, 1.f};
	groundCs[1] = (Color){1.f, 1.f, 1.f, 1.f};
	groundCs[2] = (Color){1.f, 1.f, 1.f, 1.f};
	groundCs[3] = (Color){1.f, 1.f, 1.f, 1.f};

	groundTs[0] = (Vec2){0.f, 0.f};
	groundTs[1] = (Vec2){size, 0.f};
	groundTs[2] = (Vec2){size, size};
	groundTs[3] = (Vec2){0.f, size};

	r.groundMesh = renderMeshNew(4, groundPs, groundCs, groundTs, 6, groundIs);
	r.groundTex = renderTextureLoad("res/textures/ground.png");

	unsigned int wallsIs[24] = {
		0, 3, 1, 3, 2, 1,
		4, 7, 5, 7, 6, 5,
		8, 11, 9, 11, 10, 9,
		12, 15, 13, 15, 14, 13
	};

	Vec3 wallsPs[16];
	Color wallsCs[16];
	Vec2 wallsTs[16];

	// Left wall
	wallsPs[0] = (Vec3){-size / 2.f, 0.f,     size / 2.f};
	wallsPs[1] = (Vec3){-size / 2.f, height,  size / 2.f};
	wallsPs[2] = (Vec3){-size / 2.f, height, -size / 2.f};
	wallsPs[3] = (Vec3){-size / 2.f, 0.f,    -size / 2.f};

	wallsCs[0] = (Color){1.f, 1.f, 1.f, 1.f};
	wallsCs[1] = (Color){1.f, 1.f, 1.f, 1.f};
	wallsCs[2] = (Color){1.f, 1.f, 1.f, 1.f};
	wallsCs[3] = (Color){1.f, 1.f, 1.f, 1.f};

	wallsTs[0] = (Vec2){0.f, 0.f};
	wallsTs[1] = (Vec2){0.f, 1.f};
	wallsTs[2] = (Vec2){1.f, 1.f};
	wallsTs[3] = (Vec2){1.f, 0.f};

	// Front wall
	wallsPs[4]  = (Vec3){-size / 2.f, 0.f,    -size / 2.f};
	wallsPs[5]  = (Vec3){-size / 2.f, height, -size / 2.f};
	wallsPs[6] = (Vec3){ size / 2.f, height,  -size / 2.f};
	wallsPs[7] = (Vec3){ size / 2.f,  0.f,    -size / 2.f};

	wallsCs[4] = (Color){1.f, 1.f, 1.f, 1.f};
	wallsCs[5] = (Color){1.f, 1.f, 1.f, 1.f};
	wallsCs[6] = (Color){1.f, 1.f, 1.f, 1.f};
	wallsCs[7] = (Color){1.f, 1.f, 1.f, 1.f};

	wallsTs[4] = (Vec2){0.f, 0.f};
	wallsTs[5] = (Vec2){0.f, 1.f};
	wallsTs[6] = (Vec2){1.f, 1.f};
	wallsTs[7] = (Vec2){1.f, 0.f};

	// Right wall
	wallsPs[8] = (Vec3){size / 2.f, 0.f,    -size / 2.f};
	wallsPs[9] = (Vec3){size / 2.f, height, -size / 2.f};
	wallsPs[10] = (Vec3){size / 2.f, height, size / 2.f};
	wallsPs[11] = (Vec3){size / 2.f, 0.f,    size / 2.f};

	wallsCs[8] = (Color){1.f, 1.f, 1.f, 1.f};
	wallsCs[9] = (Color){1.f, 1.f, 1.f, 1.f};
	wallsCs[10] = (Color){1.f, 1.f, 1.f, 1.f};
	wallsCs[11] = (Color){1.f, 1.f, 1.f, 1.f};

	wallsTs[8] = (Vec2){0.f, 0.f};
	wallsTs[9] = (Vec2){0.f, 1.f};
	wallsTs[10] = (Vec2){1.f, 1.f};
	wallsTs[11] = (Vec2){1.f, 0.f};

	// Back wall
	wallsPs[12] = (Vec3){ size / 2.f, 0.f,    size / 2.f};
	wallsPs[13] = (Vec3){ size / 2.f, height, size / 2.f};
	wallsPs[14] = (Vec3){-size / 2.f, height, size / 2.f};
	wallsPs[15] = (Vec3){-size / 2.f,  0.f,   size / 2.f};

	wallsCs[12] = (Color){1.f, 1.f, 1.f, 1.f};
	wallsCs[13] = (Color){1.f, 1.f, 1.f, 1.f};
	wallsCs[14] = (Color){1.f, 1.f, 1.f, 1.f};
	wallsCs[15] = (Color){1.f, 1.f, 1.f, 1.f};

	wallsTs[12] = (Vec2){0.f, 0.f};
	wallsTs[13] = (Vec2){0.f, 1.f};
	wallsTs[14] = (Vec2){1.f, 1.f};
	wallsTs[15] = (Vec2){1.f, 0.f};

	r.wallsMesh = renderMeshNew(16, wallsPs, wallsCs, wallsTs, 24, wallsIs);
	r.wallsTex = renderTextureLoad("res/textures/walls.png");

	return r;
}
