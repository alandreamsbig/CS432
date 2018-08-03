#include "Smoke.h"


void Smoke::cleanup()
{
	glDeleteBuffers(1, &buffer);
}

//initialize the smoke particles with random position
void Smoke::initParticles()
{
	for (int i = 0; i < numSmokeParticles; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			particles[i].position[j] = .9*(float)rand() / RAND_MAX;
			if (j != 1 && 20 * rand() / RAND_MAX < 10.0) { particles[i].position[j] *= -1.0; }
			particles[i].velocity = 1.0*(float)rand() / RAND_MAX;
		}
		particles[i].position.w = 1.0;
		particles[i].position.y += .001;

		particles[i].velocity.x = 0.0;
		particles[i].velocity.z = 0.0;
		particles[i].velocity.w = 0.0;

		particles[i].velocity /= 10;

		particles[i].steps = 0;
		particles[i].stepMax = 15.0*rand() / RAND_MAX;
	}
}

//apply transformation to the smoke
void Smoke::applyTransformation(mat4 trans)
{
	model_matrix = trans*model_matrix;
	modelMatrix_loc = glGetUniformLocation(program, "model_matrix");
	glUniformMatrix4fv(modelMatrix_loc, 1, GL_TRUE, model_matrix);
}

//initialize the smoke with colors
void Smoke::initColors()
{
	for (int i = 1; i < numSmokeParticles; i++)
	{
		particles[i].color = vec4(250.0 / 255.0, 66.0 / 255.0, 22.0 / 255.0, 0);

		if (1.0*(float)rand() / RAND_MAX < 0.5)
		{
			particles[i].color -= vec4((1.0*(float)rand() / RAND_MAX) / 10.0, 0, 0, 0);
		}
		else
		{
			particles[i].color += vec4((1.0*(float)rand() / RAND_MAX) / 10.0, 0, 0, 0);
		}
		particles[i].color.w = 0;
	}
}

//construct the smoke
Smoke::Smoke()
{
	initParticles();
	initColors();
	particles[0].color = vec4(250.0 / 255.0, 66.0 / 255.0, 22.0 / 255.0, 0);
	particles[0].position = vec4(0, 0, 0, 1);
	particles[0].velocity = vec4(0, 0, 0, 0);

	view_matrix = mat4(1.0);
	projection_matrix = mat4(1.0);

	//create the smoke buffer
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &buffer);

	//move the data to the buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(particlePoints) + sizeof(particleColors), NULL, GL_STATIC_DRAW);


	//now load the shader and get the location of it's variables
	program = InitShader("vshader01_v150_colorFromBuffer.glsl", "fshader01_v150_colorFromBuffer.glsl");
	glUseProgram(program);

	//link the vertex attributes to the buffer
	vPosition_loc = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition_loc);
	glVertexAttribPointer(vPosition_loc, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	vColor_loc = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(vColor_loc);
	glVertexAttribPointer(vColor_loc, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(particlePoints)));


	model_matrix = Translate(-5, 0.01, -2)*mat4(1.0);//Scale(0.1);//Translate(5, 2, 0)*Scale(0.1)* mat4(1.0);

	modelMatrix_loc = glGetUniformLocation(program, "model_matrix");
	glUniformMatrix4fv(modelMatrix_loc, 1, GL_TRUE, model_matrix);

	viewMatrix_loc = glGetUniformLocation(program, "view_matrix");
	glUniformMatrix4fv(viewMatrix_loc, 1, GL_TRUE, view_matrix);

	projectionMatrix_loc = glGetUniformLocation(program, "projection_matrix");
	glUniformMatrix4fv(projectionMatrix_loc, 1, GL_TRUE, projection_matrix);


}

//draw the smoke
void Smoke::draw()
{
	glBindVertexArray(VAO);
	glUseProgram(program);

	glBindBuffer(GL_ARRAY_BUFFER, buffer);

	for (int i = 0; i < numSmokeParticles; i++)
	{
		particlePoints[i] = particles[i].position;
		particleColors[i] = particles[i].color;
	}

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(particlePoints), particlePoints);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(particlePoints), sizeof(particleColors), particleColors);
	
	modelMatrix_loc = glGetUniformLocation(program, "model_matrix");
	glUniformMatrix4fv(modelMatrix_loc, 1, GL_TRUE, model_matrix);

	viewMatrix_loc = glGetUniformLocation(program, "view_matrix");
	glUniformMatrix4fv(viewMatrix_loc, 1, GL_TRUE, view_matrix);

	projectionMatrix_loc = glGetUniformLocation(program, "projection_matrix");
	glUniformMatrix4fv(projectionMatrix_loc, 1, GL_TRUE, projection_matrix);

	//glPointSize(6.0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, numSmokeParticles);
}


//smoke destructor
Smoke::~Smoke()
{
}
