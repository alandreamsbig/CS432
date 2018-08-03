#include "Skybox.h"



Skybox::Skybox()
{
	currentCubeIndex = 0;
	buildCube();

	projection_matrix = Perspective(65, 1.0, .1, 250); //Perspective(90, GLfloat(500.0 / 500.0), 0.1, 200); //
	model_view = LookAt(vec4(0, 0, 0, 1), vec4(0, 0, 0, 1) - currNormal, currV);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexLocations), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertexLocations), vertexLocations);

	program = InitShader("vshader01_v150_skybox.glsl", "fshader01_v150_skybox.glsl");
	glUseProgram(program);

	vPosition_loc = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition_loc);
	glVertexAttribPointer(vPosition_loc, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));


	modelviewMatrix_loc = glGetUniformLocation(program, "modelview_matrix");
	glUniformMatrix4fv(modelviewMatrix_loc, 1, GL_TRUE, model_matrix);
	
	projectionMatrix_loc = glGetUniformLocation(program, "projection_matrix");
	glUniformMatrix4fv(projectionMatrix_loc, 1, GL_TRUE, projection_matrix);


	int TextureSize = 512;

	glGenTextures(1, &texture);
	
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

void Skybox::setNormal(vec4 nI)
{
	currNormal = nI;
}

void Skybox::setV(vec4 vI)
{
	currV = vI;
}

Skybox::~Skybox()
{
}

void Skybox::draw()
{
	model_view = LookAt(vec4(0, 0, 0, 1), vec4(0, 0, 0, 1) - currNormal, currV);

	glBindVertexArray(VAO);
	glUseProgram(program);

	GLuint model_loc = glGetUniformLocation(program, "modelview_matrix");
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model_view);

	GLuint proj_loc = glGetUniformLocation(program, "projection_matrix");
	glUniformMatrix4fv(proj_loc, 1, GL_TRUE, projection_matrix);


	glEnable(GL_TEXTURE_CUBE_MAP);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
	GLuint mapPos = glGetUniformLocation(program, "cubeMap");
	glUniform1i(mapPos, 0);

	glDisable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);

	glDrawArrays(GL_TRIANGLES, 0, 6 * 3 * 2);


	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);

}
