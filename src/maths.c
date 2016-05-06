#include "maths.h"
#include <math.h>

float mathVec2Len(Vec2 v) {
	return (float)sqrt(v.x * v.x + v.y * v.y);
}

float mathVec3Len(Vec3 v) {
	return (float)sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

float mathVec4Len(Vec4 v) {
	return (float)sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
}

float mathVec2Dot(Vec2 v1, Vec2 v2) {
	return v1.x * v2.x + v1.y * v2.y;
}

float mathVec3Dot(Vec3 v1, Vec3 v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
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

float mathQuatLen(Quat q) {
	return (float)sqrt(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
}

Quat mathQuatNorm(Quat q) {
	float len = mathQuatLen(q);
	Quat qq;

	qq.x = q.x / len;
	qq.y = q.y / len;
	qq.z = q.z / len;
	qq.w = q.w / len;

	return qq;
}

Quat mathQuatMulQ(Quat q1, Quat q2) {
	Quat r;

	r.w = q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z;
	r.x = q1.x * q2.w + q1.w * q2.x + q1.y * q2.z - q1.z * q2.y;
	r.y = q1.y * q2.w + q1.w * q2.y + q1.z * q2.x - q1.x * q2.z;
	r.z = q1.z * q2.w + q1.w * q2.z + q1.x * q2.y - q1.y * q2.x;

	return r;
}

Quat mathQuatMulV(Quat q, Vec3 v) {
	Quat r;

	r.w = -q.x * v.x - q.y * v.y - q.z * v.z;
	r.x =  q.w * v.x + q.y * v.z - q.z * v.y;
	r.y =  q.w * v.y + q.z * v.x - q.x * v.z;
	r.z =  q.w * v.z + q.x * v.y - q.y * v.x;

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

	return mathMat4Mul(rz, mathMat4Mul(ry, rx));
}

Mat4 mathMat4Scale(Vec3 v) {
	Mat4 m = {{0.f}};
	m.m[0][0] = v.x;
	m.m[1][1] = v.y;
	m.m[2][2] = v.z;
	m.m[3][3] = 1;

	return m;
}

Mat4 mathMat4Mul(Mat4 m1, Mat4 m2) {
	Mat4 r = {{0.f}};

	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			r.m[i][j] = m1.m[i][0] * m2.m[0][j] + m1.m[i][1] * m2.m[1][j] + m1.m[i][2] * m2.m[2][j] + m1.m[i][3] * m2.m[3][j];
		}
	}

	return r;
}

Transform mathTransform(Vec3 t, Vec3 r, Vec3 s) {
	Transform tr;

	tr.translation = t;
	tr.rotation = r;
	tr.scale = s;

	return tr;
}

Mat4 mathTransformMatrix(Transform* tr) {
	Mat4 t = mathMat4Translation(tr->translation);
	Mat4 r = mathMat4Rotation(tr->rotation);
	Mat4 s = mathMat4Scale(tr->scale);

	return mathMat4Mul(t, mathMat4Mul(r, s));
}
