#include "Sphere.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include<math.h>


void Sphere::cleanup()
{
	glDeleteBuffers(1, &buffer);
}

GLenum err;

//Construct the sphere
Sphere::Sphere()
{
	//makeSphere();
	createVertices();

	activated = true;

	view_matrix = mat4(vec4(1, 0, 0, 0), vec4(0, 1, 0, 0), vec4(0, 0, -1, 0), vec4(0, 0, 0, 1));
	projection_matrix = Perspective(65, 1.0, 1.0, 100);

	//create sphere buffer
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &buffer);

	//move the data to the buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexLocations) + sizeof(vertexNormals) + sizeof(vertexTextureLocations), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertexLocations), vertexLocations);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertexLocations), sizeof(vertexNormals), vertexNormals);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertexLocations) + sizeof(vertexNormals), sizeof(vertexTextureLocations), vertexTextureLocations);

	
	program = InitShader("vshader01_v150_lightInVShader.glsl", "fshader01_v150_lightInVShader.glsl");

	glUseProgram(program);

	//link the vertex attributes to the buffer
	vPosition_loc = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition_loc);
	glVertexAttribPointer(vPosition_loc, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	normal_Loc = glGetAttribLocation(program, "vNormal");
	glEnableVertexAttribArray(normal_Loc);
	glVertexAttribPointer(normal_Loc, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertexLocations)));

	GLuint vTex = glGetAttribLocation(program, "vTexCoord");
	glEnableVertexAttribArray(vTex);
	glVertexAttribPointer(vTex, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertexLocations) + sizeof(vertexNormals)));

	model_matrix = mat4(1.0);


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

	//get the sphere texture
	int TextureSize = 512;

	glGenTextures(1, &texture);

	int len = strlen(currentTextureName.c_str()) + 1;
	char *fileName;
	fileName = new char[len];
	strncpy_s(fileName, len, currentTextureName.c_str(), len);


	GLubyte *image0 = ppmRead(fileName, &TextureSize, &TextureSize);

	//set the texturing parameters
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TextureSize, TextureSize, 0, GL_RGB, GL_UNSIGNED_BYTE, image0);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


}

//sphere destructor
Sphere::~Sphere()
{
}

bool Sphere::getActivated()
{
	return activated;
}
void Sphere::deactivate()
{
	activated = false;
}

//update sphere view matrix
void Sphere::updateViewMatrix(mat4 newViewMatrix) {
	view_matrix = newViewMatrix;
}

//set sphere model matrix
void Sphere::setModelMatrix(mat4 newMM)
{
	model_matrix = newMM;
}

//get sphere model matrix
mat4 Sphere::getModelMatrix()
{
	return model_matrix;
}

//apply transformation to the sphere
void Sphere::applyTransformation(mat4 trans)
{
	model_matrix = trans*model_matrix;
		modelMatrix_loc = glGetUniformLocation(program, "model_matrix");
	glUniformMatrix4fv(modelMatrix_loc, 1, GL_TRUE, model_matrix);
}


//rotate the sphere along the X-axis
void Sphere::rotateX(double theta)
{
	model_matrix = RotateX(theta)*model_matrix;
}

//rotate the sphere along the y axis
void Sphere::rotateY(double theta)
{
	model_matrix = RotateY(theta) * model_matrix;
}

//rotate sphere along the z axis
void Sphere::rotateZ(double theta)
{
	model_matrix = RotateZ(theta)*model_matrix;
}

//set sphere normal
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

//draw the sphere
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

	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(program, "textureID"), 0);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 32768);

	/*
		GL_POINT
		GL_TRIANGLE_FAN
		GL_TRIANGLES
		GL_TRIANGLE_STRIP_ADJACENCY
		GL_TRIANGLES_ADJACENCY
		GL_TRIANGLES_ADJACENCY 
	
	*/
}

//set the sphere texture
void Sphere::setTexture(std::string textureName)
{
	currentTextureName = textureName;

	int TextureSize = 512;

	glGenTextures(1, &texture);


	int len = strlen(currentTextureName.c_str()) + 1;
	char *fileName;
	fileName = new char[len];
	strncpy_s(fileName, len, currentTextureName.c_str(), len);


	GLubyte *image0 = ppmRead(fileName, &TextureSize, &TextureSize);

	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TextureSize, TextureSize, 0, GL_RGB, GL_UNSIGNED_BYTE, image0);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
}

