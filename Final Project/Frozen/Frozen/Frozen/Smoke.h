#pragma once
#include "Drawable.h"

struct particle {
	vec4 color;
	vec4 position;
	vec4 velocity;
	double steps;
	double stepMax;
};

class Smoke : //derived from drawable class
	public Drawable
{
public:
	void cleanup();
	void initParticles();
	void applyTransformation(mat4 trans);
	void initColors();

	//constructor
	Smoke();
	void draw();

	//destructor
	~Smoke();

	GLuint modelMatrix_loc, viewMatrix_loc, projectionMatrix_loc;
	GLuint vPosition_loc;
	GLuint vColor_loc;
	GLuint buffer;
	mat4 model_matrix;

	particle* getParticles() { return particles; }

	//particle properties
	particle particles[4096 * 4];
	vec4 particlePoints[4096 * 4];
	vec4 particleColors[4096 * 4];

	int numSmokeParticles = 4096 * 4;
};

