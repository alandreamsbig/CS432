#include "CubeMap.h"



CubeMap::CubeMap()
{
	currentCubeIndex = 0;
	buildCube();
	projection_matrix = Perspective(65, 1.0, 1.0, 100);
	model_matrix = Translate(-2, 1, -4);


	//create buffer for the cube
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//move data onto the buffer
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexLocations), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertexLocations), vertexLocations);

	program = InitShader("vshader01_v150_cubeMap.glsl", "fshader01_v150_cubeMap.glsl");
	glUseProgram(program);

	//link the vertex attributes with the buffer
	vPosition_loc = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition_loc);
	glVertexAttribPointer(vPosition_loc, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));


	modelMatrix_loc = glGetUniformLocation(program, "model_matrix");
	glUniformMatrix4fv(modelMatrix_loc, 1, GL_TRUE, model_matrix);

	viewMatrix_loc = glGetUniformLocation(program, "view_matrix");
	glUniformMatrix4fv(viewMatrix_loc, 1, GL_TRUE, view_matrix);

	projectionMatrix_loc = glGetUniformLocation(program, "projection_matrix");
	glUniformMatrix4fv(projectionMatrix_loc, 1, GL_TRUE, projection_matrix);

	int TextureSize = 512;

	//get the texture data
	glGenTextures(1, &texture);

	//set the texturing parameters
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	skyTop = ppmRead("skybox\\skybox-top.ppm", &TextureSize, &TextureSize);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, TextureSize, TextureSize, 0, GL_RGB, GL_UNSIGNED_BYTE, skyTop);
	skyBottom = ppmRead("skybox\\skybox-bottom.ppm", &TextureSize, &TextureSize);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, TextureSize, TextureSize, 0, GL_RGB, GL_UNSIGNED_BYTE, skyBottom);
	skyRight = ppmRead("skybox\\skybox-right.ppm", &TextureSize, &TextureSize);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, TextureSize, TextureSize, 0, GL_RGB, GL_UNSIGNED_BYTE, skyRight);
	skyLeft = ppmRead("skybox\\skybox-left.ppm", &TextureSize, &TextureSize);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, TextureSize, TextureSize, 0, GL_RGB, GL_UNSIGNED_BYTE, skyLeft);
	skyFront = ppmRead("skybox\\skybox-front.ppm", &TextureSize, &TextureSize);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, TextureSize, TextureSize, 0, GL_RGB, GL_UNSIGNED_BYTE, skyFront);
	skyBack = ppmRead("skybox\\skybox-back.ppm", &TextureSize, &TextureSize);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, TextureSize, TextureSize, 0, GL_RGB, GL_UNSIGNED_BYTE, skyBack);

}


void CubeMap::updateViewMatrix(mat4 newViewMatrix)
{
	view_matrix = newViewMatrix;
}


CubeMap::~CubeMap()
{
}

//draw the cube
void CubeMap::draw()
{
	glBindVertexArray(VAO);
	glUseProgram(program);

	modelMatrix_loc = glGetUniformLocation(program, "model_matrix");
	glUniformMatrix4fv(modelMatrix_loc, 1, GL_TRUE, model_matrix);

	viewMatrix_loc = glGetUniformLocation(program, "view_matrix");
	glUniformMatrix4fv(viewMatrix_loc, 1, GL_TRUE, view_matrix);

	projectionMatrix_loc = glGetUniformLocation(program, "projection_matrix");
	glUniformMatrix4fv(projectionMatrix_loc, 1, GL_TRUE, projection_matrix);


	glEnable(GL_TEXTURE_CUBE_MAP);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
	GLuint mapPos = glGetUniformLocation(program, "cubeMap");
	glUniform1i(mapPos, 0);

	glDrawArrays(GL_TRIANGLES, 0, 6 * 3 * 2);
}
