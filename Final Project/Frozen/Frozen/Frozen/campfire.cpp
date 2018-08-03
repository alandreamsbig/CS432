#include "campfire.h"


void campfire::cleanup()
{
	glDeleteBuffers(1, &buffer);
}

//construct the campfire
campfire::campfire()
{
	view_matrix = mat4(1.0);
	projection_matrix = mat4(1.0);

	//create campfire buffer
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &buffer);
	std::cout << std::endl;

	//move the data to the buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(fullVertices) +sizeof(textureCoords)+sizeof(vertexNormals), NULL, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(fullVertices), fullVertices);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(fullVertices), sizeof(textureCoords), textureCoords);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(fullVertices)+sizeof(textureCoords), sizeof(vertexNormals), vertexNormals);
	
	//now load the shader and get the location of it's variables
	program = InitShader("vshader01_v150_campfire.glsl", "fshader01_v150_campfire.glsl");
	glUseProgram(program);

	//link the vertex attributes with the buffer
	vPosition_loc = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition_loc);
	glVertexAttribPointer(vPosition_loc, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));


	GLuint vTex = glGetAttribLocation(program, "vTexCoord");
	glEnableVertexAttribArray(vTex);
	glVertexAttribPointer(vTex, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(fullVertices)));

	normal_Loc = glGetAttribLocation(program, "vNormal");
	glEnableVertexAttribArray(normal_Loc);
	glVertexAttribPointer(normal_Loc, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(fullVertices) + sizeof(textureCoords)));

	double scale = 0.25;
	model_matrix = Translate(-5, scale+.001, -2)*Scale(scale)*mat4(1.0);

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
	//get the texture
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

//draw the camp fire
void campfire::draw()
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


	GLuint light_loc2 = glGetUniformLocation(program, "lightPos2");
	glUniform4fv(light_loc2, 1, lights[1].getPosition());

	GLuint lightAmbient_Loc2 = glGetUniformLocation(program, "lightAmbient2");
	glUniform4fv(lightAmbient_Loc2, 1, lights[1].getAmbient());

	GLuint lightDiffuse_Loc2 = glGetUniformLocation(program, "lightDiffuse2");
	glUniform4fv(lightDiffuse_Loc2, 1, lights[1].getDiffuse());

	GLuint lightSpecular_Loc2 = glGetUniformLocation(program, "lightSpecular2");
	glUniform4fv(lightSpecular_Loc2, 1, lights[1].getSpecular());



	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(program, "textureID"), 0);

	glDrawArrays(GL_TRIANGLES, 0, 2976);
}

//apply tranformation to the campfire
void campfire::applyTransformation(mat4 trans)
{
	model_matrix = trans*model_matrix;
	modelMatrix_loc = glGetUniformLocation(program, "model_matrix");
	glUniformMatrix4fv(modelMatrix_loc, 1, GL_TRUE, model_matrix);
}

//campfire destructor
campfire::~campfire()
{
}
