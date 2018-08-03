//SAMPLE CODE
//2D Graphics
//2 Objects Rendered using Triangles
//1 Set of lines rendered in black
//and Uniform Colors

#include "Angel.h"  //includes gl.h, glut.h and other stuff...


//Data for Square object
const int NumSquareVertices = 6;
int currentSquareIndex = 0;
vec2 squareVertices[6];
#define SQUARE_BUFFER 0

//Data for Triangle object
const int NumTriangleVertices = 3;
vec2 triangleVertices[]={vec2(-1,-1), vec2(0,0), vec2(0,-1)};
#define TRIANGLE_BUFFER 1

//Data for lines
const int NumLineVertices = 4;
vec2 lineVertices[] = {vec2(0,0), vec2(-0.4f, 0.8f), vec2(0.5f, 0.5f), vec2(-0.8f,0.1f)};
#define LINE_BUFFER 2

//Need 3 buffers:  1 for square vertices, 1 for triangle vertices, 1 for line vertices
GLuint buffers[3];
//Need 3 VAOs:  1 for square vertices, 1 for triangle vertices, 1 for line vertices
GLuint VAOs[3];

////SHADER STUFF////////
//Shader program
GLuint program;
//uniform variable locations
GLuint color_loc;
//attribute variable locations
GLuint vPosition_loc;


//Foward declarations of functions
void makeQuad(vec2, vec2, vec2, vec2);
void init();
void display();
void keyboard(unsigned char, int, int);
void close();

//----------------------------------------------------------------------------
int main( int argc, char **argv )
{
    glutInit( &argc, argv );	//initialize glut
#ifdef __APPLE__
    glutInitDisplayMode( GLUT_3_2_CORE_PROFILE|GLUT_RGBA | GLUT_SINGLE);
#else
    glutInitDisplayMode( GLUT_RGBA | GLUT_SINGLE);
#endif
    glutInitWindowSize( 512, 512 );	//set window size to be 512x512 pixels

    glutCreateWindow( "2D Graphics" );  //open a window with the title "2D Graphics"

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
	
	glGenVertexArrays(3,VAOs);

	// Create and initialize the buffers
    glGenBuffers( 3, buffers);
	
		
	makeQuad(vec2(-0.9f,-0.9f), vec2(0.0f, -0.9f), vec2(0, 0), vec2(-0.9f, 0));
    glBindBuffer( GL_ARRAY_BUFFER, buffers[SQUARE_BUFFER]);
    glBufferData( GL_ARRAY_BUFFER, sizeof(squareVertices),squareVertices, GL_STATIC_DRAW );

	//Move triangle data onto a buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffers[TRIANGLE_BUFFER]);
	glBufferData( GL_ARRAY_BUFFER, sizeof(triangleVertices),triangleVertices, GL_STATIC_DRAW );

	//Move line data onto a buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffers[LINE_BUFFER]);
	glBufferData( GL_ARRAY_BUFFER, sizeof(lineVertices),lineVertices, GL_STATIC_DRAW );


	//now load the shader and get the location of it's variables
	program = InitShader( "vshader00_v150.glsl", "fshader00_v150.glsl" );
    
	glUseProgram(program);
	vPosition_loc = glGetAttribLocation( program, "vPosition" );
	color_loc = glGetUniformLocation(program, "color");


	//Bind the attributes to each VAO
	//Blue rectangle
	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[SQUARE_BUFFER]);
    glEnableVertexAttribArray(vPosition_loc);
    glVertexAttribPointer( vPosition_loc, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
	
	
	//Red Triangle
	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[TRIANGLE_BUFFER]);
    glEnableVertexAttribArray(vPosition_loc);
    glVertexAttribPointer( vPosition_loc, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
	
	//Black Lines
	glBindVertexArray(VAOs[2]);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[LINE_BUFFER]);
    glEnableVertexAttribArray(vPosition_loc);
    glVertexAttribPointer( vPosition_loc, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
	
	//define color to use when color buffer is cleared
    glClearColor( 1.0, 1.0, 1.0, 1.0 ); 
}

//----------------------------------------------------------------------------

void display( void )
{
    glClear( GL_COLOR_BUFFER_BIT );  //clear out the color of the framebuffer
		
	//Render the square blue	
	glBindVertexArray(VAOs[0]);
	glUniform4fv(color_loc, 1, vec4(1,0,0,1));
	glDrawArrays( GL_TRIANGLES, 0, NumSquareVertices);
	

	
	//Render the triangle red
	glBindVertexArray(VAOs[1]);
	glUniform4fv(color_loc, 1, vec4(0,0,1,1));
	glDrawArrays( GL_TRIANGLES, 0, NumTriangleVertices);
	
	
	//Render the lines black
	glBindVertexArray(VAOs[2]);
	glUniform4fv(color_loc, 1, vec4(0,0,0,1));
	glLineWidth(4.0); //draw think lines
	glDrawArrays( GL_LINES, 0, NumLineVertices);
	

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
	glDeleteBuffers(3, buffers);  //delete the buffers (free up space on GPU)

}

//----------------------------------------------------------------------------

void makeQuad(vec2 a, vec2 b, vec2 c, vec2 d){
	//Triangle #1
	squareVertices[currentSquareIndex] = a;
	currentSquareIndex++;

	squareVertices[currentSquareIndex] = b;
	currentSquareIndex++;

	squareVertices[currentSquareIndex] = c;
	currentSquareIndex++;

	//Triangle #2
	squareVertices[currentSquareIndex] = c;
	currentSquareIndex++;

	squareVertices[currentSquareIndex] = d;
	currentSquareIndex++;

	squareVertices[currentSquareIndex] = a;
	currentSquareIndex++;
}
