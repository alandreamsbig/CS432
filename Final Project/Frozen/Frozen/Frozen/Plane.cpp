#include "Plane.h"

void Plane::cleanup()
{
	glDeleteBuffers(1, &buffer);
}

//construct a plane
Plane::Plane()
{
	srand(static_cast<unsigned int>(time(0)));

	//set plane vertices
	vec4 a(-0.5,0,0.5, 1);
	vec4 b(.5,0,0.5, 1);
	vec4 c(0.5,0,-0.5, 1);
	vec4 d(-0.5,0,-0.5, 1);

	divideSquare(a, b, c, d, numDivisions);


	model_matrix = mat4(1.0); 

	view_matrix = mat4(vec4(1, 0, 0, 0), vec4(0, 1, 0, 0), vec4(0, 0, -1, 0), vec4(0, 0, 0, 1));
	projection_matrix = Perspective(65, 1.0, 1.0, 100);

	//create plane buffer
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//move the data onto the buffer
	glGenBuffers(1, &buffer);

	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexLocations) + sizeof(vertexNormals) + sizeof(vertexTextureLocations), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertexLocations), vertexLocations);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertexLocations), sizeof(vertexNormals), vertexNormals);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertexLocations)+sizeof(vertexNormals), sizeof(vertexTextureLocations), vertexTextureLocations);


	program = InitShader("vshader01_v150_lightInFShader.glsl", "fshader01_v150_lightInFShader.glsl");
	glUseProgram(program);

	//link vertex attributes with buffer
	vPosition_loc = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition_loc);
	glVertexAttribPointer(vPosition_loc, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	normal_Loc = glGetAttribLocation(program, "vNormal");
	glEnableVertexAttribArray(normal_Loc);
	glVertexAttribPointer(normal_Loc, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertexLocations)));

	GLuint vTex = glGetAttribLocation(program, "vTexCoord");
	glEnableVertexAttribArray(vTex);
	glVertexAttribPointer(vTex, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertexLocations) + sizeof(vertexNormals)));


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

	//get the texture
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

//set the plane texture
void Plane::setTexture(std::string textureName)
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
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}


Plane::~Plane()
{
}


void Plane::updateViewMatrix(mat4 newViewMatrix)
{
	view_matrix = newViewMatrix;
}

//draw the plane
void Plane::draw()
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

	GLuint spotlightEnabled = glGetUniformLocation(program, "enabled1");
	glUniform1i(spotlightEnabled, lights[0].getEnabled());

	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(program, "textureID"), 0);


	glDrawArrays(GL_TRIANGLES, 0, numVertices);
}

//create triangles for the plane
void Plane::createTriangle(vec4 a, vec4 b, vec4 c)
{
	vec3 ai(a.x, a.y, a.z);
	vec3 bi(b.x, b.y, b.z);
	vec3 ci(c.x, c.y, c.z);

	vec3 N = normalize(cross(bi - ai, ci - ai));

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

vec4 Plane::getCenter(vec4 p1, vec4 p3)
{
	double midX = (p1[0] + p3[0]) / 2.0;
	double midY = (p1[1] + p3[1]) / 2.0;

	return vec4(midX, midY, p1[2], 1.0);
}

//create plane from triangles
void Plane::makeQuad(vec4 a, vec4 b, vec4 c, vec4 d)
{
	vec3 ai(a.x, a.y, a.z);
	vec3 bi(b.x, b.y, b.z);
	vec3 ci(c.x, c.y, c.z);
	vec3 di(d.x, d.y, d.z);

	vec3 N = normalize(cross(bi - ai, di - ai));
	

	vertexLocations[index] = a;
	vertexNormals[index] = N;
	vertexTextureLocations[index] = vec2(0, 0);
	index++;

	vertexLocations[index] = b;
	vertexNormals[index] = N;
	vertexTextureLocations[index] = vec2(1, 0);
	index++;

	vertexLocations[index] = d;
	vertexNormals[index] = N;
	vertexTextureLocations[index] = vec2(0,1);
	index++;

	vec3 N2 = normalize(cross(di - ci, bi - ci));

	vertexLocations[index] = d;
	vertexNormals[index] = N2;
	vertexTextureLocations[index] = vec2(0, 1);
	index++;

	vertexLocations[index] = b;
	vertexNormals[index] = N2;
	vertexTextureLocations[index] = vec2(1, 0);
	index++;

	vertexLocations[index] = c;
	vertexNormals[index] = N2;
	vertexTextureLocations[index] = vec2(1,1);
	index++;





	
}


void Plane::divideSquare(vec4 a, vec4 b, vec4 c, vec4 d, int count)
{
	if (count > 0)
	{
		vec4 center = getCenter(a, c);
		center[2] = (a[2] + d[2]) / 2.0;

		vec4 halfBottom = vec4(center[0], a[1], a[2], 1.0);
		vec4 halfRight = vec4(b[0], center[1], center[2], 1.0);
		vec4 halfTop = vec4(center[0], c[1], c[2], 1.0);
		vec4 halfLeft = vec4(a[0], center[1], center[2], 1.0);

		divideSquare(a, halfBottom, center, halfLeft, count - 1);
		divideSquare(halfBottom, b, halfRight, center, count - 1);
		divideSquare(center, halfRight, c, halfTop, count - 1);
		divideSquare(halfLeft, center, halfTop, d, count - 1);
	}
	else
	{
		//createTriangle(a, b, d);
		//createTriangle(d, b, c);

		makeQuad(a, b, c, d);

	}
}



void Plane::updateModelMatrix(mat4 newViewMatrix)
{
	model_matrix  = newViewMatrix;
}