//SAMPLE CODE
//3D Graphics


#include "Angel.h"  //includes gl.h, glut.h and other stuff...


//Data for Cube object
const int NumCubeVertices = 6*2*3;
int currentCubeIndex = 0;
vec4 cubeVertexLocations[6*2*3];
vec4 cubeVertexColors[6*2*3];
#define SQUARE_BUFFER 0
vec4 vertices[] = {vec4(-0.5,-0.5,0.5,1.0),vec4(-0.5,0.5,0.5,1.0),vec4(0.5,0.5,0.5,1.0),vec4(0.5,-0.5,0.5,1.0), vec4(-0.5,-0.5,-0.5,1.0),vec4(-0.5,0.5,-0.5,1.0),vec4(0.5,0.5,-0.5,1.0),vec4(0.5,-0.5,-0.5,1.0)};
vec4 potentialColors[] = {vec4(0,0,0,1), vec4(1,0,0,1), vec4(0,1,0,1), vec4(0,0,1,1), vec4(1,1,0,1), vec4(1,0,1,1),vec4(0,1,1,1),vec4(0.5f,0.2f,0.4f,1)};


//Need 1 buffers:  1 for cube data
GLuint buffer;
GLuint VAO;

////SHADER STUFF////////
//Shader program
GLuint program;
//uniform variable locations
GLuint modelMatrix_loc;
//attribute variable locations
GLuint vPosition_loc;
GLuint vColor_loc;


//Foward declarations of functions
void buildCube();
void makeQuad(int, int, int, int);
void init();
void display();
void keyboard(unsigned char, int, int);
void close();

//----------------------------------------------------------------------------
int main( int argc, char **argv )
{
    glutInit( &argc, argv );	//initialize glut
	#ifdef __APPLE__
    glutInitDisplayMode( GLUT_3_2_CORE_PROFILE|GLUT_RGBA | GLUT_SINGLE|GLUT_DEPTH);
#else
    glutInitDisplayMode( GLUT_RGBA | GLUT_SINGLE|GLUT_DEPTH);
#endif
    glutInitWindowSize( 512, 512 );	//set window size to be 512x512 pixels

    glutCreateWindow( "3D Graphics" );  //open a window with the title "2D Graphics"

	//initialize glew if necessary (don't need to on Macs)
#ifndef __APPLE__
	GLenum err = glewInit();
#endif

    init();  //do some initialize for our program

	//set up the callback functions
    glutDisplayFunc( display );  //REQUIRED.  What to do when it's time to draw
    glutKeyboardFunc( keyboard );  //What to do if a keyboard event is detected
	glutWMCloseFunc(close);
    glutMainLoop();  //start infinite loop, listening for events
    return 0;
}

//Initialization
void init()
{
	

    // Create and initialize the buffers
    glGenBuffers( 1, &buffer);
	glGenVertexArrays(1,&VAO);

	//now load the shader and get the location of it's variables
	program = InitShader( "vshader01_v150.glsl", "fshader01_v150.glsl" );
	glUseProgram(program);
	
	//Set up the data for the cube and move that data to a buffer
	buildCube();
	glBindVertexArray(VAO);
    glBindBuffer( GL_ARRAY_BUFFER, buffer);
    glBufferData( GL_ARRAY_BUFFER, sizeof(cubeVertexLocations)+sizeof(cubeVertexColors),NULL, GL_STATIC_DRAW );
	glBufferSubData(GL_ARRAY_BUFFER,0, sizeof(cubeVertexLocations),cubeVertexLocations);
	glBufferSubData(GL_ARRAY_BUFFER,sizeof(cubeVertexLocations),sizeof(cubeVertexColors),cubeVertexColors);

	vPosition_loc = glGetAttribLocation( program, "vPosition" );
	glEnableVertexAttribArray(vPosition_loc);
    glVertexAttribPointer( vPosition_loc, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );

	vColor_loc = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(vColor_loc);
	glVertexAttribPointer(vColor_loc,4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(cubeVertexLocations)));

	modelMatrix_loc = glGetUniformLocation(program,"model_matrix");
	mat4 modelMatrix = RotateY(10.0)*RotateX(10.0)*mat4(1.0);  //rotate the model 10 degrees around the x-axis and then 10 degree around the y-axis
	glUniformMatrix4fv(modelMatrix_loc,1,GL_TRUE,modelMatrix);

	GLuint viewMatrix_loc = glGetUniformLocation(program, "view_matrix");
	mat4 viewMatrix = mat4(vec4(1, 0, 0, 0), vec4(0, 1, 0, 0), vec4(0, 0, -1, 0), vec4(0, 0, 0, 1));
	glUniformMatrix4fv(viewMatrix_loc, 1, GL_TRUE, viewMatrix);

	glEnable(GL_DEPTH_TEST); //since we're doing 3D graphics, enable the Z-buffer depth test

	//define color to use when color buffer is cleared
    glClearColor( 1.0, 1.0, 1.0, 1.0 ); 
}

//----------------------------------------------------------------------------

void display( void )
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );  //clear out the color of the framebuffer and the depth info from the depth buffer

	glUseProgram(program);
	glBindVertexArray(VAO);
	glDrawArrays( GL_TRIANGLES, 0, NumCubeVertices);
	
	glFlush();
}

//----------------------------------------------------------------------------

void keyboard( unsigned char key, int x, int y )
{
    switch( key ) {
	case 033:  // Escape key
	case 'q': case 'Q':
	    exit( EXIT_SUCCESS );
	    break;
    }
}

void close(){
	glDeleteBuffers(1, &buffer);  //delete the buffers (free up space on GPU)

}

//----------------------------------------------------------------------------

void makeQuad(int a, int b, int c, int d){
	//Triangle #1
	cubeVertexLocations[currentCubeIndex] = vertices[a];
	cubeVertexColors[currentCubeIndex] = potentialColors[currentCubeIndex%8];
	currentCubeIndex++;

	cubeVertexLocations[currentCubeIndex] = vertices[b];
	cubeVertexColors[currentCubeIndex] = cubeVertexColors[currentCubeIndex-1];
	currentCubeIndex++;

	cubeVertexLocations[currentCubeIndex] = vertices[c];
	cubeVertexColors[currentCubeIndex] = cubeVertexColors[currentCubeIndex-1];
	currentCubeIndex++;

	//Triangle #2
	cubeVertexLocations[currentCubeIndex] = vertices[c];
	cubeVertexColors[currentCubeIndex] = cubeVertexColors[currentCubeIndex-1];
	currentCubeIndex++;

	cubeVertexLocations[currentCubeIndex] = vertices[d];
	cubeVertexColors[currentCubeIndex] = cubeVertexColors[currentCubeIndex-1];
	currentCubeIndex++;

	cubeVertexLocations[currentCubeIndex] = vertices[a];
	cubeVertexColors[currentCubeIndex] = cubeVertexColors[currentCubeIndex-1];
	currentCubeIndex++;
}

void buildCube(){
	makeQuad(1,0,3,2);  //front
	makeQuad(2,3,7,6);  //right
	makeQuad(3,0,4,7);  //bottom
	makeQuad(6,5,1,2);  //top
	makeQuad(4,5,6,7);  //back
	makeQuad(5,4,0,1);  //left
}
