#include "Shape.h"
Shape::Shape() {
	//load the shader and get the location of it's variables
	program = InitShader("vshaderLighting_v150.glsl", "fshaderLighting_v150.glsl");
	build();
}

void Shape::build(){
		glGenBuffers(1,&VBO);
		glGenVertexArrays(1,&VAO);

		buildTriangle();  //build the triangle (set the vertex locations and normals)

		//move the data onto the buffer
		glBindVertexArray(VAO);
		glBindBuffer( GL_ARRAY_BUFFER, VBO);
		glBufferData( GL_ARRAY_BUFFER, sizeof(vertexLocations)+sizeof(vertexNormals),NULL, GL_STATIC_DRAW );
		glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(vertexLocations),vertexLocations);
		glBufferSubData(GL_ARRAY_BUFFER,sizeof(vertexLocations),sizeof(vertexNormals),vertexNormals);

		//link the vertex attributes with the buffer
		GLuint vPosition = glGetAttribLocation( program, "vPosition" );
		glEnableVertexAttribArray( vPosition );
		glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
	
		GLuint vNormal = glGetAttribLocation(program, "vNormal");
		glEnableVertexAttribArray( vNormal );
		glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertexLocations)) );

		
}

//on destroy, delete the buffer (cleanup)
Shape::~Shape(){
	glDeleteBuffers(1,&VBO);
	glDeleteVertexArrays(1, &VAO);
}

//set the materials
void Shape::setMaterial(vec4 d, vec4 a, vec4 s, float sh){
	matDiffuse = d;
	matAmbient = a;
	matSpecular = s;
	shininess = sh;
}

void Shape::buildTriangle(){
	//set up the vertices
	vertexLocations[0] = vec4(-1,0,0,1);
	vertexLocations[1] = vec4(1,0,0,1);
	vertexLocations[2] = vec4(0,0,-1,1);

	//compute two of the edges
	vec4 e1 = vertexLocations[1]-vertexLocations[0];
	vec4 e2 = vertexLocations[2]-vertexLocations[0];

	//use the cross product to get the direction of the triangle's normal
	vec3 n = cross(vec3(e1.x,e1.y,e1.z),vec3(e2.x,e2.y,e2.z));
	n = normalize(n);
	//use computed normal for each vertex of the triangle
	vertexNormals[0] = n;
	vertexNormals[1] = n;
	vertexNormals[2] = n;
	
}

void Shape::draw(Camera cam, vector<Light>lights){
	
	glBindVertexArray(VAO);
	glUseProgram(program);

	//set the transformation matrices
	GLuint model_loc = glGetUniformLocation(program,"model_matrix");
	glUniformMatrix4fv(model_loc,1,GL_TRUE,modelmatrix);
	GLuint view_loc = glGetUniformLocation(program, "view_matrix");
	glUniformMatrix4fv(view_loc, 1, GL_TRUE, cam.getViewMatrix());
	GLuint proj_loc = glGetUniformLocation(program, "proj_matrix");
	glUniformMatrix4fv(proj_loc, 1, GL_TRUE, cam.getProjectionMatrix());

	//set the materials
	GLuint ambient_loc = glGetUniformLocation(program,"matAmbient");
	glUniform4fv(ambient_loc,1,matAmbient);
	GLuint diffuse_loc = glGetUniformLocation(program,"matDiffuse");
	glUniform4fv(diffuse_loc,1,matDiffuse);
	GLuint specular_loc = glGetUniformLocation(program,"matSpecular");
	glUniform4fv(specular_loc,1,matSpecular);
	GLuint alpha_loc = glGetUniformLocation(program,"matAlpha");
	glUniform1f(alpha_loc,shininess);


	//set up the lighting
	//light stuff
	GLuint light_loc = glGetUniformLocation(program, "lightPos");
	glUniform4fv(light_loc, 1, lights[0].getPosition());
	ambient_loc = glGetUniformLocation(program, "lightAmbient");
	glUniform4fv(ambient_loc, 1, lights[0].getAmbient());
	diffuse_loc = glGetUniformLocation(program, "lightDiffuse");
	glUniform4fv(diffuse_loc, 1, lights[0].getDiffuse());
	specular_loc = glGetUniformLocation(program, "lightSpecular");
	glUniform4fv(specular_loc, 1, lights[0].getSpecular());
	
	//draw!
	glDrawArrays(GL_TRIANGLES,0,3);

}


