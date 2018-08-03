#include "Roof.h"

//create vertices for the roof
vec4 roofvertices[] = {
	vec4(-0.5,0.5,0.5,1.0),
	vec4(0.5,0.5,0.5,1.0),
	vec4(0,1.0,0.5,1.0),
	vec4(-0.5,0.5,-0.5,1.0),
	vec4(0.5,0.5,-0.5,1.0),
	vec4(0,1.0,-0.5,1.0)
};
void Roof::cleanup()
{
	glDeleteBuffers(1, &buffer);
}

//build the roof
void Roof::build()
{
	makeTriangle(0, 1, 2);
	makeTriangle(4, 3, 5);
	makeTriangle(1,5,2);
	makeTriangle(1,4,5);
	makeTriangle(0,2,5);
	makeTriangle(0,5,3);
	makeTriangle(0,3,4);
	makeTriangle(0,4,1);
}

//create triangles for the roof
void Roof::makeTriangle(int a, int b, int c)
{
	vertexLocations[currentCubeIndex] = roofvertices[a];
	vertexNormals[currentCubeIndex] = normalize(vec3(roofvertices[a][0], roofvertices[a][1], roofvertices[a][2]));
	vertexTextureLocations[currentCubeIndex] = vec2(0, 0);
	currentCubeIndex++;

	vertexLocations[currentCubeIndex] = roofvertices[b];
	vertexNormals[currentCubeIndex] = normalize(vec3(roofvertices[b][0], roofvertices[b][1], roofvertices[b][2]));
	vertexTextureLocations[currentCubeIndex] = vec2(1, 1);	
	currentCubeIndex++;

	vertexLocations[currentCubeIndex] = roofvertices[c];
	vertexNormals[currentCubeIndex] = normalize(vec3(roofvertices[c][0], roofvertices[c][1], roofvertices[c][2]));
	vertexTextureLocations[currentCubeIndex] = vec2(0, 1);
	currentCubeIndex++;
}




//construct a roof
Roof::Roof()
{

	build();

	projection_matrix = Perspective(65, 1.0, 1.0, 100);

	//create buffer for the roof
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//move the data to the buffer
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexLocations) + sizeof(vertexNormals) + sizeof(vertexTextureLocations), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertexLocations), vertexLocations);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertexLocations), sizeof(vertexNormals), vertexNormals);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertexLocations) + sizeof(vertexNormals), sizeof(vertexTextureLocations), vertexTextureLocations);

	program = InitShader("vshader01_v150_lightInFShader.glsl", "fshader01_v150_lightInFShader.glsl");
	glUseProgram(program);

	//link vertex attributes with the buffer
	vPosition_loc = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition_loc);
	glVertexAttribPointer(vPosition_loc, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	normal_Loc = glGetAttribLocation(program, "vNormal");
	glEnableVertexAttribArray(normal_Loc);
	glVertexAttribPointer(normal_Loc, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertexLocations)));

	GLuint vTex = glGetAttribLocation(program, "vTexCoord");
	glEnableVertexAttribArray(vTex);
	glVertexAttribPointer(vTex, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertexLocations) + sizeof(vertexNormals)));

	model_matrix = mat4(1.0)*Translate(0, 0, -10)*Scale(10.0, 10.0, 10.0);


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

	//get the roof texture
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

void Roof::updateViewMatrix(mat4 newViewMatrix)
{
	view_matrix = newViewMatrix;
}

//draw the roof
void Roof::draw()
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

	glDrawArrays(GL_TRIANGLES, 0, 32);
}



Roof::~Roof()
{
}
