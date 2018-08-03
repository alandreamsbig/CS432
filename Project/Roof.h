#pragma once
#include "Drawable.h"
class Roof :
	public Drawable
{
public:
	void build();
	void makeTriangle(int a, int b, int c);
	Roof();
	void updateViewMatrix(mat4 newViewMatrix);
	void draw();
	vec4 vertexLocations[36];
	vec3 vertexNormals[36];
	vec2 vertexTextureLocations[36];
	int currentCubeIndex = 0;

	GLuint modelMatrix_loc, viewMatrix_loc, projectionMatrix_loc, vPosition_loc;
	vec4 currNormal;
	mat4 model_matrix;
	GLuint buffer;
	GLuint texture;
	std::string currentTextureName = "roof.ppm";


	~Roof();
};

