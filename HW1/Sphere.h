#ifndef  __SPHERE_H__
#define __SPHERE_H__
#include "Drawable.h"
#include "Angel.h"
#include "Camera.h"

class Sphere:Drawable {

public:
	Sphere();
	void drawSphere(Camera*);
	void drawSquare();
	~Sphere();

private:
	static const unsigned int numVertices = 3072;



	void build();
	void plane();
	unsigned int index;
	GLuint vpos, cpos, mmpos, vmpos, pmpos;

	vec4 vertexLocations[numVertices];
	vec4 vertexColors[numVertices];
	float sqrt2, sqrt6;
	void tetrahedron(int);
	void divideTriangle(vec4, vec4, vec4, int);
	void triangle(vec4, vec4, vec4);
	void buildSquare();
	
	vec4 unit(vec4);


};
#endif // ! __SPHERE_H__
