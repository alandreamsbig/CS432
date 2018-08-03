#pragma once
#include "Cube.h"
class CubeMap : //derived from cube class
	public Cube
{
public:

	//constructor
	CubeMap();
	void updateViewMatrix(mat4 newViewMatrix);

	//destructor
	~CubeMap();
	

	void draw();

	GLuint modelMatrix_loc, viewMatrix_loc, projectionMatrix_loc;
	mat4 model_matrix;

	GLuint vPosition_loc;

	GLuint modelviewMatrix_loc;

	vec4 currNormal, currV;
	mat4 model_view;

	GLubyte  *skyTop, *skyBottom, *skyRight, *skyLeft, *skyFront, *skyBack;
};

