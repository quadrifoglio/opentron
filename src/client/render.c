#include "client/render.h"

#include <stdio.h>
#include "utils.h"

void renderInit(void) {
	glClearColor(0.f, 0.f, 0.f, 0.f);

	glFrontFace(GL_CW);
	glCullFace(GL_BACK);

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_FRAMEBUFFER_SRGB);
}

void renderClear(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

Shader renderShaderLoad(const char* vpath, const char* fpath) {
	Shader s = {0};

	char* vs = fileGetContentStr(vpath);
	if(!vs) {
		fprintf(stderr, "Can not read shader from %s\n", vpath);
		return s;
	}

	char* fs = fileGetContentStr(fpath);
	if(!fs) {
		fprintf(stderr, "Can not read shader from %s\n", fpath);
		return s;
	}

	GLuint vsid = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vsid, 1, (const GLchar**)&vs, 0);

	GLuint fsid = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fsid, 1, (const GLchar**)&fs, 0);

	GLint status;
	glCompileShader(vsid);

	glGetShaderiv(vsid, GL_COMPILE_STATUS, &status);
	if(status != GL_TRUE) {
		char err[512];
		glGetShaderInfoLog(vsid, 512, NULL, err);

		fprintf(stderr, "Can not compile fragment shader: %s\n", err);
		return s;
	}

	status = GL_TRUE;
	glCompileShader(fsid);

	glGetShaderiv(fsid, GL_COMPILE_STATUS, &status);
	if(status != GL_TRUE) {
		char err[512];
		glGetShaderInfoLog(fsid, 512, NULL, err);

		fprintf(stderr, "Can not compile fragment shader: %s\n", err);
		return s;
	}

	s.program = glCreateProgram();
	glAttachShader(s.program, vsid);
	glAttachShader(s.program, fsid);

	status = GL_TRUE;
	glLinkProgram(s.program);

	glGetProgramiv(s.program, GL_LINK_STATUS, &status);
	if(status != GL_TRUE) {
		char err[512];
		glGetProgramInfoLog(s.program, 512, NULL, err);

		fprintf(stderr, "Can not link shader program: %s\n", err);
		return s;
	}

	glUseProgram(s.program);

	s.model = glGetUniformLocation(s.program, "model");
	s.view = glGetUniformLocation(s.program, "view");
	s.proj = glGetUniformLocation(s.program, "proj");

	s.position = glGetAttribLocation(s.program, "position");
	glEnableVertexAttribArray(s.position);

	s.color = glGetAttribLocation(s.program, "color");
	glEnableVertexAttribArray(s.color);

	s.tex = glGetAttribLocation(s.program, "tex");
	glEnableVertexAttribArray(s.tex);

	return s;
}

void renderShaderSetModel(Shader* s, Mat4* model) {
	glUniformMatrix4fv(s->model, 1, GL_TRUE, (const GLfloat*)model->m);
}

void renderShaderSetView(Shader* s, Mat4* view) {
	glUniformMatrix4fv(s->view, 1, GL_TRUE, (const GLfloat*)view->m);
}

void renderShaderSetProj(Shader* s, Mat4* proj) {
	glUniformMatrix4fv(s->proj, 1, GL_TRUE, (const GLfloat*)proj->m);
}

void renderShaderBind(Shader* s) {
	glUseProgram(s->program);
}

Mesh renderMeshNew(size_t vn, Vec3* poss, Color* cols, Vec2* texs, size_t in, int* is) {
	Mesh m;
	m.size = in;

	glGenBuffers(4, &m.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m.vbo);
	glBufferData(GL_ARRAY_BUFFER, vn * 3 * sizeof(float), poss, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, m.cbo);
	glBufferData(GL_ARRAY_BUFFER, vn * 4 * sizeof(float), cols, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, m.tbo);
	glBufferData(GL_ARRAY_BUFFER, vn * 2 * sizeof(float), texs, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m.ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, in * sizeof(int), is, GL_STATIC_DRAW);

	return m;
}

void renderMeshDraw(Shader* s, Mesh* m) {
	glBindBuffer(GL_ARRAY_BUFFER, m->vbo);
	glVertexAttribPointer(s->position, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m->cbo);
	glVertexAttribPointer(s->color, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m->tbo);
	glVertexAttribPointer(s->tex, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m->ibo);
	glDrawElements(GL_TRIANGLES, m->size, GL_UNSIGNED_INT, 0);
}
