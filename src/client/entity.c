#include "client/entity.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

Entity entityNew(Mesh mesh) {
	Entity e;
	e.mesh = mesh;
	e.tr = mathTransform((Vec3){0.f, 0.f, 0.f}, (Vec3){0.f, 0.f, 0.f}, (Vec3){1.f, 1.f, 1.f});

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

	// Ground
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

	/*groundCs[0] = (Color){0.03f, 0.07f, 0.09f, 1.f};
	groundCs[1] = (Color){0.03f, 0.07f, 0.09f, 1.f};
	groundCs[2] = (Color){0.03f, 0.07f, 0.09f, 1.f};
	groundCs[3] = (Color){0.03f, 0.07f, 0.09f, 1.f};*/

	groundCs[0] = (Color){0.2f, 0.7f, 0.8f, 0.1f};
	groundCs[1] = (Color){0.2f, 0.7f, 0.8f, 0.1f};
	groundCs[2] = (Color){0.2f, 0.7f, 0.8f, 0.1f};
	groundCs[3] = (Color){0.2f, 0.7f, 0.8f, 0.1f};

	groundTs[0] = (Vec2){0.f, 0.f};
	groundTs[1] = (Vec2){size, 0.f};
	groundTs[2] = (Vec2){size, size};
	groundTs[3] = (Vec2){0.f, size};

	r.groundMesh = renderMeshNew(4, groundPs, groundCs, groundTs, 6, groundIs);

	// Ground grid
	unsigned int gridIs[2] = {
		0, 1,
	};

	Vec3 gridPs[6];
	Color gridCs[6];
	Vec2 gridTs[6];

	r.yGridMesh = renderMeshNew(2, gridPs + 4, gridCs + 4, gridTs + 4, 2, gridIs);
	r.yGridMesh.primitive = GL_LINES;

	// Walls
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
	wallsTs[2] = (Vec2){2.f, 1.f};
	wallsTs[3] = (Vec2){2.f, 0.f};

	// Front wall
	wallsPs[4] = (Vec3){-size / 2.f, 0.f,    -size / 2.f};
	wallsPs[5] = (Vec3){-size / 2.f, height, -size / 2.f};
	wallsPs[6] = (Vec3){ size / 2.f, height, -size / 2.f};
	wallsPs[7] = (Vec3){ size / 2.f,  0.f,   -size / 2.f};

	wallsCs[4] = (Color){1.f, 1.f, 1.f, 1.f};
	wallsCs[5] = (Color){1.f, 1.f, 1.f, 1.f};
	wallsCs[6] = (Color){1.f, 1.f, 1.f, 1.f};
	wallsCs[7] = (Color){1.f, 1.f, 1.f, 1.f};

	wallsTs[4] = (Vec2){0.f, 0.f};
	wallsTs[5] = (Vec2){0.f, 1.f};
	wallsTs[6] = (Vec2){2.f, 1.f};
	wallsTs[7] = (Vec2){2.f, 0.f};

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
	wallsTs[10] = (Vec2){2.f, 1.f};
	wallsTs[11] = (Vec2){2.f, 0.f};

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
	wallsTs[14] = (Vec2){2.f, 1.f};
	wallsTs[15] = (Vec2){2.f, 0.f};

	r.wallsMesh = renderMeshNew(16, wallsPs, wallsCs, wallsTs, 24, wallsIs);

	return r;
}

void entityRoomRender(Shader* s, Room* r, Texture texGround, Texture texGrid, Texture texWalls) {
	Mat4 m;

	renderMeshDraw(s, &r->groundMesh, texGround);
	renderMeshDraw(s, &r->wallsMesh, texWalls);

	m = mathMat4Translation((Vec3){0.f, 0.f, 0.f});
	renderShaderSetModel(s, &m);
	renderMeshDraw(s, &r->yGridMesh, texGrid);
}

Wall entityWallNew(Vec3 start, Vec3 end) {
	static float height = 0.6f;

	Wall w;
	w.start = start;
	w.end = end;

	unsigned int is[6] = {
		3, 1, 0,
		3, 2, 1
	};

	Vec3 ps[4] = {
		(Vec3){0.f, 0.f, 0.f},
		(Vec3){0.f, height, 0.f},
		(Vec3){1.f, height, 0.f},
		(Vec3){1.f, 0.f, 0.f}
	};

	Color cs[4] = {
		(Color){0.f, 0.50f, 0.81f, 0.9f},
		(Color){0.f, 0.50f, 0.81f, 0.9f},
		(Color){0.f, 0.50f, 0.81f, 0.9f},
		(Color){0.f, 0.50f, 0.81f, 0.9f}
	};

	Vec2 ts[4] = {
		(Vec2){0.f, 0.f},
		(Vec2){0.f, 1.f},
		(Vec2){1.f, 1.f},
		(Vec2){1.f, 0.f}
	};

	w.mesh = renderMeshNew(4, ps, cs, ts, 6, is);
	return w;
}

