#include "Snowflake.h"

//construct the snowflake
Snowflake::Snowflake()
{
	view_matrix = mat4(1.0);
	projection_matrix = mat4(1.0);
	initColors();

	//create snowflake buffer
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &buffer);

	//move the data onto the buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(fullVertices)+sizeof(vertexColors), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(fullVertices), fullVertices);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(fullVertices), sizeof(vertexColors), vertexColors);



	//now load the shader and get the location of it's variables
	program = InitShader("vshader01_v150_colorFromBuffer.glsl", "fshader01_v150_colorFromBuffer.glsl");
	glUseProgram(program);

	//link the vertex attributes with the buffer
	vPosition_loc = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition_loc);
	glVertexAttribPointer(vPosition_loc, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	vColor_loc = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(vColor_loc);
	glVertexAttribPointer(vColor_loc, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(fullVertices)));


	model_matrix = Scale(0.1);//Translate(5, 2, 0)*Scale(0.1)* mat4(1.0);

	modelMatrix_loc = glGetUniformLocation(program, "model_matrix");
	glUniformMatrix4fv(modelMatrix_loc, 1, GL_TRUE, model_matrix);

	viewMatrix_loc = glGetUniformLocation(program, "view_matrix");
	glUniformMatrix4fv(viewMatrix_loc, 1, GL_TRUE, view_matrix);

	projectionMatrix_loc = glGetUniformLocation(program, "projection_matrix");
	glUniformMatrix4fv(projectionMatrix_loc, 1, GL_TRUE, projection_matrix);

}

//draw the snowflakes
void Snowflake::draw()
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


	glDrawArrays(GL_TRIANGLES, 0, 540);    
}

//initialize snowflake color
void Snowflake::initColors()
{
	vec4 color(1.0*rand() / RAND_MAX, 1.0*rand() / RAND_MAX, 1.0*rand() / RAND_MAX, 1);
	for (int i = 0; i < 540; i++)
	{
		vertexColors[i] = color;
		color = vec4(1.0*rand() / RAND_MAX, 1.0*rand() / RAND_MAX, 1.0*rand() / RAND_MAX, 1);
	}
}

//apply transformation to the snowflake
void Snowflake::applyTransformation(mat4 input)
{
	model_matrix = input * model_matrix;
}

//snowflake destructor
Snowflake::~Snowflake()
{
}
