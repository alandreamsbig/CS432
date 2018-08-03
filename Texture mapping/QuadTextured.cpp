#include "QuadTextured.h"

QuadTextured::QuadTextured() {
	program = InitShader("vshaderLighting_v150.glsl", "fshaderLighting_v150.glsl");
	glUseProgram(program);

	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);

	build();

	//move the data onto the buffer
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexLocations) + sizeof(vertexNormals) + sizeof(vertexTextureLocations), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertexLocations), vertexLocations);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertexLocations), sizeof(vertexNormals), vertexNormals);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertexLocations) + sizeof(vertexNormals), sizeof(vertexTextureLocations), vertexTextureLocations);

	//link the vertex attributes with the buffer
	GLuint vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	GLuint vNormal = glGetAttribLocation(program, "vNormal");
	glEnableVertexAttribArray(vNormal);
	glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertexLocations)));

	GLuint vTexture = glGetAttribLocation(program, "vTexture");
	glEnableVertexAttribArray(vTexture);
	glVertexAttribPointer(vTexture, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertexLocations) + sizeof(vertexNormals)));

	//get the texture data for the quad
	glGenTextures(1, &texture);
	int imgsize = 512;
	GLubyte *data = ppmRead("crate_texture.ppm", &imgsize, &imgsize);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgsize, imgsize, 0, GL_RGB, GL_UNSIGNED_BYTE, data);  //move the data onto the GPU
	delete[] data;  //dont' need this data now that its on the GPU

	//set the texturing parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

void QuadTextured::build(){
	
		index = 0;
		makeQuad(vec4(0,0,0,1), vec4(1,0,0,1),vec4(1,0,-1,1), vec4(0,0,-1,1));
}

//on destroy, delete the buffer (cleanup)
QuadTextured::~QuadTextured(){
	glDeleteBuffers(1,&VBO);
}


void QuadTextured::draw(Camera cam, vector<Light> lights){
	glBindVertexArray(VAO);
	glUseProgram(program);

	GLuint light_loc = glGetUniformLocation(program, "lightPos");
	glUniform4fv(light_loc, 1, lights[0].getPosition());

	GLuint diffuse_loc = glGetUniformLocation(program, "lightDiffuse");
	glUniform4fv(diffuse_loc, 1, lights[0].getDiffuse());

	diffuse_loc = glGetUniformLocation(program, "matDiffuse");
	glUniform4fv(diffuse_loc, 1, matDiffuse);

	GLuint spec_loc = glGetUniformLocation(program, "lightSpecular");
	glUniform4fv(spec_loc, 1, lights[0].getSpecular());

	spec_loc = glGetUniformLocation(program, "matSpecular");
	glUniform4fv(spec_loc, 1, matSpecular);

	GLuint ambient_loc = glGetUniformLocation(program, "lightAmbient");
	glUniform4fv(ambient_loc, 1, lights[0].getAmbient());

	ambient_loc = glGetUniformLocation(program, "matAmbient");
	glUniform4fv(ambient_loc, 1, matAmbient);

	GLuint alpha_loc = glGetUniformLocation(program, "matAlpha");
	glUniform1f(alpha_loc, shininess);

	GLuint model_loc = glGetUniformLocation(program, "model_matrix");
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, modelmatrix);

	GLuint view_loc = glGetUniformLocation(program, "view_matrix");
	glUniformMatrix4fv(view_loc, 1, GL_TRUE, cam.getViewMatrix());

	GLuint proj_loc = glGetUniformLocation(program, "proj_matrix");
	glUniformMatrix4fv(proj_loc, 1, GL_TRUE, cam.getProjectionMatrix());

	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(program, "textureID"), 0);
	
	glDrawArrays( GL_TRIANGLES, 0, 6);


}

//set the materials
void QuadTextured::setMaterial(vec4 d, vec4 a, vec4 s, float sh){
	matDiffuse = d;
	matAmbient = a;
	matSpecular = s;
	shininess = sh;
		
}


void QuadTextured::makeQuad(vec4 a, vec4 b, vec4 c, vec4 d){
	vec4 e1 = b-a;
	vec4 e2 = c-a;
	vec3 n = cross(vec3(e1.x,e1.y,e1.z),vec3(e2.x,e2.y,e2.z));
	n = normalize(n);  //all vertices of the quad get the same normal

	
	//Triangle #1
	vertexLocations[index] = a;
	vertexNormals[index] = n;
	vertexTextureLocations[index] = vec2(0,0);
	index++;
	
	vertexLocations[index] = b;
	vertexNormals[index] = n;
	vertexTextureLocations[index] = vec2(1,0);
	index++;

	vertexLocations[index] = c;
	vertexNormals[index] = n;
	vertexTextureLocations[index] = vec2(1,1);
	index++;

	
	//Triangle #2
	vertexLocations[index] = c;
	vertexNormals[index] = n;
	vertexTextureLocations[index] = vec2(1,1);
	index++;
	
	vertexLocations[index] = d;
	vertexNormals[index] = n;
	vertexTextureLocations[index] = vec2(0,1);
	index++;

	vertexLocations[index] = a;
	vertexNormals[index] = n;
	vertexTextureLocations[index] = vec2(0,0);
	index++;
	
}



