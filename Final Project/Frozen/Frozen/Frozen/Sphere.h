#pragma once
#include "Drawable.h"
#include "Camera.h";
#include "Triangle.h";
#include "Light.h";

class Sphere : //derived from drawable class
	public Drawable
{
public:
	void cleanup();

	//constructor
	Sphere();

	//destructor
	~Sphere();

	void draw();
	void printPoints();
	mat4 getModelMatrix();

	void applyTransformation(mat4 trans);

	void setNormal(vec4 normal);

	//rotate sphere
	void rotateX(double theta);
	void rotateY(double theta);
	void rotateZ(double theta);

	GLuint modelMatrix_loc, viewMatrix_loc, projectionMatrix_loc;
	GLuint vPosition_loc;
	GLuint buffer;

	//create sphere
	void makeSphere();

	void tetrahedron(int count);

	void divideTriangle(vec4 a, vec4 b, vec4 c, int count);

	vec4 unit(vec4 p);

	vec2 getTextureLocation(vec3 point);

	void triangle(vec4 a, vec4 b, vec4 c);

	void createVertices();

	bool processClick(vec4 rayOrigin, vec4 ray);

	vec4 vertexLocations[32768*8];
	vec3 vertexNormals[32768 * 8];
	vec2 vertexTextureLocations[32768 * 8];

	int numDivisions = 8;
	int temp = pow(4, numDivisions + 1);

	void updateViewMatrix(mat4 newViewMatrix);

	void setModelMatrix(mat4 newMM);
	
	std::string currentTextureName = "snowman.ppm"; //"face.ppm";
	
	//set sphere texture
	void setTexture(std::string textureName);

	vec4 p = vec4(-5, -5, -10, 1);
	vec4 a = vec4(1.0, 0, 1, 1);
	vec4 s = vec4(1.0, 0, 1, 1);
	vec4 d = vec4(1.0, 0, 1, 1);
	

	GLuint texture;

	void headanimation();
	bool fixHeight();
	unsigned int index = 0;

	mat4 model_matrix;

	vec4 currNormal;

	bool activated = true;
	bool getActivated();
	void deactivate();
	
};

