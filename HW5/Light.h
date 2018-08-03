#ifndef __LIGHT_H__
#define __LIGHT_H__
#include "Angel.h"

class Light {
public:
	Light() {};
	Light(vec4 p, vec4 a, vec4 s, vec4 d) : position(p), ambient(a), specular(s), diffuse(d) {}	
	vec4 getPosition() { return position; }
	vec4 getAmbient() { return ambient; }
	vec4 getDiffuse() { return diffuse; }
	vec4 getSpecular() { return specular; }
	vec4 getDirection() { return direction; }
	float getAlpha() { return alpha; }
	int getType() { return type; }
	void setDirection(vec4 d) { direction = d; }
	void setAlpha(float a) { alpha = a; }
	void setType(int t) { type = t; }
	void setCutoff(float c) { cutoff = c; }
	float getCutoff() { return cutoff; }
	void turnOn() { active = true; }
	void turnOff() { active = false; }
	bool isActive() { return active; }
	void setPosition(vec4 p) { position = p; }
private:
	vec4 position;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec4 direction;
	float alpha;
	int type;		//0 distance, 1 point, 2, spotlight
	bool active;
	float cutoff;
};


#endif
