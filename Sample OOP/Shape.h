#ifndef __SHAPE_H__
#define __SHAPE_H__

#include "Angel.h"
#include "Drawable.h"

class Shape : public Drawable {  //derived from drawable class


public:

	//constructors
	Shape(float normalizedX, float normalizedY);


	//destructor
	~Shape();

	void build();
	
	void draw();
	void buildTriangle();

private:
	vec3 vertexLocations[3];
	


};
#endif
