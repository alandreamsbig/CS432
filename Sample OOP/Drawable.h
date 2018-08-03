#ifndef __DRAWABLE_H__
#define __DRAWABLE_H__
#include "Angel.h"
#include <vector>

using namespace std;

class Drawable {
protected:
	GLuint program;
	GLuint VAO;
	GLuint VBO;
	GLuint sVAO;
	GLuint sVBO;

	


public:
	virtual void draw();
	virtual void drawSquare();
	void rotation();
	float mouseX, mouseY;
	void mouseLocation(float x, float y);
	mat3 modelmatrix;
	void setModelMatrix(mat3 mm) { modelmatrix = mm; }
};

#endif
