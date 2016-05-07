#pragma once

#include "client/render.h"

typedef struct {
	Mesh mesh;
	Transform transform;
} Entity;

typedef struct {
	Vec3 position;
	Vec3 target;
	float pitch;
	float yaw;
} Camera;

typedef struct {
	float size;
	Mesh mesh;
} Room;

Entity entityNew(Mesh mesh);
void entityDraw(Entity* e, Shader* s);

Camera entityCameraNew();
void entityCameraUse(Camera* c, Shader* s);
Mat4 entityCameraMatrix(Camera* c);

Room entityRoomNew(float size);
