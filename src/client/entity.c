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

	unsigned int is[35] = {
		0, 3, 1, 3, 2, 1,       // Ground
		4, 7, 5, 7, 6, 5,       // Left wall
		11, 9, 8, 11, 10, 9,    // Front wall
		15, 13, 12, 15, 14, 13, // Right wall
		19, 17, 16, 19, 18, 17  // Back wall
	};

	Vec3 vs[20];
	Color cs[20];
	Vec2 ts[20];

	// Ground
	vs[0] = (Vec3){-size / 2.f, 0.f,  size / 2.f};
	vs[1] = (Vec3){-size / 2.f, 0.f, -size / 2.f};
	vs[2] = (Vec3){ size / 2.f, 0.f, -size / 2.f};
	vs[3] = (Vec3){ size / 2.f, 0.f,  size / 2.f};

	cs[1] = (Color){1.f, 1.f, 1.f, 1.f};
	cs[1] = (Color){1.f, 1.f, 1.f, 1.f};
	cs[2] = (Color){1.f, 1.f, 1.f, 1.f};
	cs[3] = (Color){1.f, 1.f, 1.f, 1.f};

	ts[0] = (Vec2){0.f, 0.f};
	ts[1] = (Vec2){0.f, 0.f};
	ts[2] = (Vec2){0.f, 0.f};
	ts[3] = (Vec2){0.f, 0.f};

	// Left wall
	vs[4] = (Vec3){-size / 2.f, 0.f,     size / 2.f};
	vs[5] = (Vec3){-size / 2.f, height,  size / 2.f};
	vs[6] = (Vec3){-size / 2.f, height,  -size / 2.f};
	vs[7] = (Vec3){-size / 2.f, 0.f,     -size / 2.f};

	cs[4] = (Color){0.f, 1.f, 0.f, 1.f};
	cs[5] = (Color){0.f, 1.f, 0.f, 1.f};
	cs[6] = (Color){0.f, 1.f, 0.f, 1.f};
	cs[7] = (Color){0.f, 1.f, 0.f, 1.f};

	ts[4] = (Vec2){0.f, 0.f};
	ts[5] = (Vec2){0.f, 0.f};
	ts[6] = (Vec2){0.f, 0.f};
	ts[7] = (Vec2){0.f, 0.f};

	// Front wall
	vs[8]  = (Vec3){-size / 2.f, 0.f,    -size / 2.f};
	vs[9]  = (Vec3){-size / 2.f, height, -size / 2.f};
	vs[10] = (Vec3){ size / 2.f, height, -size / 2.f};
	vs[11] = (Vec3){ size / 2.f,  0.f,   -size / 2.f};

	cs[8]  = (Color){0.f, 0.f, 1.f, 1.f};
	cs[9]  = (Color){0.f, 0.f, 1.f, 1.f};
	cs[10] = (Color){0.f, 0.f, 1.f, 1.f};
	cs[11] = (Color){0.f, 0.f, 1.f, 1.f};

	ts[8]  = (Vec2){0.f, 0.f};
	ts[9]  = (Vec2){0.f, 0.f};
	ts[10] = (Vec2){0.f, 0.f};
	ts[11] = (Vec2){0.f, 0.f};

	// Right wall
	vs[12] = (Vec3){size / 2.f, 0.f,    -size / 2.f};
	vs[13] = (Vec3){size / 2.f, height, -size / 2.f};
	vs[14] = (Vec3){size / 2.f, height,  size / 2.f};
	vs[15] = (Vec3){size / 2.f, 0.f,     size / 2.f};

	cs[12] = (Color){1.f, 1.f, 0.f, 1.f};
	cs[13] = (Color){1.f, 1.f, 0.f, 1.f};
	cs[14] = (Color){1.f, 1.f, 0.f, 1.f};
	cs[15] = (Color){1.f, 1.f, 0.f, 1.f};

	ts[12] = (Vec2){0.f, 0.f};
	ts[13] = (Vec2){0.f, 0.f};
	ts[14] = (Vec2){0.f, 0.f};
	ts[15] = (Vec2){0.f, 0.f};

	// Back wall
	vs[16] = (Vec3){ size / 2.f, 0.f,    size / 2.f};
	vs[17] = (Vec3){ size / 2.f, height, size / 2.f};
	vs[18] = (Vec3){-size / 2.f, height, size / 2.f};
	vs[19] = (Vec3){-size / 2.f,  0.f,   size / 2.f};

	cs[16] = (Color){1.f, 0.f, 0.f, 1.f};
	cs[17] = (Color){1.f, 0.f, 0.f, 1.f};
	cs[18] = (Color){1.f, 0.f, 0.f, 1.f};
	cs[19] = (Color){1.f, 0.f, 0.f, 1.f};

	ts[16] = (Vec2){0.f, 0.f};
	ts[17] = (Vec2){0.f, 0.f};
	ts[18] = (Vec2){0.f, 0.f};
	ts[19] = (Vec2){0.f, 0.f};

	r.mesh = renderMeshNew(20, vs, cs, ts, 35, is);

	return r;
}
