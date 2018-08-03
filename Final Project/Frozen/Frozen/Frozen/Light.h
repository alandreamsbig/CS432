#pragma once
#include "Angel.h";

class Light
{
	public:

		//get and set for light properties
		Light():position(vec4(0,0,0,1)), ambient(vec4(1.0,1.0,1.0,1.0)), specular(vec4(1.0, 1.0, 1.0, 1.0)), diffuse(vec4(1.0, 1.0, 1.0, 1.0)), enabled(1) {};
		Light(vec4 p, vec4 a, vec4 s, vec4 d) : position(p), ambient(a), specular(s), diffuse(d), enabled(1) {};
		vec4 getPosition() { return position; }
		vec4 getAmbient() { return ambient; }
		vec4 getDiffuse() { return diffuse; }
		vec4 getSpecular() { return specular; }
		int getEnabled() { return enabled; }
		vec4 position;
		vec4 ambient;
		vec4 diffuse;
		int enabled = 1;
		vec4 specular;
		void setPosition(vec4 pos) { position = pos; }
		void toggle() {
			if (enabled) 
			{ 
				enabled = 0;

			}
			else { 
				enabled = 1; 
			}
		}
		void printLight();

		//destructor
		~Light();
};

