#pragma once

#include "client/render.h"

typedef struct {
	Mesh mesh;
	Transform tr;
} Entity;

typedef struct {
	Vec3 position;
	Vec3 target;
	float pitch;
	float yaw;
} Camera;

typedef struct {
	float size;

	Mesh groundMesh;
	Mesh gridMesh;
	Mesh wallsMesh;
} Room;

typedef struct {
	Mesh mesh;

	Vec3 start;
	Vec3 end;
} Wall;

typedef struct {
	Entity e;

	float speed;
	Vec3 size;
	Vec3 pos; // Current position
	Vec3 dir; // Current direction
} Player;

Entity entityNew(Mesh mesh);

Camera entityCameraNew();
void entityCameraUse(Camera* c, Shader* s);
Mat4 entityCameraMatrix(Camera* c);

Room entityRoomNew(float size, float height);

Wall entityWallNew(Vec3 start, Vec3 end);
void entityWallRender(Shader* s, Wall* w, Texture t);

Player entityPlayerNew(Vec3 pos);
void entityPlayerUpdate(float dt, Player* p, Room* r);
