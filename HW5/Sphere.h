#ifndef  __SPHERE_H__
#define __SPHERE_H__
#include "Drawable.h"
#include "Angel.h"
#include "Camera.h"
#include "Light.h"

class Sphere :Drawable {

public:
	Sphere();
	void drawSphere(Camera*, vector<Light>);
	void setMaterial(vec4, vec4, vec4, float);
	void drawSquare();
	~Sphere();

private:
	
	static const unsigned int numVertices = 3072;

	
	void build();
	void plane();
	unsigned int index;
	GLuint vpos, npos, mmpos, vmpos, pmpos, diffuse_loc, spec_loc, ambient_loc, alpha_loc;
	vec4 diffuse, specular, ambient;

	vec4 vertexLocations[numVertices];
	vec3 vertexNormals[numVertices];
	//vec4 vertexColors[numVertices];
	
	float shine;
	float sqrt2, sqrt6;
	void assignGouradVertices();
	void tetrahedron(int);
	void divideTriangle(vec4, vec4, vec4, int);
	void triangle(vec4, vec4, vec4);
	void buildSquare();

	vec4 unit(vec4);


};
#endif // ! __SPHERE_H__
