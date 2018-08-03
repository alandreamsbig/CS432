//SAMPLE CODE
//Lighting
//1 Triangle
//1 Distance Light Source

#include "Angel.h"  //includes gl.h, glut.h and other stuff...
#include "Shape.h"
#include "Light.h"
#include "Camera.h"


Camera camera;

//Foward declarations of functions
void init();
void display();
void resize(int width, int height);
void keyboard(unsigned char, int, int);
void close();

//objects
vector<Light> lights;
Shape *myTriangle;

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
	//make a triangle and set its material
	myTriangle = new Shape();
	myTriangle->setMaterial(vec4(1,0.8f,0,1),vec4(1,0,1,1),vec4(1,0.8f,0,1),100);
	myTriangle->setModelMatrix(Scale(3, 1, 3));  //scale it

	//camera stuff	
	camera.positionCamera(vec4(0,10,0,0), vec4(0,1,0,0), vec4(0,0,-1,0), vec4(1,0,0,0));
	
	//lights
	lights.push_back(Light(vec4(10, 10, 0, 1), vec4(1, 1, 1, 1), vec4(0.2f, 0.2f, 0.2f, 1), vec4(1, 1, 1, 1)));
	
	glEnable(GL_DEPTH_TEST); //since we're doing 3D graphics, enable the Z-buffer depth test

	//define color to use when color buffer is cleared
    glClearColor( 1.0, 1.0, 1.0, 1.0 ); 
}

//----------------------------------------------------------------------------

void display( void )
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );  //clear out the color of the framebuffer and the depth info from the depth buffer
		
	myTriangle->draw(camera,lights);  //draw the triangle
	
	glFlush();
}

//----------------------------------------------------------------------------

void resize(int w, int h){
	glViewport(0,0,(GLsizei) w, (GLsizei) h);  //make the viewport the entire window
	camera.changeProjection(w, h);		//update the projection matrix so it has the aspect ratio of the window
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
	delete myTriangle;  //call destructor on close
}

