#pragma once
#include "Drawable.h"
#include "Light.h"
#include <string>;

class Cube :
	public Drawable
{
public:
	void makeQuad(int a, int b, int c, int d);
	void triangle(vec4 a, vec4 b, vec4 c);
	void buildCube();

	void updateModelMatrix(mat4 newModelMatrix);

	Cube();
	~Cube();

	void transformModelMatrix(mat4 newMM);
	void draw();

	vec4 * getPoints();

	void setNormal(vec4 normal);


	GLuint modelMatrix_loc, viewMatrix_loc, projectionMatrix_loc, vPosition_loc;
	vec4 currNormal;
	mat4 model_matrix;
	GLuint buffer;
	GLuint texture;
	std::string currentTextureName = "crate1.ppm";

	vec4 vertexLocations[36];
	vec3 vertexNormals[36];
	vec2 vertexTextureLocations[36];

	int numDivisions = 3;
	int temp = pow(4, numDivisions + 1);

	unsigned int index = 0;



	void setTexture(std::string textureName);

	vec4 p = vec4(-5, -5, -10, 1);
	vec4 a = vec4(1.0, 0, 1, 1);
	vec4 s = vec4(1.0, 0, 1, 1);
	vec4 d = vec4(1.0, 0, 1, 1);


	
	
	void updateViewMatrix(mat4 newViewMatrix);

	int currentCubeIndex = 0;

	int triNumDivisions = 1;


};

