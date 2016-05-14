#include "client/render.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STB_IMAGE_IMPLEMENTATION
#include "lib/stb_image.h"

#include "utils.h"

void renderInit(void) {
	glClearColor(0.03f, 0.07f, 0.09f, 1.f);

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_MULTISAMPLE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void renderClear(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void renderCullFace(bool enabled) {
	if(enabled) {
		glEnable(GL_CULL_FACE);
	}
	else {
		glDisable(GL_CULL_FACE);
	}
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

		free(vs);
		free(fs);
		return s;
	}

	status = GL_TRUE;
	glCompileShader(fsid);

	glGetShaderiv(fsid, GL_COMPILE_STATUS, &status);
	if(status != GL_TRUE) {
		char err[512];
		glGetShaderInfoLog(fsid, 512, NULL, err);
		fprintf(stderr, "Can not compile fragment shader: %s\n", err);

		free(vs);
		free(fs);
		return s;
	}

	free(vs);
	free(fs);

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

	glDeleteShader(vsid);
	glDeleteShader(fsid);

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

void renderShaderSetTransform(Shader* s, Transform t) {
	Mat4 m = mathTransformMatrix(t);
	renderShaderSetModel(s, &m);
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

Texture renderTextureWhite(void) {
	unsigned char data[4] = { 255, 255, 255, 255 };
	Texture tex;

	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glBindTexture(GL_TEXTURE_2D, 0);

	return tex;
}

Texture renderTextureLoad(const char* path) {
	int w, h, n;
	void* data = stbi_load(path, &w, &h, &n, 4);
	if(!data) {
		fprintf(stderr, "Can not load texture %s\n", path);
		return 0;
	}

	GLuint tex;

	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	free(data);
	glBindTexture(GL_TEXTURE_2D, 0);

	return tex;
}

Mesh renderMeshNew(size_t vn, Vec3* poss, Color* cols, Vec2* texs, size_t in, unsigned int* is) {
	Mesh m;
	m.size = in;
	m.primitive = GL_TRIANGLES;

	glGenBuffers(4, &m.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m.vbo);
	glBufferData(GL_ARRAY_BUFFER, vn * 3 * sizeof(float), poss, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, m.cbo);
	glBufferData(GL_ARRAY_BUFFER, vn * 4 * sizeof(float), cols, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, m.tbo);
	glBufferData(GL_ARRAY_BUFFER, vn * 2 * sizeof(float), texs, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m.ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, in * sizeof(unsigned int), is, GL_STATIC_DRAW);

	return m;
}

Mesh renderMeshLoad(const char* path, Color defColor) {
	Mesh m = {0};
	m.primitive = GL_TRIANGLES;

	char* data = fileGetContentStr(path);
	if(!data) {
		return m;
	}

	Vec3* vs = 0;
	Color* cs = 0;
	Vec2* ts = 0;
	size_t nvs = 0;

	unsigned int* is = 0;
	size_t nis = 0;

	char* line = data;
	while(line) {
		char* next = strchr(line, '\n');
		if(next) *next = 0;

		if(line[0] == 'v') {
			float x, y, z;
			sscanf(line, "v %f %f %f", &x, &y, &z);

			vs = realloc(vs, (++nvs) * sizeof(Vec3));
			vs[nvs - 1] = (Vec3){x, y, z};

			cs = realloc(cs, nvs * sizeof(Color));
			cs[nvs - 1] = defColor;

			ts = realloc(ts, nvs * sizeof(Vec2));
			ts[nvs - 1] = (Vec2){0.f, 0.f};
		}
		else if(line[0] == 'f') {
			int i[3]; // Indices
			int t[3]; // Tex coords
			int n[3]; // Normals

			sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d", &i[0], &t[0], &n[0], &i[1], &t[1], &n[1], &i[2], &t[2], &n[2]);

			i[0] = i[0] - 1;
			i[1] = i[1] - 1;
			i[2] = i[2] - 1;

			is = realloc(is, (nis += 3) * sizeof(int));
			memcpy(is + (nis - 3), i, 3 * sizeof(int));
		}

		if(next) *next = '\n';
		line = next ? (next + 1) : 0;
	}

	free(data);
	m = renderMeshNew(nvs, vs, cs, ts, nis, is);

	free(vs);
	free(cs);
	free(ts);
	free(is);

	return m;
}

void renderMeshDraw(Shader* s, Mesh* m, Texture tex) {
	glBindTexture(GL_TEXTURE_2D, tex);

	glBindBuffer(GL_ARRAY_BUFFER, m->vbo);
	glVertexAttribPointer(s->position, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m->cbo);
	glVertexAttribPointer(s->color, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m->tbo);
	glVertexAttribPointer(s->tex, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m->ibo);
	glDrawElements(m->primitive, m->size, GL_UNSIGNED_INT, 0);
}
