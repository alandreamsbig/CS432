#include"cube.h"
#include"math.h"
#include"Camera.h"

//uniform variable locations
GLuint modelMatrixloc;
GLuint viewMatrixloc;

//attribute variable locations
GLuint vPositionloc;
GLuint vColorloc;

vec3 squareLocations1[4];
Camera * cb;
//Camera * p;

vec4 vertices[] = { vec4(-0.5,-0.5,0.5,1.0),vec4(-0.5,0.5,0.5,1.0),vec4(0.5,0.5,0.5,1.0),vec4(0.5,-0.5,0.5,1.0), vec4(-0.5,-0.5,-0.5,1.0),vec4(-0.5,0.5,-0.5,1.0),vec4(0.5,0.5,-0.5,1.0),vec4(0.5,-0.5,-0.5,1.0) };
vec4 potentialColors[] = { vec4(0,0,0,1), vec4(1,0,0,1), vec4(0,1,0,1), vec4(0,0,1,1), vec4(1,1,0,1), vec4(1,0,1,1),vec4(0,1,1,1),vec4(0.5f,0.2f,0.4f,1) };

cube::cube()
{
	program1 = InitShader("vshaderLighting_v150.glsl", "fshaderLighting_v150.glsl");
	vpos = glGetAttribLocation(program1, "vPosition");
	npos = glGetAttribLocation(program1, "vNormal");
	mmpos = glGetUniformLocation(program1, "model_matrix");
	vmpos = glGetUniformLocation(program1, "view_matrix");
	pmpos = glGetUniformLocation(program1, "proj_matrix");
	diffuse_loc = glGetUniformLocation(program1, "matDiffuse");
	spec_loc = glGetUniformLocation(program1, "matSpecular");
	ambient_loc = glGetUniformLocation(program1, "matAmbient");
	alpha_loc = glGetUniformLocation(program1, "matAlpha");

	build();
}

cube:: ~cube()
{
	glDeleteBuffers(1, &cVBO);
	glDeleteVertexArrays(1, &cVAO);

	
}

void cube::build()
{


	// Create and initialize the buffers
	glGenBuffers(1, &cVBO);
	glGenVertexArrays(1, &cVAO);

	//now load the shader and get the location of it's variables
	
	glUseProgram(program1);

	//Set up the data for the cube and move that data to a buffer
	buildCube();
	glBindVertexArray(cVAO);
	glBindBuffer(GL_ARRAY_BUFFER, cVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertexLocations) + sizeof(cubeVertexColors), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(cubeVertexLocations), cubeVertexLocations);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(cubeVertexLocations), sizeof(cubeVertexColors), cubeVertexColors);

	vPositionloc = glGetAttribLocation(program1, "vPosition");
	glEnableVertexAttribArray(vPositionloc);
	glVertexAttribPointer(vPositionloc, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	vColorloc = glGetAttribLocation(program1, "vColor");
	glEnableVertexAttribArray(vColorloc);
	glVertexAttribPointer(vColorloc, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(cubeVertexLocations)));

	modelMatrixloc = glGetUniformLocation(program1, "model_matrix");
	mat4 modelMatrix = Translate(2,2,-4)*RotateY(10.0)*RotateX(10.0)*mat4(1.0);  //rotate the model 10 degrees around the x-axis and then 10 degree around the y-axis
	glUniformMatrix4fv(modelMatrixloc, 1, GL_TRUE, modelMatrix);


}


void cube::makeQuad(int a, int b, int c, int d) {
	//Triangle #1
	cubeVertexLocations[currentCubeIndex] = vertices[a];
	cubeVertexColors[currentCubeIndex] = potentialColors[currentCubeIndex % 8];
	currentCubeIndex++;

	cubeVertexLocations[currentCubeIndex] = vertices[b];
	cubeVertexColors[currentCubeIndex] = cubeVertexColors[currentCubeIndex - 1];
	currentCubeIndex++;

	cubeVertexLocations[currentCubeIndex] = vertices[c];
	cubeVertexColors[currentCubeIndex] = cubeVertexColors[currentCubeIndex - 1];
	currentCubeIndex++;

	//Triangle #2
	cubeVertexLocations[currentCubeIndex] = vertices[c];
	cubeVertexColors[currentCubeIndex] = cubeVertexColors[currentCubeIndex - 1];
	currentCubeIndex++;

	cubeVertexLocations[currentCubeIndex] = vertices[d];
	cubeVertexColors[currentCubeIndex] = cubeVertexColors[currentCubeIndex - 1];
	currentCubeIndex++;

	cubeVertexLocations[currentCubeIndex] = vertices[a];
	cubeVertexColors[currentCubeIndex] = cubeVertexColors[currentCubeIndex - 1];
	currentCubeIndex++;
}

void cube::buildCube() {
	makeQuad(1, 0, 3, 2);  //front
	makeQuad(2, 3, 7, 6);  //right
	makeQuad(3, 0, 4, 7);  //bottom
	makeQuad(6, 5, 1, 2);  //top
	makeQuad(4, 5, 6, 7);  //back
	makeQuad(5, 4, 0, 1);  //left
}



void cube::setMaterial(vec4 a, vec4 d, vec4 s, float sh)
{
	diffuse = d;
	specular = s;
	ambient = a;
	shine = sh;
}

//----------------------------------------------------------------------------

void cube::drawCube(Camera* cb, vector<Light>lights)
{

	glUseProgram(program1);
	glBindVertexArray(cVAO);
	viewMatrixloc = glGetUniformLocation(program1, "view_matrix");
	glUniformMatrix4fv(viewMatrixloc, 1, GL_TRUE, cb->view_matrix);
	GLuint projMatrixloc = glGetUniformLocation(program1, "proj_matrix");
	glUniformMatrix4fv(projMatrixloc, 1, GL_TRUE, cb->proj_matrix);
	
	
	glUniform4fv(diffuse_loc, 1, diffuse);
	glUniform4fv(spec_loc, 1, specular);
	glUniform4fv(ambient_loc, 1, ambient);
	glUniform1f(alpha_loc, shine);


	
	GLuint light_loc = glGetUniformLocation(program1, "lightPos");
	glUniform4fv(light_loc, 1, lights[0].getPosition());
	GLuint ambient_loc2 = glGetUniformLocation(program1, "lightAmbient");
	glUniform4fv(ambient_loc2, 1, lights[0].getAmbient());
	GLuint diffuse_loc2 = glGetUniformLocation(program1, "lightDiffuse");
	glUniform4fv(diffuse_loc2, 1, lights[0].getDiffuse());
	GLuint specular_loc2 = glGetUniformLocation(program1, "lightSpecular");
	glUniform4fv(specular_loc2, 1, lights[0].getSpecular());
	
	glDrawArrays(GL_TRIANGLES, 0, numVertices);
}

