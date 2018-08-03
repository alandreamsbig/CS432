#include"Sphere.h"
#include"math.h"
#include"Camera.h"

//uniform variable locations
GLuint modelMatrix_loc;
GLuint viewMatrix_loc;

//attribute variable locations
GLuint vPosition_loc;
GLuint vColor_loc;

vec3 squareLocations[4];
Camera * k;
Camera * p;


Sphere::Sphere()
{
	program = InitShader("vshader01_v150.glsl", "fshader01_v150.glsl");
	buildSquare();
	//modelMatrix = Translate(0, 1, -4)*RotateY(1)*RotateX(1)*mat4(1.0);
	build();
	plane();
}

Sphere:: Sphere()
{
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);

	glDeleteBuffers(1, &sVBO);
	glDeleteVertexArrays(1, &sVAO);
}

void Sphere::build()
{
	

	sqrt2 = (float)sqrt(2.0);
	sqrt6 = (float)sqrt(6.0);

	index = 0;

	

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	
	glUseProgram(program);

	tetrahedron(4);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexLocations) + sizeof(vertexColors), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertexLocations), vertexLocations);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertexLocations), sizeof(vertexColors), vertexColors);

	vPosition_loc = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition_loc);
	glVertexAttribPointer(vPosition_loc, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	vColor_loc = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(vColor_loc);
	glVertexAttribPointer(vColor_loc, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertexLocations)));

	modelMatrix_loc = glGetUniformLocation(program, "model_matrix");


	//mat4 viewMatrix = k->view_matrix;//mat4(vec4(1, 0, 0, 0), vec4(0, 1, 0, 0), vec4(0, 0, -1, 0), vec4(0, 0, 0, 1));
	mat4 modelMatrix = Translate(0, 1, -4)*RotateY(0)*RotateX(0)*mat4(1.0); //rotate the model 10 degrees around the x-axis and then 10 degree around the y-axis
	glUniformMatrix4fv(modelMatrix_loc, 1, GL_TRUE, modelMatrix);


	

}

void Sphere::plane()
{

	glGenVertexArrays(1, &sVAO);
	glGenBuffers(1, &sVBO);


	glBindVertexArray(sVAO);
	glBindBuffer(GL_ARRAY_BUFFER, sVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(squareLocations), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(squareLocations), squareLocations);



	GLuint sPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(sPosition);
	glVertexAttribPointer(sPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
}

void Sphere::buildSquare() {
	squareLocations[0] = vec4(-13, -3, 13, 1);
	squareLocations[1] = vec4(-13, -3, -13,1);
	squareLocations[2] = vec4(13, -3,-13, 1);
	squareLocations[3] = vec4(13, -3,13, 1);
}

void Sphere::tetrahedron(int count) {

	vec4 v[4] = {
		vec4(0,0,1,1),
		vec4(0,2 * sqrt2 / 3, -1.0f / 3.0f, 1),
		vec4(-sqrt6 / 3.0f, -sqrt2 / 3.0f, -1.0f / 3.0f, 1.0f),
		vec4(sqrt6 / 3.0f, -sqrt2 / 3.0f, -1.0f / 3.0f, 1.0f)
	};

	//subdivide each of the 4 faces
	divideTriangle(v[0], v[1], v[2], count);
	divideTriangle(v[3], v[2], v[1], count);
	divideTriangle(v[0], v[3], v[1], count);
	divideTriangle(v[0], v[2], v[3], count);
}

void Sphere::divideTriangle(vec4 a, vec4 b, vec4 c, int count) {
	if (count > 0) {
		vec4 v1 = unit(a + b);
		v1.w = 1.0;
		vec4 v2 = unit(a + c);
		v2.w = 1.0;
		vec4 v3 = unit(b + c);
		v3.w = 1.0;

		divideTriangle(a, v1, v2, count - 1);
		divideTriangle(c, v2, v3, count - 1);
		divideTriangle(b, v3, v1, count - 1);
		divideTriangle(v1, v3, v2, count - 1);
	}
	else
		triangle(a, b, c);
}

void Sphere::triangle(vec4 a, vec4 b, vec4 c) {
	vec4 color(1.0*rand() / RAND_MAX, 1.0*rand() / RAND_MAX, 1.0*rand() / RAND_MAX, 1.0);
	vertexLocations[index] = a;
	vertexColors[index] = color;
	index++;

	vertexLocations[index] = b;
	vertexColors[index] = color;
	index++;

	vertexLocations[index] = c;
	vertexColors[index] = color;
	index++;
}

vec4 Sphere::unit(vec4 p) {
	float len = p.x*p.x + p.y*p.y + p.z*p.z;
	vec4 t;
	if (len > DivideByZeroTolerance) {
		t = p / sqrt(len);
		t.w = 1.0;
	}
	return t;
}


//----------------------------------------------------------------------------

void Sphere::drawSphere(Camera* k)
{
	//k = new Camera();

	

	glUseProgram(program);
	glBindVertexArray(VAO);
	viewMatrix_loc = glGetUniformLocation(program, "viewMatrix");
	glUniformMatrix4fv(viewMatrix_loc, 1, GL_TRUE, k->view_matrix);
	GLuint projMatrix_loc = glGetUniformLocation(program, "proj_matrix");
	glUniformMatrix4fv(projMatrix_loc, 1, GL_TRUE, k->proj_matrix);
	glDrawArrays(GL_TRIANGLES, 0,numVertices);
}

void Sphere::drawSquare() {


	glBindVertexArray(sVAO);
	glUseProgram(program);

	//set the transformation matrices
	GLuint model = glGetUniformLocation(program, "model_matrix");
	GLuint sColor = glGetUniformLocation(program, "color");
	glUniform4fv(sColor, 1, vec4(0.5, 0.5, 1, 1));
	glUniformMatrix3fv(model, 1, GL_TRUE, modelmatrix);


	//glUniform4fv(sColor, 1, vec4(1, 0, 1, 1));

	//draw!
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

}