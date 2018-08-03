#pragma once

#include "Angel.h"


class Camera
{
public:

	//constructor
	Camera();

	//destructor
	~Camera();

	void printCamera();
	vec4 getV();

	//Camera position
	Camera(vec4 eyeI, vec4 nI, vec4 upI);

	//static camera
	void setStatic(bool in);

	//create camera view matrix
	void createViewMatrix();
	

	int xBoundLower = -150;
	int yBoundLower = 0;
	int zBoundLower = -150;
	int xBoundUpper = 150;
	int yBoundUpper = 50;
	int zBoundUpper = 150;


	void toggleProjectionType();

	vec4 getViewPerspecPoint(double x, double y);

	vec4 getClickedPointRay(double x, double y);

	void setBounds(vec2 x, vec2 y, vec2 z);

	bool checkInside(vec4 eyeLocation);

	bool isInside(vec4 eyeLocation);

	mat4 view_matrix;
	mat4 projection_matrix;
	mat4 inverseProjection_matrix;
	bool isPerspective = false;

	//camera size
	double width = 500;
	double height = 500;

	void updateWindow(int inputW, int inputH)
	{
		width = inputW;
		height = inputH;
		createViewMatrix();
		getProjectionMatrix();
	}

	vec4 eye, at, up;
	vec4 u, v, n;

	double nearP = 1.0;
	double farP = 350.0;
	double t, rP;

	bool isStatic = false;

	mat4 getProjectionMatrix();
	mat4 getProjectionMatrixInverse();

	mat4 getViewMatrix();

	//Camera move functions
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

	void setN(vec4 newN);


};

