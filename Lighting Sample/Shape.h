#ifndef __SHAPE_H__
#define __SHAPE_H__

#include "Angel.h"
#include "Drawable.h"

class Shape: public Drawable{  //derived from drawable class


public:	

	//constructors
	Shape();
	
	//destructor
	~Shape();

	void build();
	void draw(Camera, vector<Light>);
	void setMaterial(vec4, vec4, vec4, float);

private:
	vec4 vertexLocations[3];
	vec3 vertexNormals[3];
		
	void buildTriangle();

	//materials
	vec4 matDiffuse, matSpecular, matAmbient;
	float shininess;
	

};
#endif
