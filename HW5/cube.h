#ifndef  __CUBE_H__
#define __CUBE_H__
#include "Drawable.h"
#include "Angel.h"
#include "Camera.h"
#include "Light.h"

class cube :Drawable {

public:
	cube();
	void drawCube(Camera*, vector<Light>);
	void setMaterial(vec4, vec4, vec4, float);
	~cube();

private:
	
	static const unsigned int numVertices = 3072;

	
	void build();
	void buildCube();
	void makeQuad(int a, int b, int c, int d);

	//Data for Cube object
	const int NumCubeVertices = 6 * 2 * 3;
	int currentCubeIndex = 0;
	vec4 cubeVertexLocations[6 * 2 * 3];
	vec4 cubeVertexColors[6 * 2 * 3];
	#define SQUARE_BUFFER 0
	
	float shine;
	GLuint vpos, npos, mmpos, vmpos, pmpos, diffuse_loc, spec_loc, ambient_loc, alpha_loc;
	vec4 diffuse, specular, ambient;


};
#endif // ! __SPHERE_H__
