#pragma once
#include "Drawable.h"
#include "Camera.h";
#include "Triangle.h";

class SphereOld :
	public Drawable
{
public:
	SphereOld();
	~SphereOld();
	int curr = 0;

	void draw();
	void printPoints();
	mat4 getModelMatrix();

	std::vector<Triangle> getTriangles();

	double getT(vec4 rayOrigin, vec4 ray);

	void setModelMatrix(mat4 newMM);

	bool processClick(vec4 rayOrigin, vec4 ray);
	void printViewMatrix();

	void rotateX(double theta);
	void rotateY(double theta);
	void rotateZ(double theta);

	void updateViewMatrix(mat4 newViewMatrix);

	GLuint modelMatrix_loc, viewMatrix_loc, projectionMatrix_loc;
	GLuint vPosition_loc;
	GLuint vColor_loc;
	GLuint uniformColorLoc;
	GLuint buffer;


	std::string currentTextureName = "snowman.ppm"; 
	GLuint texture;



	mat4 model_matrix;
	
	void makeSphereOld();

	void tetrahedron(int count);

	void divideTriangle(vec4 a, vec4 b, vec4 c, int count);

	vec4 unit(vec4 p);

	vec2 getTextureLocation(vec3 point);

	void triangle(vec4 a, vec4 b, vec4 c);

	vec4 vertexLocations[3072];
	vec4 vertexNormals[3072];
	vec2 vertexTextureLocations[3072];

	int numDivisions = 4;
	int temp = pow(4, numDivisions + 1);

	unsigned int index = 0;
};

