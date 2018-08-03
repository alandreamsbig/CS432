//SAMPLE CODE
//3D Graphics


#include "Angel.h"  //includes gl.h, glut.h and other stuff...
#include "Camera.h"
#include "Sphere.h"



bool rotation = false;
Camera* s;
Sphere* a;

void display();
void close();
bool toggle = false;

//Foward declarations of functions


void keyboard(unsigned char, int, int);

void special(int, int, int);

void close() {
	delete a;
}
void init() {

	glEnable(GL_DEPTH_TEST); //since we're doing 3D graphics, enable the Z-buffer depth test

							 //define color to use when color buffer is cleared
	glClearColor(1.0, 1.0, 1.0, 1.0);

	s = new Camera();
	a = new Sphere();
}
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

    glutCreateWindow( "TsaiAlanHW4" );  //open a window with the title "2D Graphics"

	//initialize glew if necessary (don't need to on Macs)
#ifndef __APPLE__
	GLenum err = glewInit();
#endif

	init();
	//set up the callback functions
    glutDisplayFunc( display );  //REQUIRED.  What to do when it's time to draw
    glutKeyboardFunc( keyboard );  //What to do if a keyboard event is detected
	glutSpecialFunc(special);
	glutWMCloseFunc(close);
    glutMainLoop();  //start infinite loop, listening for events
    return 0;
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //clear out the color of the framebuffer and the depth info from the depth buffer

	a->drawSphere(s);
	a->drawSquare();

	glFlush();
}




//----------------------------------------------------------------------------

void keyboard( unsigned char key, int x, int y )
{
	switch (key) {

	case 'X':
	{

		s->pitchUp();
		break;
	}
	case 'x':
	{

		s->pitchDown();
		break;
	}
	case 'C':
	{

		s->YawClockwise();
		break;
	}
	case 'c':
	{

		s->YawCounterwise();
		break;
	}
	case 'Z':
	{

		s->RollClockwise();
		break;
	}
	case 'z':
	{

		s->RollCounterwise();
		break;
	}
	case 'P':
	{
		bool ortho = true;
		s->getProj(ortho);
		break;
	}
	case 'p':
	{
		bool proj = false;
		s->getProj(proj);
		break;
	}
	case ' ':
	{
		toggle = !toggle;
		s->toggleCam(toggle);
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
		
			s->MoveTowards();
			break;
		}
		case GLUT_KEY_DOWN:
		{
			
			s->MoveAway();
			break;

		}
		case GLUT_KEY_LEFT:
		{
			s->MoveLeft();
			break;
		}
		case GLUT_KEY_RIGHT:
		{
			s->MoveRight();
			break;
		}
	}
		
	glutPostRedisplay();
}


