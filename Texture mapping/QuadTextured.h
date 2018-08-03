#ifndef __QUADTEXTURED_H__
#define __QUADTEXTURED_H__

#include "Angel.h"
#include "Drawable.h"
#include "Light.h"
#include "Camera.h"
#include <vector>

class QuadTextured: public Drawable{  //derived from drawable class


public:	

	//constructors
	QuadTextured();

	//destructor
	~QuadTextured();

	void build();
	void draw(Camera, vector<Light>);
	void setMaterial(vec4, vec4, vec4, float);

private:
	GLuint texture;

	vec4 vertexLocations[6];
	vec3 vertexNormals[6];
	vec2 vertexTextureLocations[6];

	void makeQuad(vec4, vec4, vec4, vec4);

	unsigned int index;
	

	//materials will be instantiatable
	vec4 matDiffuse, matSpecular, matAmbient;
	float shininess;
	

};
#endif
