#include "Shape.h"

Shape::Shape(float normalizedX, float normalizedY) {
	//load the shader and get the location of it's variables
	program = InitShader("vshader00_v150.glsl", "fshader00_v150.glsl");
	buildTriangle();
	modelmatrix = mat3(1.0, 0, 0, 0, 1, 0, normalizedX, normalizedY, 1);
	mouseLocation(normalizedX, normalizedY);
	build();
}

void Shape::build() {
	/*
	theta++;
	if (theta > 360)
	theta = 0;
	float rad = theta * 2 * 3.14 / 360;
	float s = sin(rad);
	float c = cos(rad);

	mat3 rot(c, s, 0, -s, c, 0, 0, 1);

	for (int i = 0; i < 3; i++)
	{
	vertexLocation[i] = rot*vertexLocation[i];
	}
	*/
	
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);


	glUseProgram(program);
	//buildTriangle(normalizedX, normalizedY);  //build the triangle (set the vertex locations and normals)
		

	///move the data onto the buffer
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexLocations), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertexLocations), vertexLocations);
	

	//link the vertex attributes with the buffer
	GLuint vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));


	//glutTimerFunc(interval, timerCallback, value);
	//glutPostRedispla();
}

//on destroy, delete the buffer (cleanup)
Shape::~Shape() {
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);

}


void Shape::buildTriangle() {
	//set up the vertices
	vertexLocations[0] = vec3(-0.1, -0.1, 1);
	vertexLocations[1] = vec3(0.3, -0.1, 1);
	vertexLocations[2] = vec3(-0.1, 0.3, 1);
}

int a = 0;
void Shape::draw() {
	a += 45;
	if (a > 360)
		a = 0;
	glBindVertexArray(VAO);
	glUseProgram(program);

	//set the transformation matrices
	GLuint model_loc = glGetUniformLocation(program, "model_matrix");
	glUniformMatrix3fv(model_loc, 1, GL_TRUE, modelmatrix);

	GLuint vColor = glGetUniformLocation(program, "color");
	glUniform4fv(vColor, 1, vec4(1 * a / 360, 0, 0, 1));

	//draw!
	glDrawArrays(GL_TRIANGLES, 0, 3);

}

