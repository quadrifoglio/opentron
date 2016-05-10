#pragma once

/*
 * This is from YoctoGL by xelatihy (https://github.com/xelatihy/yocto-gl)
 * released under the terms of the permissive MIT license.
 */

//
// LICENSE:
//
// Copyright (c) 2016 Fabio Pellacini
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

#include <math.h>
#include <stdbool.h>

#define PIF 3.14159265f
#define PI 3.1415926535897932384626433832795

typedef struct {
	float x, y;
} Vec2;

typedef struct {
	float x, y, z;
} Vec3;

typedef struct {
	float x, y, z, w;
} Vec4;

typedef struct {
	float m[16];
} Mat4;

typedef struct {
	Vec3 translation;
	Vec3 rotation;
	Vec3 scaling;
} Transform;

static inline
int mathMin(int x, int y) {
    return (x < y) ? x : y;
}
static inline
int mathMax(int x, int y) {
    return (x > y) ? x : y;
}
static inline
int mathClamp(int x, int m, int M) {
    return mathMin(M, mathMax(m, x));
}
static inline
double mathFclamp(double x, double m, double M) {
    return fmin(M, fmax(m, x));
}
static inline
float mathFclampF(float x, float m, float M) {
    return fminf(M, fmaxf(m, x));
}

static inline
Vec3 mathVec3Zero() {
    return (Vec3){0, 0, 0};
}

static inline
Vec3 mathVec3Negate(const Vec3 a) {
    return (Vec3){-a.x, -a.y, -a.z};
}

static inline
Vec3 mathVec3Add(const Vec3 a, const Vec3 b) {
    return (Vec3){a.x + b.x, a.y + b.y, a.z + b.z};
}

static inline
Vec3 mathVec3Lerp(const Vec3 a, const Vec3 b, float u) {
	return (Vec3){a.x * (1 - u) + b.x * u, a.y * (1 - u) + b.y * u, a.z * (1 - u) + b.z * u};
}

static inline
Vec3 mathVec3Sub(const Vec3 a, const Vec3 b) {
	return (Vec3){a.x - b.x, a.y - b.y, a.z - b.z};
}

static inline
Vec3 mathVec3Mul(const Vec3 a, const Vec3 b) {
	return (Vec3){a.x * b.x, a.y * b.y, a.z * b.z};
}

static inline
Vec3 mathVec3MulF(const Vec3 a, float b) {
	return (Vec3){a.x * b, a.y * b, a.z * b};
}

static inline
float mathVec3Dot(const Vec3 a, const Vec3 b) {
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

static inline
float mathVec3Length(const Vec3 a) {
	return (float)sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
}

static inline
Vec3 mathVec3Norm(const Vec3 a) {
	return mathVec3MulF(a, (1 / mathVec3Length(a)));
}

static inline
float mathVec3Dist(const Vec3 a, const Vec3 b) {
	return (float)sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z));
}

static inline
Vec3 mathVec3Cross(const Vec3 a, const Vec3 b) {
	return (Vec3){a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
}

static inline
Vec2 mathVec2Zero() {
	return (Vec2){0, 0};
}

static inline
Vec2 mathVec2Neg(const Vec2 a) {
	return (Vec2){-a.x, -a.y};
}

static inline
Vec2 mathVec2Sum(const Vec2 a, const Vec2 b) {
	return (Vec2){a.x + b.x, a.y + b.y};
}

static inline
Vec2 mathVec2Sub(const Vec2 a, const Vec2 b) {
return (Vec2){a.x - b.x, a.y - b.y};
}

static inline
Vec2 mathVec2Mul(const Vec2 a, const Vec2 b) {
	return (Vec2){a.x * b.x, a.y * b.y};
}

static inline
Vec2 mathVec2MulF(const Vec2 a, float b) {
	return (Vec2){a.x * b, a.y * b};
}

static inline
float mathVec2Dot(const Vec2 a, const Vec2 b) {
	return (a.x * b.x + a.y * b.y);
}

static inline
Mat4 mathMat4Identity() {
	return (Mat4){{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 }};
}

static inline
Mat4 mathMat4Transpose(const Mat4 a) {
	Mat4 c = a;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			c.m[i * 4 + j] = a.m[j * 4 + i];
		}
	}

	return c;
}

static inline
Mat4 mathMat4Mul(const Mat4 a, const Mat4 b) {
	Mat4 c = {{ 0 }};

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			c.m[i * 4 + j] = 0;

			for (int k = 0; k < 4; k++) {
				c.m[i * 4 + j] += a.m[i * 4 + k] * b.m[k * 4 + j];
			}
		}
	}

	return c;
}

