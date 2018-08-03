#pragma once
#include "Angel.h"


class Triangle
{
public:
	Triangle();
	Triangle(vec4 p1, vec4 p2, vec4 p3);
	void setRayAndOrigin(vec4 rayOI, vec4 rayI);
	void print();
	vec4 * getPoints();
	~Triangle();

	vec4 getNormal();

	bool collisionWithPlane(double & tI);

	bool isInside();

	vec4 point1, point2, point3;

	vec4 rayOrigin, ray;
	
	vec4 intersectionPoint;
};

