#include "Triangle.h"


//triangle constructor
Triangle::Triangle()
{
}

Triangle::Triangle(vec4 p1, vec4 p2, vec4 p3)
{
	point1 = p1;
	point2 = p2;
	point3 = p3;
}

//set triangle ray and origin
void Triangle::setRayAndOrigin(vec4 rayOI, vec4 rayI)
{
	rayOrigin = rayOI;
	ray = rayI;
}

void Triangle::print()
{

	std::cout << point1 << "\n" << point2 << "\n" << point3 << std::endl;

}


//triangle destructor
Triangle::~Triangle()
{
}

vec4 Triangle::getNormal()
{
	vec3 p1 = normalize(vec3(point2[0], point2[1], point2[2]) - vec3(point1[0], point1[1], point1[2]));
	vec3 p2 = normalize(vec3(point3[0], point3[1], point3[2]) - vec3(point1[0], point1[1], point1[2]));


	vec3 newP = cross(p1, p2);
	newP = normalize(newP);
	vec4 ret = vec4(newP[0], newP[1], newP[2], 0.0);
	return ret;
}

//check if the triangle is colliding with the plane
bool Triangle::collisionWithPlane(double & tI)
{
	double d = -1 * dot(vec3(point1[0], point1[1], point1[2]), vec3(getNormal()[0], getNormal()[1], getNormal()[2]));
	double num = (dot(getNormal(), vec3( rayOrigin[0], rayOrigin[1], rayOrigin[2])) + d);
	double denom = dot(getNormal(), vec3(ray[0], ray[1], ray[2]));
	
	if (denom == 0)
	{
		//std::cout << "0 denom\n";
		return false;
	}
	if (isnan(d))
	{

	}

	double t = -1.0 * ( num / denom );
	if (t < 0)
	{
		//std::cout << "ttt: " << t << std::endl;
		return false;
	}


	//std::cout << "tHere: " << t << std::endl;
	intersectionPoint = rayOrigin + t*ray;
	//std::cout << "intPoint: " << intersectionPoint << std::endl;
	//std::cout << "rayOrigin + t*ray    " << rayOrigin << " + " << t << "*" << ray << std::endl;

	if (isInside())
	{
		tI = t;
		//std::cout << "\ntInsideee: " << tI << " t: " << t << std::endl << std::endl;

		//std::cout << "intPoint: " << intersectionPoint << std::endl;
		return true;
	}
	else
	{
		//std::cout << "outside" << std::endl;
		return false;
	}
	//std::cout << "intersection Point: " << intersectionPoint << std::endl;

	
	return true;
}

//check if the triangle is inside or outside
bool Triangle::isInside()
{
	double dotP, dotP2, dotP3;
	vec3 p1(point1[0], point1[1], point1[2]);
	vec3 p2(point2[0], point2[1], point2[2]);
	vec3 p3(point3[0], point3[1], point3[2]);
	vec3 intPoint(intersectionPoint[0], intersectionPoint[1], intersectionPoint[2]);

	vec3 vec1 = cross(p2 - p1, intPoint - p1);
	dotP = dot(getNormal(), vec1);

	vec3 vec2 = cross(p3 - p2, intPoint - p2);
	dotP2 = dot(getNormal(), vec2);

	vec3 veC3 = cross(p1 - p3, intPoint - p3);
	dotP3 = dot(getNormal(), veC3);

	/*
	std::cout << "points\n" << p1 << "\n" << p2 << "\n" << p3 << std::endl;

	std::cout << "vecs:\n" << vec1 << "\n" << vec2 << "\n" << veC3 << std::endl;

	std::cout << "dot products: " << dotP << " " << dotP2 << " " << dotP3 << std::endl;

	*/

	if (dotP < 0 || dotP2 < 0 || dotP3 < 0)
	{
		return false;
	}

	return true;
}