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
	program = InitShader("vshaderLighting_v150.glsl", "fshaderLighting_v150.glsl");
	vpos = glGetAttribLocation(program, "vPosition");
	npos = glGetAttribLocation(program, "vNormal");
	mmpos = glGetUniformLocation(program, "model_matrix");
	vmpos = glGetUniformLocation(program, "view_matrix");
	pmpos = glGetUniformLocation(program, "proj_matrix");
	diffuse_loc = glGetUniformLocation(program, "matDiffuse");
	spec_loc = glGetUniformLocation(program, "matSpecular");
	ambient_loc = glGetUniformLocation(program, "matAmbient");
	alpha_loc = glGetUniformLocation(program, "matAlpha");


	buildSquare();
	build();
	plane();

}

Sphere:: ~Sphere()
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
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexLocations) + sizeof(vertexNormals), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertexLocations), vertexLocations);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertexLocations), sizeof(vertexNormals), vertexNormals);

	glEnableVertexAttribArray(vpos);
	glVertexAttribPointer(vpos, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glEnableVertexAttribArray(npos);
	glVertexAttribPointer(npos, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertexLocations)));

	modelMatrix_loc = glGetUniformLocation(program, "model_matrix");


	//mat4 viewMatrix = k->view_matrix;//mat4(vec4(1, 0, 0, 0), vec4(0, 1, 0, 0), vec4(0, 0, -1, 0), vec4(0, 0, 0, 1));
	mat4 modelMatrix = Translate(0, 2, -4)*RotateY(0)*RotateX(0)*mat4(1.0); //rotate the model 10 degrees around the x-axis and then 10 degree around the y-axis
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
	squareLocations[1] = vec4(-13, -3, -13, 1);
	squareLocations[2] = vec4(13, -3, -13, 1);
	squareLocations[3] = vec4(13, -3, 13, 1);
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

void Sphere::triangle(vec4 ai, vec4 bi, vec4 ci) {
	vec3 a = vec3(ai.x, ai.y, ai.z);
	vec3 b = vec3(bi.x, bi.y, bi.z);
	vec3 c = vec3(ci.x, ci.y, ci.z);

	vec3 N = normalize(cross(b - a, c - a));

	vertexLocations[index] = a;
	vertexNormals[index] = N;
	index++;

	vertexLocations[index] = b;
	vertexNormals[index] = N;
	index++;

	vertexLocations[index] = c;
	vertexNormals[index] = N;
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

void Sphere::setMaterial(vec4 a, vec4 d, vec4 s, float sh)
{
	diffuse = d;
	specular = s;
	ambient = a;
	shine = sh;
}

void Sphere::assignGouradVertices() {

	vec3 normalSum[numVertices];
	int counts[numVertices];

	for (int i = 0; i < numVertices; i++) {
		normalSum[i] = vec3(0, 0, 0);
		counts[i] = 0;
	}

	for (int i = 0; i < numVertices; i++)
	{
		int count = 0;
		for (int j = 0 ;j < numVertices; j++)
		{
			if ((vertexLocations[i].x == vertexLocations[j].x) && (vertexLocations[i].y == vertexLocations[j].y) && (vertexLocations[i].z == vertexLocations[j].z))
			{
				count++;
				normalSum[i] += vertexNormals[j];
			}
		}
		counts[i] = count;
	}

	for (int i = 0; i < numVertices; i++)
	{
		vertexNormals[i] = normalSum[i] / counts[i];
	}
}

//----------------------------------------------------------------------------

void Sphere::drawSphere(Camera* k, vector<Light>lights)
{

	glUseProgram(program);
	glBindVertexArray(VAO);
	viewMatrix_loc = glGetUniformLocation(program, "view_matrix");
	glUniformMatrix4fv(viewMatrix_loc, 1, GL_TRUE, k->view_matrix);
	GLuint projMatrix_loc = glGetUniformLocation(program, "proj_matrix");
	glUniformMatrix4fv(projMatrix_loc, 1, GL_TRUE, k->proj_matrix);
	
	
	glUniform4fv(diffuse_loc, 1, diffuse);
	glUniform4fv(spec_loc, 1, specular);
	glUniform4fv(ambient_loc, 1, ambient);
	glUniform1f(alpha_loc, shine);


	
	GLuint light_loc = glGetUniformLocation(program, "lightPos");
	glUniform4fv(light_loc, 1, lights[0].getPosition());
	GLuint ambient_loc2 = glGetUniformLocation(program, "lightAmbient");
	glUniform4fv(ambient_loc2, 1, lights[0].getAmbient());
	GLuint diffuse_loc2 = glGetUniformLocation(program, "lightDiffuse");
	glUniform4fv(diffuse_loc2, 1, lights[0].getDiffuse());
	GLuint specular_loc2 = glGetUniformLocation(program, "lightSpecular");
	glUniform4fv(specular_loc2, 1, lights[0].getSpecular());
	
	glDrawArrays(GL_TRIANGLES, 0, numVertices);
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