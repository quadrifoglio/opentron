#pragma once

#define PI 3.14159265f

/*
 * Two-dimensional vector
 */
typedef struct {
	float x, y;
} Vec2;

/*
 * Three-dimensional vector
 */
typedef struct {
	float x, y, z;
} Vec3;

/*
 * Four-dimensional vector
 */
typedef struct {
	float x, y, z, w;
} Vec4;

/*
 * Quaternion
 */
typedef struct {
	float x, y, z, w;
} Quat;

/*
 * 4x4 square matrix
 */
typedef struct {
	float m[4][4];
} Mat4;

/*
 * Transform (translation, rotation, scaling)
 */
typedef struct {
	Vec3 translation;
	Vec3 rotation;
	Vec3 scale;
} Transform;

/*
 * Vector length
 */
float mathVec2Len(Vec2 v);
float mathVec3Len(Vec3 v);
float mathVec4Len(Vec4 v);

/*
 * Vector dot product
 */
float mathVec2Dot(Vec2 v1, Vec2 v2);
float mathVec3Dot(Vec3 v1, Vec3 v2);

/*
 * Vector cross product
 */
Vec3 mathVec3Cross(Vec3 v1, Vec3 v2);

/*
 * Vector normalization
 */
Vec2 mathVec2Norm(Vec2 v);
Vec3 mathVec3Norm(Vec3 v);
Vec4 mathVec4Norm(Vec4 v);

/*
 * Vector rotation
 */
Vec2 mathVec2Rotate(Vec2 v, float angle);
Vec3 mathVec3Rotate(Vec3 v, float angle);

/*
 * Vector addition
 */
Vec2 mathVec2AddV(Vec2 v1, Vec2 v2);
Vec3 mathVec3AddV(Vec3 v1, Vec3 v2);
Vec4 mathVec4AddV(Vec4 v1, Vec4 v2);

Vec2 mathVec2AddF(Vec2 v, float n);
Vec3 mathVec3AddF(Vec3 v, float n);
Vec4 mathVec4AddF(Vec4 v, float n);

/*
 * Vector substration
 */
Vec2 mathVec2SubV(Vec2 v1, Vec2 v2);
Vec3 mathVec3SubV(Vec3 v1, Vec3 v2);
Vec4 mathVec4SubV(Vec4 v1, Vec4 v2);

Vec2 mathVec2SubF(Vec2 v, float n);
Vec3 mathVec3SubF(Vec3 v, float n);
Vec4 mathVec4SubF(Vec4 v, float n);

/*
 * Vector multiplication
 */
Vec2 mathVec2MulV(Vec2 v1, Vec2 v2);
Vec3 mathVec3MulV(Vec3 v1, Vec3 v2);
Vec4 mathVec4MulV(Vec4 v1, Vec4 v2);

Vec2 mathVec2MulF(Vec2 v, float n);
Vec3 mathVec3MulF(Vec3 v, float n);
Vec4 mathVec4MulF(Vec4 v, float n);

/*
 * Vector division
 */
Vec2 mathVec2DivV(Vec2 v1, Vec2 v2);
Vec3 mathVec3DivV(Vec3 v1, Vec3 v2);
Vec4 mathVec4DivV(Vec4 v1, Vec4 v2);

Vec2 mathVec2DivF(Vec2 v, float n);
Vec3 mathVec3DivF(Vec3 v, float n);
Vec4 mathVec4DivF(Vec4 v, float n);

/*
 * Quaternion operations
 */
float mathQuatLen(Quat q);
Quat mathQuatNorm(Quat q);
Quat mathQuatMulQ(Quat q1, Quat q2);
Quat mathQuatMulV(Quat q, Vec3 v);

/*
 * Matrice initialization
 */
Mat4 mathMat4Identity(void);
Mat4 mathMat4Perspective(float fov, float w, float h, float zNear, float zFar);
Mat4 mathMat4Translation(Vec3 v);
Mat4 mathMat4Rotation(Vec3 v);
Mat4 mathMat4Scale(Vec3 v);
Mat4 mathMat4Mul(Mat4 m1, Mat4 m2);

/*
 * Transform functionality
 */
Transform mathTransform(Vec3 t, Vec3 r, Vec3 s);
Mat4 mathTransformMatrix(Transform* t);
