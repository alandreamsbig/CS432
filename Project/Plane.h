#pragma once
#include "Drawable.h"
class Plane :
	public Drawable
{
public:
	Plane();
	void setTexture(std::string textureName);
	~Plane();


	void updateViewMatrix(mat4 newViewMatrix);

	void draw();
		
	void createTriangle(vec4 a, vec4 b, vec4 c);

	vec4 getCenter(vec4 p1, vec4 p3);

	void makeQuad(vec4 a, vec4 b, vec4 c, vec4 d);

	void divideSquare(vec4 a, vec4 b, vec4 c, vec4 d, int count);

	void updateModelMatrix(mat4 newViewMatrix);

	int numDivisions = 3;
	const int numVertices = 3 * pow(2, (2 * numDivisions) + 1);
	vec4 vertexColors[24576];
	vec4 vertexLocations[24576];
	vec3 vertexNormals[24576];

	vec2 vertexTextureLocations[24576];
	std::string currentTextureName = "grass.ppm";


	int index = 0;
	GLuint modelMatrix_loc, viewMatrix_loc, projectionMatrix_loc;
	GLuint vPosition_loc;
	GLuint vColor_loc;
	GLuint uniformColorLoc;
	GLuint buffer;
	GLuint program;
	GLuint texture;

	mat4 model_matrix;
	
};

