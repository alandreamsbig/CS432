#include "Sphere.h"
#include <iostream>
#include <fstream>
#include <cmath>


Sphere::Sphere()
{
	makeSphere();

	view_matrix = mat4(vec4(1, 0, 0, 0), vec4(0, 1, 0, 0), vec4(0, 0, -1, 0), vec4(0, 0, 0, 1));
	projection_matrix = Perspective(65, 1.0, 1.0, 100);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &buffer);

	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexLocations) + sizeof(vertexNormals), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertexLocations), vertexLocations);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertexLocations), sizeof(vertexNormals), vertexNormals);


	program = InitShader("vshader01_v150_lightInVShader.glsl", "fshader01_v150_lightInVShader.glsl");
	
	glUseProgram(program);

	vPosition_loc = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition_loc);
	glVertexAttribPointer(vPosition_loc, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	normal_Loc = glGetAttribLocation(program, "vNormal");
	glEnableVertexAttribArray(normal_Loc);
	glVertexAttribPointer(normal_Loc, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertexLocations)));



	model_matrix = Translate(0, 1, -4)*mat4(1.0);


	modelMatrix_loc = glGetUniformLocation(program, "model_matrix");
	glUniformMatrix4fv(modelMatrix_loc, 1, GL_TRUE, model_matrix);

	viewMatrix_loc = glGetUniformLocation(program, "view_matrix");
	glUniformMatrix4fv(viewMatrix_loc, 1, GL_TRUE, view_matrix);

	projectionMatrix_loc = glGetUniformLocation(program, "projection_matrix");
	glUniformMatrix4fv(projectionMatrix_loc, 1, GL_TRUE, projection_matrix);

	


	diffuse_Loc = glGetUniformLocation(program, "matDiffuse");
	specular_Loc = glGetUniformLocation(program, "matSpecular");
	ambient_Loc = glGetUniformLocation(program, "matAmbient");
	alpha_Loc = glGetUniformLocation(program, "matAlpha");


	lights[0].printLight();
	std::cout << std::endl;


}


Sphere::~Sphere()
{
}


void Sphere::updateViewMatrix(mat4 newViewMatrix) {
	view_matrix = newViewMatrix;
}

void Sphere::setModelMatrix(mat4 newMM)
{
	model_matrix = newMM;
}

mat4 Sphere::getModelMatrix()
{
	return model_matrix;
}

void Sphere::applyTransformation(mat4 trans)
{
	model_matrix = trans*model_matrix;
		modelMatrix_loc = glGetUniformLocation(program, "model_matrix");
	glUniformMatrix4fv(modelMatrix_loc, 1, GL_TRUE, model_matrix);
}



void Sphere::rotateX(double theta)
{
	model_matrix = RotateX(theta)*model_matrix;
}

void Sphere::rotateY(double theta)
{
	model_matrix = Translate(0, 0, -2)*RotateY(theta)*Translate(0, 0, 2)*model_matrix;
}

void Sphere::rotateZ(double theta)
{
	model_matrix = RotateZ(theta)*model_matrix;
}


void Sphere::setNormal(vec4 normal)
{
	currNormal = normal;
}

double distance(vec3 a, vec3 b)
{
	double x = a[0];
	double y = a[1];
	double z = a[2];

	double x2 = b[0];
	double y2 = b[1];
	double z2 = b[2];

	return sqrt(pow((x - x2), 2) + pow((y - y2), 2) + pow((z - z2), 2));
}