void entityWallRender(Shader* s, Wall* w, Texture tx) {
	float step = 1.f;

	float dx = w->end.x - w->start.x;
	float dz = w->end.z - w->start.z;
	float adx = fabsf(dx);
	float adz = fabsf(dz);

	int n = (int)((adx != 0.f ? adx : adz) / step);
	float c = adx != 0.f ? w->start.x : w->start.z;

	renderCullFace(0);

	for(int i = 1; i <= n; ++i) {
		Vec3 tv;
		tv.x = adx != 0.f ? c : w->end.x;
		tv.y = 0.f;
		tv.z = adz != 0.f ? c : w->end.z;

		float alpha = adz != 0.f ? (adz > 0.f ? (-90.f * PI / 180.f) : (90.f * PI / 180.f)) : 0.f;

		Mat4 t = mathMat4Translation(tv);
		Mat4 r = mathMat4Rotation((Vec3){0.f, alpha * 180.f / PI, 0.f});
		Mat4 m = mathMat4MulM(t, r);

		renderShaderSetModel(s, &m);
		renderMeshDraw(s, &w->mesh, tx);

		if(dx > 0.f || dz > 0.f) {
			c += step;
		}
		else {
			c -= step;
		}
	}

	renderCullFace(1);
}

Player entityPlayerNew(Vec3 pos) {
	static float width = 0.2f;
	static float height = 0.6f;
	static float length = 1.f;
	static float speed = 3.f; // 3 units / second

	Player p;

	p.e = entityNew(renderMeshLoad("res/models/cube.obj", (Color){0.f, 0.f, 1.f, 1.f}));
	p.e.tr.scale = (Vec3){width * 0.5f, height * 0.5f, length * 0.5f};

	p.size = (Vec3){width, height, length};
	p.pos = pos;
	p.dir = (Vec3){-1.f, 0.f, 0.f};
	p.speed = speed;

	return p;
}

void entityPlayerUpdate(float dt, Player* p, Room* r, WallGroup* w) {
	static float collisionDistance = 0.1f;

	if(p->dir.x > 0.f) {
		p->e.tr.rotation.y = -90.f;
	}
	else if(p->dir.x < 0.f) {
		p->e.tr.rotation.y = 90.f;
	}
	else if(p->dir.z > 0.f) {
		p->e.tr.rotation.y = 0.f;
	}
	else if(p->dir.z < 0.f) {
		p->e.tr.rotation.y = 180.f;
	}

	float nx = p->pos.x + (p->dir.x * p->speed * dt);
	float nz = p->pos.z + (p->dir.z * p->speed * dt);

	if(fabsf(nx) + p->size.z / 2.f > r->size / 2.f || fabsf(nz) + p->size.z / 2.f > r->size / 2.f) {
		printf("Map collision ! \n");

		nx = 0.f;
		nz = 0.f;
	}

	if(nz != 0.f) {
		for(int i = 0; i < w->xWallCount; ++i) {
			Wall wall = w->xWalls[i];
			float d;

			if(p->dir.z > 0.f) d = (nx + p->size.z / 2.f) - wall.start.z;
			if(p->dir.z < 0.f) d = (nx - p->size.z / 2.f) - wall.start.z;

			if(fabsf(d) < collisionDistance) {
				printf("Wall collison !\n");
			}
		}
	}
	else if(nx != 0.f) {
		for(int i = 0; i < w->zWallCount; ++i) {
			Wall wall = w->zWalls[i];
			float d;

			if(p->dir.x > 0.f) d = (nx + p->size.z / 2.f) - wall.start.x;
			if(p->dir.x < 0.f) d = (nx - p->size.z / 2.f) - wall.start.x;

			if(fabsf(d) < collisionDistance) {
				printf("Wall collison !\n");
			}
		}
	}

	p->pos.x = nx;
	p->pos.z = nz;

	p->e.tr.translation = p->pos;
}
