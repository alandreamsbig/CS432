#pragma once
#include "Drawable.h"
#include "Camera.h";
#include "Triangle.h";
#include "Light.h";

class Sphere :
	public Drawable
{
public:
	Sphere();

	
	~Sphere();

	void draw();
	void printPoints();
	mat4 getModelMatrix();

	void applyTransformation(mat4 trans);

	void setNormal(vec4 normal);

	void rotateX(double theta);
	void rotateY(double theta);
	void rotateZ(double theta);

	GLuint modelMatrix_loc, viewMatrix_loc, projectionMatrix_loc;
	GLuint vPosition_loc;
	GLuint buffer;

	void makeSphere();

	void tetrahedron(int count);

	void divideTriangle(vec4 a, vec4 b, vec4 c, int count);

	vec4 unit(vec4 p);

	void triangle(vec4 a, vec4 b, vec4 c);

	vec4 vertexLocations[786432];
	vec3 vertexNormals[786432];

	int numDivisions = 8;
	int temp = pow(4, numDivisions + 1);

	void updateViewMatrix(mat4 newViewMatrix);

	void setModelMatrix(mat4 newMM);

	unsigned int index = 0;

	mat4 model_matrix;

	vec4 currNormal;
	
};

