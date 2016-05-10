#pragma once

#include <GL/glew.h>
#include "lib/maths.h"

typedef struct {
	float r, g, b, a;
} Color;

typedef struct {
	GLuint program;

	// Uniform locations
	GLint model;
	GLint view;
	GLint proj;

	// Atrribute locations
	GLint position;
	GLint color;
	GLint tex;
} Shader;

typedef struct {
	GLuint vbo, cbo, tbo, ibo;
	size_t size;
} Mesh;

void renderInit(void);
void renderClear(void);

Shader renderShaderLoad(const char* vpath, const char* fpath);
void renderShaderSetModel(Shader* s, Mat4* model);
void renderShaderSetView(Shader* s, Mat4* view);
void renderShaderSetProj(Shader* s, Mat4* proj);
void renderShaderBind(Shader* s);

Mesh renderMeshNew(size_t vn, Vec3* poss, Color* cols, Vec2* texs, size_t in, int* is);
Mesh renderMeshLoad(const char* path);
void renderMeshDraw(Shader* s, Mesh* m);
