//SAMPLE CODE
//Lighting
//1 Triangle
//1 Distance Light Source

#include "Angel.h"  //includes gl.h, glut.h and other stuff...
#include "QuadTextured.h"
#include "Camera.h"
#include "Light.h"


vector<Light> lights;
Camera cam;

QuadTextured *myQuad;

//Foward declarations of functions
void init();
void display();
void resize(int width, int height);
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

    glutCreateWindow( "Lighting" );  //open a window with the title "2D Graphics"

	//initialize glew if necessary (don't need to on Macs)
	#ifndef __APPLE__
	GLenum err = glewInit();
	#endif

    init();  //do some initialize for our program

	//set up the callback functions
    glutDisplayFunc( display );  //REQUIRED.  What to do when it's time to draw
    glutKeyboardFunc( keyboard );  //What to do if a keyboard event is detected
	glutWMCloseFunc(close);
	glutReshapeFunc(resize);  //use for recomputing projection matrix on reshape
    glutMainLoop();  //start infinite loop, listening for events
    return 0;
}


//Initialization
void init()
{
	//set up the camera
	cam.positionCamera(vec4(0, 2, 0, 1), vec4(0, 1, 0, 0), vec4(0, 0, -1, 0), vec4(1, 0, 0, 0));
	
	//set up the lights
	lights.push_back(Light(vec4(2, 1, 0, 1), vec4(1, 1, 1, 1), vec4(0.2f, 0.2f, 0.2f, 1), vec4(1, 1, 1, 1)));  //the light

	//make a triangle and set its material
	myQuad = new QuadTextured();
	myQuad->setMaterial(vec4(1,0.8f,0,1),vec4(1,0,1,1),vec4(1,0.8f,0,1),100);
	
	
	glEnable(GL_DEPTH_TEST); //since we're doing 3D graphics, enable the Z-buffer depth test
	
	//define color to use when color buffer is cleared
    glClearColor( 1.0, 1.0, 1.0, 1.0 ); 
}

//----------------------------------------------------------------------------

void display( void )
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );  //clear out the color of the framebuffer and the depth info from the depth buffer
		
	myQuad->draw(cam,lights);
		
	glFlush();
}

//----------------------------------------------------------------------------

void resize(int w, int h){
	glViewport(0,0,(GLsizei) w, (GLsizei) h);
	cam.setProjection(Perspective(65.0, GLfloat(w / h), 1.0, 100.0));
}
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
	delete myQuad;

}

//----------------------------------------------------------------------------
