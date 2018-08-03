//SAMPLE CODE
//3D Graphics


#include "Angel.h"  //includes gl.h, glut.h and other stuff...
#include "Camera.h"

//Data for Cube object
const int NumCubeVertices = 6*2*3*2;
int currentCubeIndex = 0;
vec4 cubeVertexLocations[6*2*3*2];
vec4 cubeVertexColors[6*2*3*2];
#define SQUARE_BUFFER 0
vec4 vertices[] = { vec4(0,0,0.5,1.0),vec4(0.3,0.5,0.5,1.0),vec4(0.5,0,0.5,1.0),vec4(0.3,-0.5,0.5,1.0), vec4(-0.3,-0.5,0.5,1.0), vec4(-0.5,0,0.5,1.0), vec4(-0.3, 0.5,0.5,1.0),vec4(0,0,-0.5,1.0),vec4(0.3,0.5,-0.5,1.0),vec4(0.5,0,-0.5,1.0),vec4(0.3,-0.5,-0.5,1.0), vec4(-0.3,-0.5,-0.5,1.0), vec4(-0.5,0,-0.5,1.0), vec4(-0.3, 0.5,-0.5,1.0) };
vec4 potentialColors[] = {vec4(0,0,0,1), vec4(0,0,0,1), vec4(1,0,0,1),vec4(0,0,1,1),vec4(1,1,0,1),vec4(0,1,1,1), vec4(0,1,0,1),vec4(1,0.5,0,1),vec4(1,1,0,1), vec4(1,1,0,1) };


//Need 1 buffers:  1 for cube data
GLuint buffer;
GLuint VAO;
GLuint fbuffer;
GLuint fVAO;

////SHADER STUFF////////
//Shader program
GLuint program;
GLuint program1;
//uniform variable locations
GLuint modelMatrix_loc;
GLuint viewMatrix_loc;
//attribute variable locations
GLuint vPosition_loc;
GLuint vColor_loc;
GLuint fPos;
GLuint fColor;
bool rotation = false;
Camera* k;

//Foward declarations of functions
void buildCube();
void makeQuad(int, int, int);
void init();
void display();
void keyboard(unsigned char, int, int);
void close();
void special(int, int, int);

//----------------------------------------------------------------------------
int main( int argc, char **argv )
{
    glutInit( &argc, argv );	//initialize glut
	#ifdef __APPLE__
    glutInitDisplayMode( GLUT_3_2_CORE_PROFILE|GLUT_RGBA | GLUT_SINGLE|GLUT_DEPTH);
#else
    glutInitDisplayMode( GLUT_RGB | GLUT_SINGLE|GLUT_DEPTH);
#endif
    glutInitWindowSize( 512, 512 );	//set window size to be 512x512 pixels

    glutCreateWindow( "TsaiAlanHW3" );  //open a window with the title "2D Graphics"

	//initialize glew if necessary (don't need to on Macs)
#ifndef __APPLE__
	GLenum err = glewInit();
#endif

    init();  //do some initialize for our program

	//set up the callback functions
    glutDisplayFunc( display );  //REQUIRED.  What to do when it's time to draw
    glutKeyboardFunc( keyboard );  //What to do if a keyboard event is detected
	glutSpecialFunc(special);
	glutWMCloseFunc(close);
    glutMainLoop();  //start infinite loop, listening for events
    return 0;
}

/*
void timerCallback(int value)
{

	

	for (unsigned int i = 0; i < vertices.size(); i++)

		vertices[i]->rotation();

	for (unsigned int j = 0; j < vertices.size(); j++)
		vertices[j]->rotation();

	if (rotation)
	{
		glutTimerFunc(50, timerCallback, value);
	}

	glutPostRedisplay();


}
*/

//Initialization
void init()
{
	k = new Camera();

    // Create and initialize the buffers
    glGenBuffers( 1, &buffer);
	glGenVertexArrays(1,&VAO);
	//glGenBuffers(1, &fbuffer);
	//glGenVertexArrays(1, &fVAO);

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
	
	
	mat4 viewMatrix = k->view_matrix;//mat4(vec4(1, 0, 0, 0), vec4(0, 1, 0, 0), vec4(0, 0, -1, 0), vec4(0, 0, 0, 1));
	mat4 modelMatrix = Translate(0, 0, -2)*RotateY(-50.0)*RotateX(30.0)*mat4(1.0); //rotate the model 10 degrees around the x-axis and then 10 degree around the y-axis
	glUniformMatrix4fv(modelMatrix_loc, 1, GL_TRUE, modelMatrix);
	viewMatrix_loc = glGetUniformLocation(program, "viewMatrix");
	glUniformMatrix4fv(viewMatrix_loc, 1, GL_TRUE, viewMatrix);
	
	//program1 = InitShader("fFrame.glsl", "vFrame.glsl");
	
	/*
	glBindVertexArray(fVAO);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, fbuffer);
	glUseProgram(program1);
	fPos = glGetAttribLocation(program1, "vPosition");
	glEnableVertexAttribArray(fPos);
	glVertexAttribPointer(fPos, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	*/
	/*
	glBindVertexArray(fVAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, fbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertices) + sizeof(frameIndices), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(frameIndices), frameIndices);
	*/
	
	glEnable(GL_DEPTH_TEST); //since we're doing 3D graphics, enable the Z-buffer depth test

	//define color to use when color buffer is cleared
    glClearColor( 1.0, 1.0, 1.0, 1.0 ); 
}

