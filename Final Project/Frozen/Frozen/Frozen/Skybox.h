#pragma once
#include "Cube.h"
class Skybox : //derived from cube class
	public Cube
{
public:
	void cleanup();
	Skybox(); //constructor
	~Skybox(); //destructor

	void setNormal(vec4 nI);
	void setV(vec4 vI);
	

	void draw();

	GLuint modelviewMatrix_loc;

	vec4 currNormal, currV;
	mat4 model_view;

	GLubyte  *skyTop, *skyBottom, *skyRight, *skyLeft, *skyFront, *skyBack;
};