void Sphere::draw()
{
	glBindVertexArray(VAO);
	glUseProgram(program);

	glBindBuffer(GL_ARRAY_BUFFER, buffer);

	modelMatrix_loc = glGetUniformLocation(program, "model_matrix");
	glUniformMatrix4fv(modelMatrix_loc, 1, GL_TRUE, model_matrix);

	viewMatrix_loc = glGetUniformLocation(program, "view_matrix");
	glUniformMatrix4fv(viewMatrix_loc, 1, GL_TRUE, view_matrix);

	projectionMatrix_loc = glGetUniformLocation(program, "projection_matrix");
	glUniformMatrix4fv(projectionMatrix_loc, 1, GL_TRUE, projection_matrix);

	glUniform4fv(diffuse_Loc, 1, diffuse);
	glUniform4fv(specular_Loc, 1, specular);
	glUniform4fv(ambient_Loc, 1, ambient);
	glUniform1f(alpha_Loc,  shine);


	GLuint light_loc = glGetUniformLocation(program, "lightPos1");
	glUniform4fv(light_loc, 1, lights[0].getPosition());

	GLuint lightAmbient_Loc = glGetUniformLocation(program, "lightAmbient1");
	glUniform4fv(lightAmbient_Loc, 1, lights[0].getAmbient());

	GLuint lightDiffuse_Loc = glGetUniformLocation(program, "lightDiffuse1");
	glUniform4fv(lightDiffuse_Loc, 1, lights[0].getDiffuse());

	GLuint lightSpecular_Loc = glGetUniformLocation(program, "lightSpecular1");
	glUniform4fv(lightSpecular_Loc, 1, lights[0].getSpecular());

	GLuint light_loc2 = glGetUniformLocation(program, "lightPos2");
	glUniform4fv(light_loc2, 1, lights[1].getPosition());

	GLuint lightAmbient_Loc2 = glGetUniformLocation(program, "lightAmbient2");
	glUniform4fv(lightAmbient_Loc2, 1, lights[1].getAmbient());

	GLuint lightDiffuse_Loc2 = glGetUniformLocation(program, "lightDiffuse2");
	glUniform4fv(lightDiffuse_Loc2, 1, lights[1].getDiffuse());

	GLuint lightSpecular_Loc2 = glGetUniformLocation(program, "lightSpecular2");
	glUniform4fv(lightSpecular_Loc2, 1, lights[1].getSpecular());

	GLuint sunEnabled = glGetUniformLocation(program, "enabled2");
	glUniform1i(sunEnabled, lights[1].getEnabled());

	GLuint flashlightEnabled = glGetUniformLocation(program, "enabled1");
	glUniform1i(flashlightEnabled, lights[0].getEnabled());


	glDrawArrays(GL_TRIANGLES, 0, temp *3);
}

void Sphere::printPoints()
{
	std::ofstream myfile;
	myfile.open("IhadTo.txt");

	size_t barCount = sizeof(vertexLocations) / (double) sizeof(vec4);

	for (int i = 0; i < barCount; i++)
	{
		std::cout << "[" << vertexLocations[i][0] << ", " <<vertexLocations[i][1] << ", " <<vertexLocations[i][2] << "], ";
		myfile << "[" << vertexLocations[i][0] << ", " << vertexLocations[i][1] << ", " << vertexLocations[i][2] << "], ";
	}

	std::cout << std::endl;
	myfile.close();
}


void Sphere::makeSphere()
{
	tetrahedron(numDivisions);
}

void Sphere::tetrahedron(int count)
{
	vec4 v[4] = {
		vec4(0,0,1,1),
		vec4(0,2.0 * ((float)sqrt(2.0)) / 3.0, -1.0 / 3.0, 1),
		vec4(-((float)sqrt(6.0)) / 3.0, -((float)sqrt(2.0)) / 3.0, -1.0 / 3.0, 1.0),
		vec4(((float)sqrt(6.0)) / 3.0, -((float)sqrt(2.0)) / 3.0, -1.0 / 3.0, 1.0)
	};

	divideTriangle(v[0], v[1], v[2], count);
	divideTriangle(v[3], v[2], v[1], count);
	divideTriangle(v[0], v[3], v[1], count);
	divideTriangle(v[0], v[2], v[3], count);

}

void Sphere::divideTriangle(vec4 a, vec4 b, vec4 c, int count)
{
	if (count > 0)
	{
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
	{
		triangle(a, b, c);
	}
}

vec4 Sphere::unit(vec4 p)
{
	float len = p.x*p.x + p.y*p.y + p.z*p.z;
	vec4 t;
	if (len > DivideByZeroTolerance)
	{
		t = p / sqrt(len);
		t.w = 1.0;
	}
	return t;
}
bool test = true;

int curr = 0;

void Sphere::triangle(vec4 a, vec4 b, vec4 c)
{
	vec3 ai(a.x, a.y, a.z);
	vec3 bi(b.x,b.y,b.z);
	vec3 ci(c.x,c.y,c.z);

	vec3 N = normalize(cross(bi-ai, ci-ai));
	
	vertexLocations[index] = a;
	vertexNormals[index] = N;
	index++;

	vertexLocations[index] = b;
	vertexNormals[index] = N;
	index++;

	vertexLocations[index] = c;
	vertexNormals[index] = N;
	index++;

	curr++;
}