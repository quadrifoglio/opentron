#include "client/entity.h"

Entity entityNew(Mesh mesh) {
	Entity e;
	e.mesh = mesh;
	e.transform = mathTransform((Vec3){0.f, 0.f, 0.f}, (Vec3){0.f, 0.f, 0.f}, (Vec3){1.f, 1.f, 1.f});

	return e;
}

void entityDraw(Entity* e, Shader* s) {
	Mat4 m = mathTransformMatrix(&e->transform);

	renderShaderSetModel(s, &m);
	renderMeshDraw(s, &e->mesh);
}

Camera entityCameraNew() {
	Camera c;
	c.position = (Vec3){0.f, 0.f, 0.f};
	c.pitch = 0.f;
	c.yaw = 0.f;

	return c;
}

void entityCameraMove(Camera* c, Vec3 amt, float dt) {
	c->position.x += amt.x * dt;
	c->position.y += amt.y * dt;
	c->position.z += amt.z * dt;
}

void entityCameraUse(Camera* c, Shader* s) {
	Mat4 m = entityCameraMatrix(c);
	renderShaderSetView(s, &m);
}

Mat4 entityCameraMatrix(Camera* c) {
	return mathMat4LookAt(c->position, c->target, (Vec3){0.f, 1.f, 0.f});
}

Room entityRoomNew(float size) {
	Room r;
	r.size = size;

	int is[6] = {0, 1, 3, 1, 2, 3};
	Vec3 vs[4];
	Color cs[4];
	Vec2 ts[4];

	vs[0] = (Vec3){0.f, 0.f, 0.f};
	vs[1] = (Vec3){0.f, 0.f, size};
	vs[2] = (Vec3){size, 0.f, size};
	vs[3] = (Vec3){size, 0.f, 0.f};

	cs[0] = (Color){1.f, 1.f, 1.f, 1.f};
	cs[1] = (Color){1.f, 1.f, 1.f, 1.f};
	cs[2] = (Color){1.f, 1.f, 1.f, 1.f};
	cs[3] = (Color){1.f, 1.f, 1.f, 1.f};

	ts[0]= (Vec2){0.f, 0.f};
	ts[1]= (Vec2){0.f, 0.f};
	ts[2]= (Vec2){0.f, 0.f};
	ts[3]= (Vec2){0.f, 0.f};

	r.mesh = renderMeshNew(4, vs, cs, ts, 6, is);

	return r;
}