// http://stackoverflow.com/questions/2624422/efficient-4x4-matrix-inverse-affine-transform
static inline
Mat4 mathMat4Inverse(const Mat4 m) {
	float a[4][4];
	*(Mat4*)a = m;

	float s0 = a[0][0] * a[1][1] - a[1][0] * a[0][1];
	float s1 = a[0][0] * a[1][2] - a[1][0] * a[0][2];
	float s2 = a[0][0] * a[1][3] - a[1][0] * a[0][3];
	float s3 = a[0][1] * a[1][2] - a[1][1] * a[0][2];
	float s4 = a[0][1] * a[1][3] - a[1][1] * a[0][3];
	float s5 = a[0][2] * a[1][3] - a[1][2] * a[0][3];

	float c5 = a[2][2] * a[3][3] - a[3][2] * a[2][3];
	float c4 = a[2][1] * a[3][3] - a[3][1] * a[2][3];
	float c3 = a[2][1] * a[3][2] - a[3][1] * a[2][2];
	float c2 = a[2][0] * a[3][3] - a[3][0] * a[2][3];
	float c1 = a[2][0] * a[3][2] - a[3][0] * a[2][2];
	float c0 = a[2][0] * a[3][1] - a[3][0] * a[2][1];

	// TODO: Should check for 0 determinant
	float invdet = 1.0f / (s0 * c5 - s1 * c4 + s2 * c3 + s3 * c2 - s4 * c1 + s5 * c0);

	float b[4][4];

	b[0][0] = (a[1][1] * c5 - a[1][2] * c4 + a[1][3] * c3) * invdet;
	b[0][1] = (-a[0][1] * c5 + a[0][2] * c4 - a[0][3] * c3) * invdet;
	b[0][2] = (a[3][1] * s5 - a[3][2] * s4 + a[3][3] * s3) * invdet;
	b[0][3] = (-a[2][1] * s5 + a[2][2] * s4 - a[2][3] * s3) * invdet;

	b[1][0] = (-a[1][0] * c5 + a[1][2] * c2 - a[1][3] * c1) * invdet;
	b[1][1] = (a[0][0] * c5 - a[0][2] * c2 + a[0][3] * c1) * invdet;
	b[1][2] = (-a[3][0] * s5 + a[3][2] * s2 - a[3][3] * s1) * invdet;
	b[1][3] = (a[2][0] * s5 - a[2][2] * s2 + a[2][3] * s1) * invdet;

	b[2][0] = (a[1][0] * c4 - a[1][1] * c2 + a[1][3] * c0) * invdet;
	b[2][1] = (-a[0][0] * c4 + a[0][1] * c2 - a[0][3] * c0) * invdet;
	b[2][2] = (a[3][0] * s4 - a[3][1] * s2 + a[3][3] * s0) * invdet;
	b[2][3] = (-a[2][0] * s4 + a[2][1] * s2 - a[2][3] * s0) * invdet;

	b[3][0] = (-a[1][0] * c3 + a[1][1] * c1 - a[1][2] * c0) * invdet;
	b[3][1] = (a[0][0] * c3 - a[0][1] * c1 + a[0][2] * c0) * invdet;
	b[3][2] = (-a[3][0] * s3 + a[3][1] * s1 - a[3][2] * s0) * invdet;
	b[3][3] = (a[2][0] * s3 - a[2][1] * s1 + a[2][2] * s0) * invdet;

	return *(Mat4*)b;
}

static inline
Mat4 mathMat4Translation(const Vec3 a) {
	return (Mat4){{ 1, 0, 0, a.x, 0, 1, 0, a.y, 0, 0, 1, a.z, 0, 0, 0, 1 }};
}

static inline
Mat4 mathMat4Scaling(const Vec3 a) {
	return (Mat4){{ a.x, 0, 0, 0, 0, a.y, 0, 0, 0, 0, a.z, 0, 0, 0, 0, 1 }};
}

static inline
Mat4 mathMat4Rotation(float a, const Vec3 b) {
	float s = sinf(a * PI / 180.f), c = cosf(a * PIF / 180.f);
	Vec3 vv = mathVec3Norm(b);

	return (Mat4){{
		c + (1 - c) * vv.x * vv.x, (1 - c) * vv.x * vv.y - s * vv.z,
		(1 - c) * vv.x * vv.z + s * vv.y, 0, (1 - c) * vv.x * vv.y + s * vv.z,
		c + (1 - c) * vv.y * vv.y, (1 - c) * vv.y * vv.z - s * vv.x, 0,
		(1 - c) * vv.x * vv.z - s * vv.y, (1 - c) * vv.y * vv.z + s * vv.x,
		c + (1 - c) * vv.z * vv.z, 0, 0, 0, 0, 1
	}};
}

