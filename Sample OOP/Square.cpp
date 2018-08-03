#include "Square.h"

Square::Square(float rnormalizedX, float rnormalizedY) {
	//load the shader and get the location of it's variables
	program = InitShader("vshader00_v150.glsl", "fshader00_v150.glsl");
	mouseLocation(rnormalizedX, rnormalizedY);
	buildSquare();
	modelmatrix = mat3(1.0, 0, 0, 0, 1, 0, rnormalizedX, rnormalizedY, 1);
	builds();
}

void Square::builds() {

	glGenVertexArrays(1, &sVAO);
	glGenBuffers(1, &sVBO);
	

	glUseProgram(program);
	//buildTriangle();  //build the triangle (set the vertex locations and normals)
	

	glBindVertexArray(sVAO);
	glBindBuffer(GL_ARRAY_BUFFER, sVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(squareLocations), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(squareLocations), squareLocations);



	GLuint sPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(sPosition);
	glVertexAttribPointer(sPosition, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));


}

//on destroy, delete the buffer (cleanup)
Square::~Square() {

	glDeleteBuffers(1, &sVBO);
	glDeleteVertexArrays(1, &sVAO);

}


void Square::buildSquare() {
	squareLocations[0] = vec3(-0.2, -0.2, 1);
	squareLocations[1] = vec3(0.2, -0.2, 1);
	squareLocations[2] = vec3(0.2, 0.2, 1);
	squareLocations[3] = vec3(-0.2, 0.2, 1);
}


int angle = 0;
void Square::drawSquare() {

	angle += 45;
	if (angle > 360)
		angle = 0;

	glBindVertexArray(sVAO);
	glUseProgram(program);

	//set the transformation matrices
	GLuint model = glGetUniformLocation(program, "model_matrix");
	GLuint sColor = glGetUniformLocation(program, "color");
	glUniform4fv(sColor, 1, vec4(1*angle/360, 0, 1, 1));
	glUniformMatrix3fv(model, 1, GL_TRUE, modelmatrix);


	//glUniform4fv(sColor, 1, vec4(1, 0, 1, 1));

	//draw!
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

}

