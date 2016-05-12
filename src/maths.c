#include "maths.h"
#include <math.h>

float mathVec2Len(Vec2 v) {
	return sqrtf(v.x * v.x + v.y * v.y);
}

float mathVec3Len(Vec3 v) {
	return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

float mathVec4Len(Vec4 v) {
	return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
}

float mathVec2Dot(Vec2 v1, Vec2 v2) {
	return v1.x * v2.x + v1.y * v2.y;
}

float mathVec3Dot(Vec3 v1, Vec3 v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

float mathVec4Dot(Vec4 v1, Vec4 v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}

Vec3 mathVec3Cross(Vec3 v1, Vec3 v2) {
	Vec3 r;

	r.x = v1.y * v2.z - v1.z * v2.y;
	r.y = v1.z * v2.x - v1.x * v2.z;
	r.z = v1.x * v2.y - v1.y * v2.x;

	return r;
}

Vec2 mathVec2Norm(Vec2 v) {
	float len = mathVec2Len(v);
	Vec2 vv;

	vv.x = v.x / len;
	vv.y = v.y / len;

	return vv;
}

Vec3 mathVec3Norm(Vec3 v) {
	float len = mathVec3Len(v);
	Vec3 vv;

	vv.x = v.x / len;
	vv.y = v.y / len;
	vv.z = v.z / len;

	return vv;
}

Vec4 mathVec4Norm(Vec4 v) {
	float len = mathVec4Len(v);
	Vec4 vv;

	vv.x = v.x / len;
	vv.y = v.y / len;
	vv.z = v.z / len;
	vv.w = v.w / len;

	return vv;
}

Vec2 mathVec2Rotate(Vec2 v, float angle) {
	Vec2 r;
	float rad = angle * 180.f / PI;
	float c = cos(rad);
	float s = sin(rad);

	r.x = v.x * c - v.y * s;
	r.y = v.x * s + v.y * c;

	return r;
}

Vec3 mathVec3Rotate(Vec3 v, float angle) {
	Vec3 r;
	// TODO: Implement 3D rotation

	r.x = 0;
	r.y = 0;
	r.z = 0;

	return r;
}

Vec2 mathVec2AddV(Vec2 v1, Vec2 v2) {
	Vec2 r;

	r.x = v1.x + v2.x;
	r.y = v1.y + v2.y;

	return r;
}

Vec3 mathVec3AddV(Vec3 v1, Vec3 v2) {
	Vec3 r;

	r.x = v1.x + v2.x;
	r.y = v1.y + v2.y;
	r.z = v1.z + v2.z;

	return r;
}

Vec2 mathVec2AddF(Vec2 v, float n) {
	Vec2 r;

	r.x = v.x + n;
	r.y = v.y + n;

	return r;
}

Vec3 mathVec3AddF(Vec3 v, float n) {
	Vec3 r;

	r.x = v.x + n;
	r.y = v.y + n;
	r.z = v.z + n;

	return r;
}

Vec2 mathVec2SubV(Vec2 v1, Vec2 v2) {
	Vec2 r;

	r.x = v1.x - v2.x;
	r.y = v1.y - v2.y;

	return r;
}

Vec3 mathVec3SubV(Vec3 v1, Vec3 v2) {
	Vec3 r;

	r.x = v1.x - v2.x;
	r.y = v1.y - v2.y;
	r.z = v1.z - v2.z;

	return r;
}

Vec2 mathVec2SubF(Vec2 v, float n) {
	Vec2 r;

	r.x = v.x - n;
	r.y = v.y - n;

	return r;
}

Vec3 mathVec3SubF(Vec3 v, float n) {
	Vec3 r;

	r.x = v.x - n;
	r.y = v.y - n;
	r.z = v.z - n;

	return r;
}

Vec2 mathVec2MulV(Vec2 v1, Vec2 v2) {
	Vec2 r;

	r.x = v1.x * v2.x;
	r.y = v1.y * v2.y;

	return r;
}

Vec3 mathVec3MulV(Vec3 v1, Vec3 v2) {
	Vec3 r;

	r.x = v1.x * v2.x;
	r.y = v1.y * v2.y;
	r.z = v1.z * v2.z;

	return r;
}

Vec2 mathVec2MulF(Vec2 v, float n) {
	Vec2 r;

	r.x = v.x * n;
	r.y = v.y * n;

	return r;
}

Vec3 mathVec3MulF(Vec3 v, float n) {
	Vec3 r;

	r.x = v.x * n;
	r.y = v.y * n;
	r.z = v.z * n;

	return r;
}

Vec2 mathVec2DivV(Vec2 v1, Vec2 v2) {
	Vec2 r;

	r.x = v1.x / v2.x;
	r.y = v1.y / v2.y;

	return r;
}

Vec3 mathVec3DivV(Vec3 v1, Vec3 v2) {
	Vec3 r;

	r.x = v1.x / v2.x;
	r.y = v1.y / v2.y;
	r.z = v1.z / v2.z;

	return r;
}

Vec2 mathVec2DivF(Vec2 v, float n) {
	Vec2 r;

	r.x = v.x / n;
	r.y = v.y / n;

	return r;
}

Vec3 mathVec3DivF(Vec3 v, float n) {
	Vec3 r;

	r.x = v.x / n;
	r.y = v.y / n;
	r.z = v.z / n;

	return r;
}

Mat4 mathMat4Identity(void) {
	Mat4 m = {{0.f}};
	m.m[0][0] = 1;
	m.m[1][1] = 1;
	m.m[2][2] = 1;
	m.m[3][3] = 1;

	return m;
}

Mat4 mathMat4Perspective(float fov, float r, float zNear, float zFar) {
	Mat4 m = mathMat4Identity();
	float f = 1.f / tanf((fov * PI / 180.f) / 2.f);

	m.m[0][0] = f / r;
	m.m[1][1] = f;
	m.m[2][2] = (zFar + zNear) / (zNear - zFar);
	m.m[2][3] = 2 * zFar * zNear / (zNear - zFar);
	m.m[3][2] = -1.f;
	m.m[3][3] = 0.f;

	return m;
}

Mat4 mathMat4LookAt(Vec3 eye, Vec3 center, Vec3 up) {
	Vec3 w = mathVec3Norm(mathVec3SubV(eye, center));
	Vec3 u = mathVec3Norm(mathVec3Cross(up, w));
	Vec3 v = mathVec3Norm(mathVec3Cross(w, u));

	Mat4 m = mathMat4Identity();

	m.m[0][0] = u.x;
	m.m[0][1] = u.y;
	m.m[0][2] = u.z;
	m.m[0][3] = -mathVec3Dot(u, eye);

	m.m[1][0] = v.x;
	m.m[1][1] = v.y;
	m.m[1][2] = v.z;
	m.m[1][3] = -mathVec3Dot(v, eye);

	m.m[2][0] = w.x;
	m.m[2][1] = w.y;
	m.m[2][2] = w.z;
	m.m[2][3] = -mathVec3Dot(w, eye);

	m.m[3][0] = 0.f;
	m.m[3][1] = 0.f;
	m.m[3][2] = 0.f;
	m.m[3][3] = 1.f;

	return m;
}

Mat4 mathMat4Translation(Vec3 v) {
	Mat4 m = mathMat4Identity();

	m.m[0][3] = v.x;
	m.m[1][3] = v.y;
	m.m[2][3] = v.z;

	return m;
}

Mat4 mathMat4Rotation(Vec3 v) {
	Mat4 rx = mathMat4Identity();
	Mat4 ry = mathMat4Identity();
	Mat4 rz = mathMat4Identity();

	float x = v.x * 180.f / PI;
	float y = v.y * 180.f / PI;
	float z = v.z * 180.f / PI;

	rz.m[0][0] = cosf(z);
	rz.m[0][1] = -sinf(z);
	rz.m[1][0] = sinf(z);
	rz.m[1][1] = cosf(z);

	rx.m[1][1] = cosf(x);
	rx.m[2][1] = sinf(x);
	rx.m[1][2] = -sinf(x);
	rx.m[2][2] = cosf(x);

	ry.m[0][0] = cosf(y);
	ry.m[2][0] = sinf(y);
	ry.m[0][2] = -sinf(y);
	ry.m[2][2] = cosf(y);

	return mathMat4MulM(rz, mathMat4MulM(ry, rx));
}

Mat4 mathMat4RotationV(float a, const Vec3 b) {
	Mat4 m;
	float s = sinf(a * PI / 180.f), c = cosf(a * PI / 180.f);
	Vec3 vv = mathVec3Norm(b);

	m.m[0][0] = c + (1.f - c) * vv.x * vv.x;
	m.m[0][1] = (1.f - c) * vv.x * vv.y - s * vv.z;
	m.m[0][2] = (1.f - c) * vv.x * vv.z + s * vv.y;
	m.m[0][3] = 0.f;
	m.m[1][0] = (1.f - c) * vv.x * vv.y + s * vv.z;
	m.m[1][1] = c + (1.f - c) * vv.y * vv.y;
	m.m[1][2] = (1.f - c) * vv.y * vv.z - s * vv.x;
	m.m[1][3] = 0.f;
	m.m[2][0] = (1.f - c) * vv.x * vv.z - s * vv.y;
	m.m[2][1] = (1.f - c) * vv.y * vv.z + s * vv.x;
	m.m[2][2] = c + (1.f - c) * vv.z * vv.z;
	m.m[2][3] = 0.f;
	m.m[3][0] = 0.f;
	m.m[3][1] = 0.f;
	m.m[3][2] = 0.f;
	m.m[3][3] = 1.f;

	return m;
}

Mat4 mathMat4Scale(Vec3 v) {
	Mat4 m = {{0.f}};
	m.m[0][0] = v.x;
	m.m[1][1] = v.y;
	m.m[2][2] = v.z;
	m.m[3][3] = 1;

	return m;
}

Mat4 mathMat4MulM(Mat4 m1, Mat4 m2) {
	Mat4 r = {{0.f}};

	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			r.m[i][j] = m1.m[i][0] * m2.m[0][j] + m1.m[i][1] * m2.m[1][j] + m1.m[i][2] * m2.m[2][j] + m1.m[i][3] * m2.m[3][j];
		}
	}

	return r;
}

Vec4 mathMat4MulV(Mat4 m, Vec4 v) {
	Vec4* mv = (Vec4*)m.m;
	Vec4 r = {0};

	r.x = mathVec4Dot(mv[0], v);
	r.y = mathVec4Dot(mv[1], v);
	r.z = mathVec4Dot(mv[2], v);
	r.w = mathVec4Dot(mv[3], v);

	return r;
}

Transform mathTransform(Vec3 t, Vec3 r, Vec3 s) {
	Transform tr;

	tr.translation = t;
	tr.rotation = r;
	tr.scale = s;

	return tr;
}

Mat4 mathTransformMatrix(Transform tr) {
	Mat4 t = mathMat4Translation(tr.translation);
	Mat4 r = mathMat4Identity(); // TODO: Implement rotation
	Mat4 s = mathMat4Scale(tr.scale);

	return mathMat4MulM(mathMat4MulM(s, r), t);
}