//activate the sphere head animation
int theta1 = 0;
void Sphere::headanimation()
{

		theta1++;
		if (theta1 > 360)
			theta1 = 0;


		float rad = theta1 * 2 * 3.14 / 360;
		mat4 r(vec4(cos(rad), -sin(rad), 0,0), vec4(sin(rad), cos(rad), 0,0), vec4(0, 0, 1,0), vec4(0,0,0,1));

		setModelMatrix(r);
	
}

bool Sphere::fixHeight()
{
	vec4 point(0, 0, 0, 1);
	if ((model_matrix * point).y - 0.6 < 0)
	{
		applyTransformation(Translate(0, 0.05, 0));
		return true;
	}

	return false;
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

//make the sphere with tetrahedron
void Sphere::makeSphere()
{
	tetrahedron(numDivisions);
}

//create tetrahedron with divide triangle
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

//get the sphere texture location
vec2 Sphere::getTextureLocation(vec3 point)
{
	float x, y, z;
	x = point.x;
	y = point.y;
	z = point.z;

	double theta, phi;
	if (abs(x) < .001)
	{
		theta = atan2( (float)y, x);
	}
	else
	{
		theta = atan( (float)x/y);
	}

	phi = acos( (float)z / 1.0 );

	double s, t;

	s = (float)(theta + M_PI) / (2.0 * M_PI);
	t = (float)(phi + M_PI) / (2.0 * M_PI);

	return vec2(s, t);
}

//create triangle for the sphere
void Sphere::triangle(vec4 a, vec4 b, vec4 c)
{
	vec3 ai(a.x, a.y, a.z);
	vec3 bi(b.x,b.y,b.z);
	vec3 ci(c.x,c.y,c.z);

	vec3 N = normalize(cross(bi-ai, ci-ai));
	
	vertexLocations[index] = a;
	vertexNormals[index] = N;
	vertexTextureLocations[index] = getTextureLocation(ai);  // vec2(0, 0);
	index++;

	vertexLocations[index] = b;
	vertexNormals[index] = N;
	vertexTextureLocations[index] = getTextureLocation(bi);// vec2(1, 1);
	index++;

	vertexLocations[index] = c;
	vertexNormals[index] = N;
	vertexTextureLocations[index] = getTextureLocation(ci); // vec2(0, 1);
	index++;

	curr++;
}


void Sphere::createVertices()
{
	std::ofstream myfile;
	myfile.open("IhadTo.txt");


	double x,y,z, nx, ny, nz, tx, ty;
	double theta, phi1, phi2;
	double s, t;
	int n = 128;
	for (int j = 0; j < n; j++)
	{
		phi1 = j*(2 * M_PI) / (float)n;
		phi2 = (j + 1) * (2 * M_PI) / (float)n;
		for (int i = 0; i < n; i++)
		{
			theta = i * M_PI / n;
			x = sin(theta) * cos(phi2);
			y = sin(theta) * sin(phi2);
			z = cos(theta);


			vertexLocations[index] = vec4(x, y, z, 1.0);
			vertexNormals[index] = vec3(x, y, z);

			s = phi2 / (2 * M_PI);
			t = 1 - theta / M_PI;
			vertexTextureLocations[index] = vec2(s, t);
			index++;



			x = sin(theta) * cos(phi1);
			y = sin(theta)*sin(phi1);
			z = cos(theta);
			vertexLocations[index] = vec4(x, y, z, 1.0);
			vertexNormals[index] = vec3(x, y, z);

			s = phi1 / (2 * M_PI);
			t = 1 - theta / M_PI;
			vertexTextureLocations[index] = vec2(s, t);
			index++;
		}
	}

	myfile << std::endl;
	myfile.close();

}


//check if the mouse click on the sphere usin ray
bool Sphere::processClick(vec4 rayOrigin, vec4 ray)
{

	std::vector<Triangle> triangles;
	for (int i = 0; i < 32768; i = i + 3)
	{
		triangles.push_back(Triangle(getModelMatrix()*vertexLocations[i], getModelMatrix()*vertexLocations[i + 1], getModelMatrix()*vertexLocations[i + 2]));
	}

	double t;
	double smallestT = 888888.00;
	int clickedTriangleVertex = -1;

	temp = 32768.0 / 3.0;
	for (int i = 0; i < temp; i++)
	{
		triangles[i].setRayAndOrigin(rayOrigin, ray);
		if (triangles[i].collisionWithPlane(t))
		{
			std::cout << "clicked vertex: " << i << std::endl;
			return true;
		}
	}
	std::cout << "clicked vertex: " << -1 << std::endl;

	return false;


}