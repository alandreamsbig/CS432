#include "SphereOld.h"
#include <iostream>
#include <fstream>


SphereOld::SphereOld()
{
	makeSphereOld();
	srand(static_cast<unsigned int>(time(0)));

	view_matrix = mat4(vec4(1, 0, 0, 0), vec4(0, 1, 0, 0), vec4(0, 0, -1, 0), vec4(0, 0, 0, 1));
	projection_matrix = Perspective(65, 1.0, 1.0, 100);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &buffer);

	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexLocations) + sizeof(vertexNormals) + sizeof(vertexTextureLocations), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertexLocations), vertexLocations);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertexLocations), sizeof(vertexNormals), vertexNormals);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertexLocations) + sizeof(vertexNormals), sizeof(vertexTextureLocations), vertexTextureLocations);


	program = InitShader("vshader01_v150_lightInVShader.glsl", "fshader01_v150_lightInVShader.glsl");

	glUseProgram(program);

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

	int TextureSize = 512;

	glGenTextures(1, &texture);

	int len = strlen(currentTextureName.c_str()) + 1;
	char *fileName;
	fileName = new char[len];
	strncpy_s(fileName, len, currentTextureName.c_str(), len);


	GLubyte *image0 = ppmRead(fileName, &TextureSize, &TextureSize);

	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TextureSize, TextureSize, 0, GL_RGB, GL_UNSIGNED_BYTE, image0);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}


SphereOld::~SphereOld()
{
}


mat4 SphereOld::getModelMatrix()
{
	return model_matrix;
}

std::vector<Triangle> SphereOld::getTriangles()
{
	std::vector<Triangle> triangles;

	for (int i = 0; i < temp*3; i = i + 3)
	{
		triangles.push_back(Triangle(getModelMatrix()*vertexLocations[i], getModelMatrix()*vertexLocations[i + 1], getModelMatrix()*vertexLocations[i + 2]));
	}
	return triangles;
}

double SphereOld::getT(vec4 rayOrigin, vec4 ray)
{
	std::vector<Triangle> triangles;

	for (int i = 0; i < temp*3; i = i + 3)
	{
		triangles.push_back(Triangle(getModelMatrix()*vertexLocations[i], getModelMatrix()*vertexLocations[i + 1], getModelMatrix()*vertexLocations[i + 2]));
	}

	double t = 0;
	double smallestT = 888888.00;
	int clickedTriangleVertex = -1;

	for (int i = 0; i < temp; i++)
	{
		triangles[i].setRayAndOrigin(rayOrigin, ray);
		if (triangles[i].collisionWithPlane(t))
		{
			//std::cout << "tInside: " << t << std::endl;
			if (t < smallestT)
			{
				smallestT = t;
				clickedTriangleVertex = i * 3;
			}
			//std::cout << "\nyes " << t << "\n" << std::endl;
		}
		else
		{
			//std::cout << "no ";
		}
	}


	return smallestT;
}
void SphereOld::setModelMatrix(mat4 newMM)
{
	model_matrix = newMM;
}

bool SphereOld::processClick(vec4 rayOrigin, vec4 ray)
{

	std::vector<Triangle> triangles;
	for (int i = 0; i < temp*3; i = i + 3)
	{
		triangles.push_back(Triangle(getModelMatrix()*vertexLocations[i], getModelMatrix()*vertexLocations[i+1], getModelMatrix()*vertexLocations[i+2]));
	}

	double t;
	double smallestT = 888888.00;
	int clickedTriangleVertex = -1;

	
	for (int i = 0; i < temp; i++)
	{
		triangles[i].setRayAndOrigin(rayOrigin, ray);
		if (triangles[i].collisionWithPlane(t))
		{
			return true;
		}
	}
	return false;
	
}



void SphereOld::printViewMatrix()
{
	std::cout << "ViewMatrix:\n" << view_matrix << std::endl;
}

void SphereOld::rotateX(double theta)
{
	model_matrix = RotateX(theta)*model_matrix;
}

void SphereOld::rotateY(double theta)
{
	model_matrix = Translate(0, 0, -2)*RotateY(theta)*Translate(0, 0, 2)*model_matrix;
}

void SphereOld::rotateZ(double theta)
{
	model_matrix = RotateZ(theta)*model_matrix;
}


void SphereOld::updateViewMatrix(mat4 newViewMatrix)
{
	view_matrix = newViewMatrix;
}


void SphereOld::draw()
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
	glUniform1f(alpha_Loc, shine);


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

	glDrawArrays(GL_TRIANGLE_FAN, 0, temp*3);
}

void SphereOld::printPoints()
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


void SphereOld::makeSphereOld()
{
	tetrahedron(numDivisions);
}

void SphereOld::tetrahedron(int count)
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

void SphereOld::divideTriangle(vec4 a, vec4 b, vec4 c, int count)
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

vec4 SphereOld::unit(vec4 p)
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

vec2 SphereOld::getTextureLocation(vec3 point)
{
	float x, y, z;
	x = point.x;
	y = point.y;
	z = point.z;

	double theta, phi;
	if (abs(x) < .001)
	{
		theta = atan2((float)y, x);
	}
	else
	{
		theta = atan((float)x / y);
	}

	phi = acos((float)z / 1.0);

	double s, t;

	s = (float)(theta + M_PI) / (2.0 * M_PI);
	t = (float)(phi + M_PI) / (2.0 * M_PI);

	return vec2(s, t);
}

void SphereOld::triangle(vec4 a, vec4 b, vec4 c)
{
	vec3 ai(a.x, a.y, a.z);
	vec3 bi(b.x, b.y, b.z);
	vec3 ci(c.x, c.y, c.z);

	vec3 N = normalize(cross(bi - ai, ci - ai));

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