//
// A GLSL "Hellow World"
// Display a blue square
//

#include "Angel.h"  //includes gl.h, glut.h and other stuff...
void m_glewInitAndVersion(void);  //pre-implementation declaration (could do in header file)
void close(void);

//Mesh 0
GLuint buffer[2];
GLuint VAO[2];
GLuint aVAO;
GLuint aVBO;



const int NumVertices = 4;

// Vertices of a unit cube centered at origin, sides aligned with axes
vec2 points[4] = {
    vec2( 0.25, 0.25),
    vec2( 0.75, 0.25),
    vec2( 0.75, 0.75),
    vec2( 0.25, 0.75)
};

const int NumTriangleVertices = 3;
vec2 triangle[3] = {
	vec2(-1, -1),
	vec2(0, -1),
	vec2(0, 0),
};

const int NumFanVertices = 126;
int fans = 42;
GLfloat radius = 0.2;
GLfloat twoPi = 2.2*3.14159;


// RGBA colors
vec4 red = vec4( 1.0, 0.0, 0.0, 1.0 );
vec4 blue = vec4(0.0, 0.0, 1.0, 1.0);
vec4 randomColor[NumFanVertices];

GLuint program;
GLuint program1;
GLuint color_loc;
GLuint vPosition;
GLuint vPos;
GLuint cPos;



//----------------------------------------------------------------------------

// OpenGL initialization
void
init()
{
	
	
	glGenVertexArrays(2, VAO);


    // Create and initialize a buffer object
    glGenBuffers( 2, buffer);


    glBindBuffer( GL_ARRAY_BUFFER, buffer[0] );
    glBufferData( GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW );

	//Move triangle data onto a buffer
	glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);

	/*
	//Move circle data onto a buffer
	glBindBuffer(GL_ARRAY_BUFFER, aVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(circle), circle, GL_STATIC_DRAW);

	
	glBindBuffer(GL_ARRAY_BUFFER, abuffer[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(randomColor), randomColor, GL_STATIC_DRAW);
	*/

	// Load shaders and use the resulting shader program
    program = InitShader( "vshader00_v150.glsl", "fshader00_v150.glsl" );
    glUseProgram( program );

    // set up vertex arrays
    vPosition = glGetAttribLocation( program, "vPosition" );
	color_loc = glGetUniformLocation(program, "color");

	//Set up VAO
	//glGenVertexArrays(1,&VAO[0]);
	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER,buffer[0]);
    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );

	//Blue Triangle
	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	
	/******************Circle **************************************/
	vec2 circle[NumFanVertices];

	circle[0] = (0, 0);
	for (int j = 1; j <= fans +1; j++)
	{
		circle[j] = vec2(radius * cos((j)*twoPi / fans), radius*sin((j)*twoPi / fans));
		randomColor[0] = vec4(GLfloat(rand()) / GLfloat(RAND_MAX), GLfloat(rand()) / GLfloat(RAND_MAX), GLfloat(rand()) / GLfloat(RAND_MAX), 1);
		randomColor[j] = vec4(GLfloat(rand()) / GLfloat(RAND_MAX), GLfloat(rand()) / GLfloat(RAND_MAX), GLfloat(rand()) / GLfloat(RAND_MAX), 1);
	}

	//Setting up VAO
	
	glGenVertexArrays(1, &aVAO);
	glBindVertexArray(aVAO);


	//Create and initialize buffer object
	
	glGenBuffers(1, &aVBO);
	glBindBuffer(GL_ARRAY_BUFFER, aVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(circle) + sizeof(randomColor), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(circle), circle);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(circle), sizeof(randomColor), randomColor);
	

	program1 = InitShader("vshaderCircle.glsl", "fshaderCircle.glsl");
	glUseProgram(program1);
	
	//Initialize the vertex position attribute from the vertex shader
	vPos = glGetAttribLocation(program1, "vPosition");
	glEnableVertexAttribArray(vPos);
	glVertexAttribPointer(vPos, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	
	cPos = glGetAttribLocation(program1, "vColor");
	glEnableVertexAttribArray(cPos);
	glVertexAttribPointer(cPos, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(circle)));
	
		
	glClearColor( 1.0, 1.0, 1.0, 1.0 );
}



//----------------------------------------------------------------------------

void
display( void )
{
    glClear( GL_COLOR_BUFFER_BIT );

	glUseProgram(program);
	glBindVertexArray(VAO[0]);
	glUniform4fv(color_loc, 1, red);
	glDrawArrays( GL_TRIANGLE_FAN, 0, NumVertices );

	glBindVertexArray(VAO[1]);
	glUniform4fv(color_loc, 1, vec4(0, 0, 1, 1));
	glDrawArrays(GL_TRIANGLE_FAN, 0, NumTriangleVertices);

	glUseProgram(program1);
	glBindVertexArray(aVAO);
	glDrawArrays(GL_TRIANGLE_FAN, 0, fans);
	
	/*
	//circle();
	//glBindVertexArray(aVAO[0]);
	glBegin(GL_TRIANGLE_FAN);

		glVertex2f(0.0, 0.0);
		for (int i = 0; i < 361; i++)
		{
			glUniform4fv(color_loc, 1, vec4(float(rand()) / float(RAND_MAX), float(rand()) / float(RAND_MAX), float(rand()) / float(RAND_MAX), 1));
			//glColor3f(float(rand()) / float(RAND_MAX), float(rand()) / float(RAND_MAX), float(rand()) / float(RAND_MAX));
			glVertex2f(0.2*cos(i*PI / 180), 0.2*sin(i*PI / 180));
			//glDrawArrays(GL_TRIANGLE_FAN, 0, NumFanVertices);
		}
	glEnd();
	*/

	glFlush();
}

//----------------------------------------------------------------------------

void
keyboard( unsigned char key, int x, int y )
{
    switch( key ) {
	case 033:  // Escape key
	case 'q': case 'Q':
	    exit( EXIT_SUCCESS );
	    break;
    }
}

//----------------------------------------------------------------------------

int main( int argc, char **argv )
{
    glutInit( &argc, argv );
#ifdef __APPLE__
    glutInitDisplayMode( GLUT_3_2_CORE_PROFILE|GLUT_RGBA | GLUT_SINGLE);
#else
	glutInitDisplayMode( GLUT_RGBA | GLUT_SINGLE);
#endif
    glutInitWindowSize( 512, 512 );

    glutCreateWindow( "Alan Tsai HW1" );
	m_glewInitAndVersion();


    init();

    glutDisplayFunc( display );
    glutKeyboardFunc( keyboard );
	glutWMCloseFunc(close);

    glutMainLoop();
    return 0;
}

void m_glewInitAndVersion(void)
{
   fprintf(stdout, "OpenGL Version: %s\n", glGetString(GL_VERSION));
   fprintf(stdout, "GLSL Version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

#ifndef __APPLE__
   GLenum err = glewInit();
   if (GLEW_OK != err)
   {
   fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
   }
   fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
#endif
}

void close(){
	glDeleteBuffers(2, buffer);  //delete the buffers (free up space on GPU)

}