static inline
Mat4 mathMat4RotationV(const Vec3 v) {
	/*Mat4 rx = mathMat4Identity();
	Mat4 ry = mathMat4Identity();
	Mat4 rz = mathMat4Identity();

	float x = v.x * 180.f / PI;
	float y = v.y * 180.f / PI;
	float z = v.z * 180.f / PI;

	rz.m[0][0] = (float)cos(z);
	rz.m[0][1] = (float)-sin(z);
	rz.m[1][0] = (float)sin(z);
	rz.m[1][1] = (float)cos(z);

	rx.m[1][1] = (float)cos(x);
	rx.m[2][1] = (float)sin(x);
	rx.m[1][2] = (float)-sin(x);
	rx.m[2][2] = (float)cos(x);

	ry.m[0][0] = (float)cos(y);
	ry.m[2][0] = (float)sin(y);
	ry.m[0][2] = (float)-sin(y);
	ry.m[2][2] = (float)cos(y);

	return mathMat4Mul(rz, mathMat4Mul(ry, rx));*/

	return mathMat4Identity();
}

static inline
Mat4 mathMat4Frustum(float l, float r, float b, float t, float n, float f) {
	return (Mat4){{
		2 * n / (r - l), 0, (r + l) / (r - l), 0,
		0, 2 * n / (t - b), (t + b) / (t - b), 0,
		0, 0, -(f + n) / (f - n), -2 * f * n / (f - n),
		0, 0, -1, 0
	}};
}

static inline
Mat4 mathMat4Ortho(float l, float r, float b, float t, float n, float f) {
	return (Mat4){{
		2 / (r - l), 0, 0, -(r + l) / (r - l),
		0, 2 / (t - b), 0, -(t + b) / (t - b),
		0, 0, -2 / (f - n), -(f + n) / (f - n),
		0, 0, 0, 1
	}};
}

static inline
Mat4 mathMat4LookAt(const Vec3 eye, const Vec3 center, const Vec3 up) {
	Vec3 w = mathVec3Norm(mathVec3Sub(eye, center));
	Vec3 u = mathVec3Norm(mathVec3Cross(up, w));
	Vec3 v = mathVec3Norm(mathVec3Cross(w, u));

	return (Mat4){{
		u.x, u.y, u.z, -mathVec3Dot(u, eye),
		v.x, v.y, v.z, -mathVec3Dot(v, eye),
		w.x, w.y, w.z, -mathVec3Dot(w, eye),
		0, 0, 0, 1
	}};
}

static inline
Mat4 mathMat4LookatXform(const Vec3 eye, const Vec3 center, const Vec3 up) {
	Vec3 w = mathVec3Norm(mathVec3Sub(eye, center));
	Vec3 u = mathVec3Norm(mathVec3Cross(up, w));
	Vec3 v = mathVec3Norm(mathVec3Cross(w, u));

	return (Mat4){{
		u.x, v.x, w.x, eye.x,
		u.y, v.y, w.y, eye.y,
		u.z, v.z, w.z, eye.z,
		0, 0, 0, 1
	}};
}

static inline
Mat4 mathMat4Ortho2D(float l, float r, float b, float t) {
	return (Mat4){{
		2 / (r - l), 0, 0, -(r + l) / (r - l),
		0, 2 / (t - b), 0, -(t + b) / (t - b),
		0, 0, -1, 0,
		0, 0, 0, 1
	}};
}

static inline
Mat4 mathMat4Perspective(float fov, float w, float h, float near, float far) {
	float aspect = w / h;

	/*float f = 1.f / tanf(fovy / 2.f);
	return (Mat4){{
		f / aspect, 0, 0, 0,
		0, f, 0, 0,
		0, 0, (far + near) / (near - far), 2 * far * near / (near - far),
		0, 0, -1, 0
	}};*/

	return (Mat4){{
		1.f / (aspect * tanf((fov * PIF / 180.f) / 2.f)), 0, 0, 0,
		0, 1.f / tanf((fov * PIF / 180.f) / 2.f), 0, 0,
		0, 0, (-near - far) / (near - far), (2 * far * near) / (near - far),
		0, 0, 1, 0
	}};
}

static inline
Transform mathTransform(const Vec3 t, const Vec3 r, const Vec3 s) {
	return (Transform){t, r, s};
}

static inline
Mat4 mathTransformMatrix(Transform t) {
	Mat4 tr = mathMat4Translation(t.translation);
	Mat4 ro = mathMat4RotationV(t.rotation);
	Mat4 sc = mathMat4Scaling(t.scaling);

	return mathMat4Mul(mathMat4Mul(sc, ro), tr);
}
