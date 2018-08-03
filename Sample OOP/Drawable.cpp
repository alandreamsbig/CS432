#include "Drawable.h"

void Drawable::draw()
{}
void Drawable::drawSquare()
{}

int theta = 0;
void Drawable::rotation()
{
	theta++;
	if (theta > 360)
		theta = 0;

	mat3 t1(vec3(1, 0, -mouseX), vec3(0, 1, -mouseY), vec3(0, 0, 1));
	float rad = theta * 2 * 3.14 / 360;
	mat3 r(vec3(cos(rad), -sin(rad), 0), vec3(sin(rad), cos(rad), 0), vec3(0, 0, 1));
	mat3 t2(vec3(1, 0, mouseX), vec3(0, 1, mouseY), vec3(0, 0, 1));
	setModelMatrix(t2*r);
}

void Drawable::mouseLocation(float x, float y)
{
	mouseX = x;
	mouseY = y;
}