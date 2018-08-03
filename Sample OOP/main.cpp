//SAMPLE CODE

#include "Angel.h"  //includes gl.h, glut.h and other stuff...
#include "Shape.h"
#include "Square.h"


//Foward declarations of functions
void init(float mouseX, float mouseY);
void initSquare(float rmouseX, float rmouseY);
void display();
void resize(int width, int height);
void keyboard(unsigned char, int, int);
void mouse(GLint button, GLint state, GLint x, GLint y);
void timerCallback(int value);
void close();
bool rotation = false;

//objects
vector<Drawable*> objs;
vector<Drawable*> squares;

//----------------------------------------------------------------------------
int main(int argc, char **argv)
{
	glutInit(&argc, argv);	//initialize glut
#ifdef __APPLE__
	glutInitDisplayMode(GLUT_3_2_CORE_PROFILE | GLUT_RGBA | GLUT_SINGLE | GLUT_DEPTH);
#else
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE | GLUT_DEPTH);
#endif

	glutInitWindowSize(500, 500);	//set window size to be 512x512 pixels

	glutCreateWindow("TsaiAlanHW2");  //open a window with the title "2D Graphics"

							  //initialize glew if necessary (don't need to on Macs)
#ifndef __APPLE__
	GLenum err = glewInit();
#endif

	glClearColor(1.0, 1.0, 1.0, 1.0);
	 //do some initialize for our program

	//glutTimerFunc(50, timerCallback, 0);

	//set up the callback functions
	glutDisplayFunc(display);  //REQUIRED.  What to do when it's time to draw
	glutKeyboardFunc(keyboard);  //What to do if a keyboard event is detected
	glutMouseFunc(mouse);
	glutWMCloseFunc(close);
	glutReshapeFunc(resize);  //use for recomputing projection matrix on reshape
	glutMainLoop();  //start infinite loop, listening for events
	return 0;
}



void timerCallback(int value)
{

	//bool rot = false;
	
		for (unsigned int i = 0; i < objs.size(); i++)

			objs[i]->rotation();

		for (unsigned int j = 0; j < squares.size(); j++)
			squares[j]->rotation();

		if (rotation)
		{
			glutTimerFunc(50, timerCallback, value);
		}

	glutPostRedisplay();


}

//Initialization
void init(float mouseX, float mouseY)
{

	//define color to use when color buffer is cleared
	glClearColor(1.0, 1.0, 1.0, 1.0);
}



void initSquare(float rmouseX, float rmouseY)
{
	
	glClearColor(1.0, 1.0, 1.0, 1.0);
}


//----------------------------------------------------------------------------

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);  //clear out the color of the framebuffer and the depth info from the depth buffer

	
	for (unsigned int i = 0; i < objs.size(); i++)
		objs[i]->draw();
	
	for (unsigned int j = 0; j < squares.size(); j++)
		squares[j]->drawSquare();
		
	glFlush();
}


//----------------------------------------------------------------------------

void resize(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);  //make the viewport the entire window
}
void keyboard(unsigned char key, int x, int y)
{
	
	switch (key) {
	case ' ':
	{
		rotation = !rotation;
		glutTimerFunc(50, timerCallback, 0);
		break;
	}
	case 033:
	{// Escape key
	case 'q': case 'Q':
		exit(EXIT_SUCCESS);
		break;
	}
	
	}
}

void mouse(GLint button, GLint state, GLint x, GLint y)
{
	
	if( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
	float normalizedX, normalizedY;
	normalizedX = 2.0f * x / 500 - 1;
	normalizedY = 2.0f * (500 - y) / 500 - 1;
	Shape* s = new Shape(normalizedX, normalizedY);
	objs.push_back(s);

	}
	
	
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		float rnormalizedX, rnormalizedY;
		rnormalizedX = 2.0f * x / 500 - 1;
		rnormalizedY = 2.0f * (500 - y) / 500 - 1;
		Square* m = new Square(rnormalizedX, rnormalizedY);
		squares.push_back(m);
	
	}
	//glutPostRedisplay();
}


void close() {
	
	for (unsigned int i = 0; i < objs.size(); i++)
		delete objs[i];
	
	for (unsigned int j = 0; j < squares.size(); j++)
		delete squares[j];
		
}

