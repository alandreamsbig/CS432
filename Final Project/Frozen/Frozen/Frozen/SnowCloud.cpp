#include "SnowCloud.h"



void SnowCloud::cleanup()
{
	glDeleteBuffers(1, &buffer);
}


//check if the snowcloud should be deleted
bool SnowCloud::shouldDelete()
{
	for (int i = 0; i < numSnowflakes; i++)
	{
		if ( (model_matrix*(snowflakeOffsets[i] + fullVertices[13])).y > 0.1)
		{
			return false;
		}
	}
	
	return true;
}

//initialize the snowcloud offsets
void SnowCloud::initOffsets()
{
	for (int i = 0; i < numSnowflakes; i++)
	{
		double x, y, z;
		double scale = 250;
		x = (float)scale*rand() / RAND_MAX;
		y = (float)scale*rand() / RAND_MAX;
		z = (float)scale*rand() / RAND_MAX;
		if (scale * rand() / RAND_MAX < (float)(scale/2.0))
		{
			x = -1.0 * x;
		}
		if (scale * rand() / RAND_MAX < (float)(scale / 2.0))
		{
			z = -1.0 * z;
		}
		snowflakeOffsets[i] = vec4(x, y, z, 0.0);
	}
}

//initialize the snowcloud colors
void SnowCloud::initColors()
{
	vec4 color(1.0*rand() / RAND_MAX, 1.0*rand() / RAND_MAX, 1.0*rand() / RAND_MAX, 1);
	for (int i = 0; i < 144; i++)
	{
		vertexColors[i] = color;
		color = vec4(1.0*rand() / RAND_MAX, 1.0*rand() / RAND_MAX, 1.0*rand() / RAND_MAX, 1);
	}
}

//initialize the snowcloud texture coordinates
void SnowCloud::initTexCoords()
{
	for (int i = 0; i < 144; i = i + 3)
	{
		textureCoords[i] = vec2(0, 0);
		textureCoords[i+1] = vec2(1, 0);
		textureCoords[i+2] = vec2(1, 1);
	}
}

//apply tranformation to the snowcloud
void SnowCloud::applyTransformation(mat4 input)
{
	model_matrix = input * model_matrix;
}

//construct the snowcloud
SnowCloud::SnowCloud()
{
	initOffsets();
	initTexCoords();
	view_matrix = mat4(1.0);
	projection_matrix = mat4(1.0);

	//create snowcloud buffer
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &buffer);

	for (int i = 0; i < 50; i++)
	{
		std::cout << snowflakeOffsets[i] << std::endl;
	}

	std::cout << std::endl;

	//move the data to the buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(fullVertices) + sizeof(vertexColors) + sizeof(snowflakeOffsets), NULL, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(fullVertices), fullVertices);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(fullVertices), sizeof(vertexColors), vertexColors);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(fullVertices) + sizeof(vertexColors), sizeof(snowflakeOffsets), snowflakeOffsets);


	//now load the shader and get the location of it's variables
	program = InitShader("vshader01_v150_snowTexture.glsl", "fshader01_v150_snowTexture.glsl");
	glUseProgram(program);

	//link the vertex attributes to the buffer
	vPosition_loc = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition_loc);
	glVertexAttribPointer(vPosition_loc, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	vColor_loc = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(vColor_loc);
	glVertexAttribPointer(vColor_loc, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(fullVertices)));

	snowflakeOffset_Loc = glGetAttribLocation(program, "snowPos");
	glEnableVertexAttribArray(snowflakeOffset_Loc);
	int offset = sizeof(fullVertices) + sizeof(vertexColors);
	glVertexAttribPointer(snowflakeOffset_Loc, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(offset));

	glVertexAttribDivisor(vPosition_loc, 0);
	glVertexAttribDivisor(vColor_loc, 1);
	glVertexAttribDivisor(snowflakeOffset_Loc, 1);
	
	model_matrix = Translate(0, 0, 0)*Scale(.25, .25, .15)*mat4(1.0);//Scale(0.1);//Translate(5, 2, 0)*Scale(0.1)* mat4(1.0);

	modelMatrix_loc = glGetUniformLocation(program, "model_matrix");
	glUniformMatrix4fv(modelMatrix_loc, 1, GL_TRUE, model_matrix);

	viewMatrix_loc = glGetUniformLocation(program, "view_matrix");
	glUniformMatrix4fv(viewMatrix_loc, 1, GL_TRUE, view_matrix);

	projectionMatrix_loc = glGetUniformLocation(program, "projection_matrix");
	glUniformMatrix4fv(projectionMatrix_loc, 1, GL_TRUE, projection_matrix);



	//get the snowcloud texture
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

//draw the snowcloud
void SnowCloud::draw()
{

	glUseProgram(program);
	glBindVertexArray(VAO);
	

	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(fullVertices) + sizeof(vertexColors), sizeof(snowflakeOffsets), snowflakeOffsets);

	snowflakeOffset_Loc = glGetAttribLocation(program, "snowPos");
	glEnableVertexAttribArray(snowflakeOffset_Loc);
	int offset = sizeof(fullVertices) + sizeof(vertexColors);
	glVertexAttribPointer(snowflakeOffset_Loc, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(offset));

	glVertexAttribDivisor(snowflakeOffset_Loc, 1);


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

	glDrawArraysInstanced(GL_TRIANGLES, 0, 144, numSnowflakes);

}


//snowcloud destructor
SnowCloud::~SnowCloud()
{
}
