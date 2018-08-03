#include "Cube.h"

vec4 vertices[] = { vec4(-0.5,-0.5,0.5,1.0),
					vec4(-0.5,0.5,0.5,1.0),
					vec4(0.5,0.5,0.5,1.0),
					vec4(0.5,-0.5,0.5,1.0), 

					vec4(-0.5,-0.5,-0.5,1.0),
					vec4(-0.5,0.5,-0.5,1.0),
					vec4(0.5,0.5,-0.5,1.0),
					vec4(0.5,-0.5,-0.5,1.0) };



void Cube::makeQuad(int a, int b, int c, int d) {
	

	vertexLocations[currentCubeIndex] = vertices[a];
	vertexNormals[currentCubeIndex] = normalize(vec3(vertices[a][0], vertices[a][1], vertices[a][2]));
	vertexTextureLocations[currentCubeIndex] = vec2(0, 0);
	currentCubeIndex++;

	vertexLocations[currentCubeIndex] = vertices[b];
	vertexNormals[currentCubeIndex] = normalize(vec3(vertices[b][0], vertices[b][1], vertices[b][2]));
	vertexTextureLocations[currentCubeIndex] = vec2(1, 0);
	currentCubeIndex++;

	vertexLocations[currentCubeIndex] = vertices[c];
	vertexNormals[currentCubeIndex] = normalize(vec3(vertices[c][0], vertices[c][1], vertices[c][2]));
	vertexTextureLocations[currentCubeIndex] = vec2(1, 1);
	currentCubeIndex++;

	vertexLocations[currentCubeIndex] = vertices[c];
	vertexNormals[currentCubeIndex] = normalize(vec3(vertices[c][0], vertices[c][1], vertices[c][2]));
	vertexTextureLocations[currentCubeIndex] = vec2(1, 1);
	currentCubeIndex++;

	vertexLocations[currentCubeIndex] = vertices[d];
	vertexNormals[currentCubeIndex] = normalize(vec3(vertices[d][0], vertices[d][1], vertices[d][2]));
	vertexTextureLocations[currentCubeIndex] = vec2(0, 1);
	currentCubeIndex++;

	vertexLocations[currentCubeIndex] = vertices[a];
	vertexNormals[currentCubeIndex] = normalize(vec3(vertices[a][0], vertices[a][1], vertices[a][2]));
	vertexTextureLocations[currentCubeIndex] = vec2(0, 0);
	currentCubeIndex++;

}


void Cube::triangle(vec4 a, vec4 b, vec4 c)
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



void Cube::buildCube() {
	makeQuad(1, 0, 3, 2);  //front
	makeQuad(2, 3, 7, 6);  //right
	makeQuad(3, 0, 4, 7);  //bottom
	makeQuad(6, 5, 1, 2);  //top
	makeQuad(4, 5, 6, 7);  //back
	makeQuad(5, 4, 0, 1);  //left
}


void Cube::updateModelMatrix(mat4 newModelMatrix) {
	model_matrix = newModelMatrix;
}

Cube::Cube()
{

	buildCube();

	projection_matrix = Perspective(65, 1.0, 1.0, 100);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexLocations) + sizeof(vertexNormals) + sizeof(vertexTextureLocations), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertexLocations), vertexLocations);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertexLocations), sizeof(vertexNormals), vertexNormals);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertexLocations)+sizeof(vertexNormals), sizeof(vertexTextureLocations), vertexTextureLocations);

	program = InitShader("vshader01_v150_lightInFShader.glsl", "fshader01_v150_lightInFShader.glsl");
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

	model_matrix = mat4(1.0); //; Scale(2.0, 2.0, 2.0);


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

	


	int TextureSize = 512;

	glGenTextures(1, &texture);

	int len = strlen(currentTextureName.c_str()) + 1;
	char *fileName;
	fileName = new char[len];
	strncpy_s(fileName, len, currentTextureName.c_str(), len);


	GLubyte *image0 = ppmRead(fileName , &TextureSize, &TextureSize);

	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TextureSize, TextureSize, 0, GL_RGB, GL_UNSIGNED_BYTE, image0);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	

}


Cube::~Cube()
{
}


void Cube::transformModelMatrix(mat4 newMM) {
	model_matrix = newMM * model_matrix;
}


void Cube::draw()
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

	glDrawArrays(GL_TRIANGLES, 0, 36);
}

vec4 * Cube::getPoints() {
	return vertexLocations;
}
void Cube::setNormal(vec4 normal)
{
	currNormal = normal;
}

void Cube::setTexture(std::string textureName)
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

void Cube::updateViewMatrix(mat4 newViewMatrix)
{
	view_matrix = newViewMatrix;
}