//----------------------------------------------------------------------------

void display( void )
{

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT );  //clear out the color of the framebuffer and the depth info from the depth buffer

	glUseProgram(program);
	glBindVertexArray(VAO);
	viewMatrix_loc = glGetUniformLocation(program, "view_Matrix");
	glUniformMatrix4fv(viewMatrix_loc, 1, GL_TRUE, k->view_matrix);
	GLuint projMatrix_loc = glGetUniformLocation(program, "proj_matrix");
	glUniformMatrix4fv(projMatrix_loc, 1, GL_TRUE, k->proj_matrix);
	glDrawArrays(GL_TRIANGLES, 0,72);

	/*
	glLineWidth(3.0);
	glUseProgram(program1);
	glBindVertexArray(fVAO);
	GLuint color = glGetUniformLocation(program1, "color");
	glUniform4fv(color, 1, vec4(1, 0, 0, 1));
	glDrawElements(GL_LINES, 24, GL_UNSIGNED_BYTE, BUFFER_OFFSET(sizeof(vertices)));
	*/
	glFlush();
}

//----------------------------------------------------------------------------

void keyboard( unsigned char key, int x, int y )
{
	switch (key) {

	case 'X':
	{

		k->pitchUp();
		break;
	}
	case 'x':
	{

		k->pitchDown();
		break;
	}
	case 'C':
	{

		k->YawClockwise();
		break;
	}
	case 'c':
	{

		k->YawCounterwise();
		break;
	}
	case 'Z':
	{

		k->RollClockwise();
		break;
	}
	case 'z':
	{

		k->RollCounterwise();
		break;
	}
	case 'P':
	{
		bool ortho = true;
		k->getProj(ortho);
		break;
	}
	case 'p':
	{
		bool proj = false;
		k->getProj(proj);
		break;
	}
	case 033:  // Escape key
	case 'q': case 'Q':
		exit(EXIT_SUCCESS);
		break;
	}
	glutPostRedisplay();
}

void special(int key, int x, int y)
{

	switch (key) {
	
		case GLUT_KEY_UP:
		{
		
			k->MoveTowards();
			break;
		}
		case GLUT_KEY_DOWN:
		{
			
			k->MoveAway();
			break;

		}
		case GLUT_KEY_LEFT:
		{
			k->MoveLeft();
			break;
		}
		case GLUT_KEY_RIGHT:
		{
			k->MoveRight();
			break;
		}
	}
		
	glutPostRedisplay();
}
void close(){
	glDeleteBuffers(1, &buffer);  //delete the buffers (free up space on GPU)

}

//----------------------------------------------------------------------------

void makeQuad(int a, int b, int c){
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

	/*
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
	*/
	
}

void buildCube(){
	


	makeQuad(0, 2, 1);
	makeQuad(0, 1, 6);
	makeQuad(0, 6, 5);
	makeQuad(0, 5, 4);
	makeQuad(0, 4, 3);
	makeQuad(0, 3, 2);

	makeQuad(1, 2, 8);
	makeQuad(8, 2, 9);
	makeQuad(2, 3, 9);
	makeQuad(9, 3, 10);

	makeQuad(3, 4, 10);
	makeQuad(4, 11, 10);

	makeQuad(6, 1, 13);
	makeQuad(1, 8, 13);


	makeQuad(7, 9, 8);
	makeQuad(7, 8, 13);
	makeQuad(7, 13, 12);
	makeQuad(7, 12, 11);
	makeQuad(7, 11, 10);
	makeQuad(7, 10, 9);

	makeQuad(6, 5, 13);
	makeQuad(5, 12, 13);

	makeQuad(5, 4, 12);
	makeQuad(4, 11, 12);

	/*
	makeQuad(0,2,1,6);	//front
	makeQuad(0, 6, 5, 4);
	makeQuad(0, 4, 3, 2);
	
	
	makeQuad(1, 2, 9, 8);  //right	
	makeQuad(2, 3, 10, 9);
	makeQuad(6, 1, 8, 13);  //top
	
	makeQuad(12, 11, 4, 5);  //left
	makeQuad(13, 12, 5, 6);
	makeQuad(3, 4, 11, 10);  //bottom
	
	

	makeQuad(7, 9, 8, 13);//back
	makeQuad(7, 13, 12, 11);
	makeQuad(7, 11, 10, 9);
	*/
}
