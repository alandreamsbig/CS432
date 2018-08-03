#include "treeTop.h"

void treeTop::cleanup()
{
	glDeleteBuffers(1, &buffer);
}

//initialize the tree top
void treeTop::initOffsets()
{
	for (int i = 0; i < numTrees; i++)
	{
		treeOffsets[i] = vec4(0, 0,0, 0.0);
	}

}

void treeTop::setOffsets(vec4 newOffsets[])
{
	for (int i = 0; i < numTrees; i++)
	{
		treeOffsets[i] = newOffsets[i];
	}
}

//set number of trees
void treeTop::setNumTrees(int num)
{
	numTrees = num;
}

//initialize the color of the tree
void treeTop::initColors()
{
	for (int i = 0; i < 690; i++)
	{
		float x = (float)1.0*rand() / RAND_MAX;
		float y = (float)1.0*rand() / RAND_MAX;
		float z = (float)1.0*rand() / RAND_MAX;

		vertexColors[i] = vec4(x, y, z, 1.0);

	}
}

//initialize the texture coordinates for the tree top
void treeTop::initTexCoords()
{
	for (int i = 0; i < 690.0 / 3.0; i++)
	{
		textureCoords[i] = vec2((float)1.0*rand() / RAND_MAX, (float)1.0*rand() / RAND_MAX);
		textureCoords[i+1] = vec2((float)1.0*rand() / RAND_MAX, (float)1.0*rand() / RAND_MAX);
		textureCoords[i+2] = vec2((float)1.0*rand() / RAND_MAX, (float)1.0*rand() / RAND_MAX);
  	}
}

//apply transformation to the tree
void treeTop::applyTransformation(mat4 input)
{
	model_matrix = input * model_matrix;
}

//construct the tree top
treeTop::treeTop()
{

	initOffsets();

	view_matrix = mat4(1.0);
	projection_matrix = mat4(1.0);

	//create tree top buffer
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &buffer);
	std::cout << std::endl;

	//move the data to the buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(fullVertices) + sizeof(treeOffsets) + sizeof(textureCoords), NULL, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(fullVertices), fullVertices);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(fullVertices) , sizeof(treeOffsets), treeOffsets);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(fullVertices) +sizeof(treeOffsets),sizeof(textureCoords), textureCoords);


	//now load the shader and get the location of it's variables
	program = InitShader("vshader01_v150_snowTexture.glsl", "fshader01_v150_snowTexture.glsl");
	glUseProgram(program);

	//link the vertex attributes with the buffer
	vPosition_loc = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition_loc);
	glVertexAttribPointer(vPosition_loc, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	
	treeOffset_Loc = glGetAttribLocation(program, "snowPos");
	glEnableVertexAttribArray(treeOffset_Loc);
	int offset = sizeof(fullVertices);
	glVertexAttribPointer(treeOffset_Loc, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(offset));

	vTexCoord_loc = glGetAttribLocation(program, "vTexCoord");
	glEnableVertexAttribArray(vTexCoord_loc);
	offset = sizeof(fullVertices) + sizeof(treeOffsets);
	glVertexAttribPointer(vTexCoord_loc, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(offset));




	glVertexAttribDivisor(vPosition_loc, 0);
	glVertexAttribDivisor(vTexCoord_loc, 0);
	glVertexAttribDivisor(treeOffset_Loc, 1);
	

	model_matrix = mat4(1.0);//Scale(0.1);//Translate(5, 2, 0)*Scale(0.1)* mat4(1.0);

	modelMatrix_loc = glGetUniformLocation(program, "model_matrix");
	glUniformMatrix4fv(modelMatrix_loc, 1, GL_TRUE, model_matrix);

	viewMatrix_loc = glGetUniformLocation(program, "view_matrix");
	glUniformMatrix4fv(viewMatrix_loc, 1, GL_TRUE, view_matrix);

	projectionMatrix_loc = glGetUniformLocation(program, "projection_matrix");
	glUniformMatrix4fv(projectionMatrix_loc, 1, GL_TRUE, projection_matrix);



	//get the tree top texture
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

//tree top destructor
treeTop::~treeTop()
{
}

//draw the tree top
void treeTop::draw()
{

	glUseProgram(program);
	glBindVertexArray(VAO);


	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(fullVertices), sizeof(treeOffsets), treeOffsets);

	treeOffset_Loc = glGetAttribLocation(program, "snowPos");
	glEnableVertexAttribArray(treeOffset_Loc);

	int offset = sizeof(fullVertices);
	glVertexAttribPointer(treeOffset_Loc, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(offset));

	glVertexAttribDivisor(treeOffset_Loc, 1);


	modelMatrix_loc = glGetUniformLocation(program, "model_matrix");
	glUniformMatrix4fv(modelMatrix_loc, 1, GL_TRUE, model_matrix);

	viewMatrix_loc = glGetUniformLocation(program, "view_matrix");
	glUniformMatrix4fv(viewMatrix_loc, 1, GL_TRUE, view_matrix);

	projectionMatrix_loc = glGetUniformLocation(program, "projection_matrix");
	glUniformMatrix4fv(projectionMatrix_loc, 1, GL_TRUE, projection_matrix);

	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(program, "textureID"), 0);

	glDrawArraysInstanced(GL_TRIANGLES, 0, 690, numTrees);
}
