#pragma once

#include "Angel.h"


class Camera
{
public:
	Camera();
	void printCamera();
	vec4 getV();
	Camera(vec4 eyeI, vec4 nI, vec4 upI);
	void setStatic(bool in);
	void createViewMatrix();
	~Camera();

	void toggleProjectionType();

	vec4 getViewPerspecPoint(double x, double y);

	vec4 getClickedPointRay(double x, double y);

	mat4 view_matrix;
	mat4 projection_matrix;
	mat4 inverseProjection_matrix;
	bool isPerspective = false;

	double width = 500;
	double height = 500;

	vec4 eye, at, up;
	vec4 u, v, n;

	double nearP, farP, t, rP;

	bool isStatic = false;

	mat4 getProjectionMatrix();
	mat4 getProjectionMatrixInverse();

	mat4 getViewMatrix();
	void moveRight();
	void moveLeft();
	void moveForward();
	void moveBackward();
	void setEye(vec4 eyeInput);
	vec4 getEye();
	vec4 getN();
	vec4 getAt();
	void rotateU(double theta);
	void rotateV(double theta);
	void rotateN(double theta);
	mat4 invert(mat4 m1);
	double determinant(mat4 m);
	void setu(vec4 eyeInput);
	void setv(vec4 vInput);
	void setn(vec4 nInput);



};

