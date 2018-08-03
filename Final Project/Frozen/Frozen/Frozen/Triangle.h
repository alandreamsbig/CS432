#pragma once
#include "Angel.h"


class Triangle
{
public:

	//constructor
	Triangle();


	Triangle(vec4 p1, vec4 p2, vec4 p3);
	void setRayAndOrigin(vec4 rayOI, vec4 rayI);
	void print();
	vec4 * getPoints();

	//destructor
	~Triangle();

	vec4 getNormal();

	//detect collision with plane
	bool collisionWithPlane(double & tI);

	//detect inside or outside of triangle
	bool isInside();

	vec4 point1, point2, point3;

	vec4 rayOrigin, ray;
	
	vec4 intersectionPoint;
};

