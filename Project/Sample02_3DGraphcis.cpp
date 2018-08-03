//SAMPLE CODE
//3D Graphics


#include "Angel.h"  //includes gl.h, glut.h and other stuff...
#include "Camera.h";
#include "Sphere.h";
#include "Triangle.h";
#include "Cube.h";
#include "Skybox.h";
#include "Plane.h";
#include "Light.h";
#include "CubeMap.h";
#include "Roof.h";


vec4 black_opaque = vec4(0.0,0.0,0.0,1.0);
void timerCallback(int value);
int theta;

//Foward declarations of functions

void init();
void display();
void keyboard(unsigned char, int, int);
void keyboardSpecial(int key, int x, int y);
void close();
void mymouse(GLint button, GLint state, GLint x, GLint y);


std::string textures[] = { "crate1.ppm", "crate2.ppm" };
int currTexture = 0;
//----------------------------------------------------------------------------
int main( int argc, char **argv )
{
    glutInit( &argc, argv );	//initialize glut
	#ifdef __APPLE__
    glutInitDisplayMode( GLUT_3_2_CORE_PROFILE|GLUT_RGBA | GLUT_SINGLE|GLUT_DEPTH);
#else
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE |GLUT_DEPTH);
#endif
    glutInitWindowSize( 500, 500 );	//set window size to be 512x512 pixels

    glutCreateWindow( "3D Graphics" );  //open a window with the title "2D Graphics"

	//initialize glew if necessary (don't need to on Macs)
#ifndef __APPLE__
	GLenum err = glewInit();
#endif

    init();  //do some initialize for our program

	//set up the callback functions
    glutDisplayFunc( display );  //REQUIRED.  What to do when it's time to draw
    glutKeyboardFunc( keyboard );  //What to do if a keyboard event is detected
	glutMouseFunc(mymouse);
	glutSpecialFunc(keyboardSpecial);
	glutWMCloseFunc(close);
    glutMainLoop();  //start infinite loop, listening for events
    return 0;
}

Sphere *sphere;
Cube *cube;
CubeMap *cMap;
Cube *door;

Camera c;
Camera staticCamera(vec4(0, 10, 0,1), vec4(0, 1, 0,0), vec4(0, 0, -1,0));
Camera *currCam;
bool rotate = true;

Plane *xzPlane;
Light flashLight, sun;
Skybox *skybox;

Cube *house;
Light whiteLite;
Sphere *snowball;

Sphere *snowmanBottom, *snowmanBody, *snowmanHead;

std::vector<Drawable*> objs;

bool snowballExists = false;

Cube *houseBottom;

Roof *roof;

Sphere *testSphere;

void makeSnowball()
{
	vec4 currLoc = currCam->getEye();

	vec3 trans = vec3(currLoc[0], currLoc[1], currLoc[2]);

	snowball = new Sphere();
	
	

	vec4 mat = vec4(219.0/255.0, 255.0 / 255.0, 255.0 / 255.0, 0.8);

	snowball->setMaterial(mat, mat, mat, 2);
	snowball->setModelMatrix(mat4(1.0));
	snowball->applyTransformation(Translate(trans)*Scale(.2, .2, .2));
	objs.push_back(snowball);
}


void init()
{
	theta = 0.0;
	
	glEnable(GL_DEPTH_TEST);


	currCam = &c;

	sphere = new Sphere();
	xzPlane = new Plane();
	cube = new Cube();
	skybox = new Skybox();
	cMap = new CubeMap();
	house = new Cube();
	door = new Cube();
	snowball = new Sphere();

	roof = new Roof();

	

	//objs.push_back(sphere);
	objs.push_back(xzPlane);
	objs.push_back(cMap);
	
	objs.push_back(door);

	
	objs.push_back(roof);
	objs.push_back(house);


	mat4 rY = Translate(2, 1, -4)*RotateY(90.0);



	snowmanBottom = new Sphere();
	snowmanBody = new Sphere();
	snowmanHead = new Sphere();

	snowmanBottom->setModelMatrix(Scale(1.25,1,1.25)*Translate(0,1,0));
	snowmanBody->setModelMatrix(Translate(0, 2.5, 0)*Scale(0.85));
	snowmanHead->setModelMatrix(Translate(0, 3.6, 0)*Scale(0.5));


	objs.push_back(snowmanBottom);
	objs.push_back(snowmanBody);
	objs.push_back(snowmanHead);

	
	snowmanBottom->setMaterial(vec4(1.0,1.0,1.0), vec4(1.0, 1.0, 1.0), vec4(1.0, 1.0, 1.0), 5);
	snowmanBody->setMaterial(vec4(1.0, 1.0, 1.0), vec4(1.0, 1.0, 1.0), vec4(1.0, 1.0, 1.0), 5);
	snowmanHead->setMaterial(vec4(1.0, 1.0, 1.0), vec4(1.0, 1.0, 1.0), vec4(1.0, 1.0, 1.0), 5);
	

	
	staticCamera.setStatic(true);
	staticCamera.createViewMatrix();
	staticCamera.toggleProjectionType();

	c.createViewMatrix();
	c.toggleProjectionType();
	c.setEye(vec4(0,2,0,1));


	for (Drawable* obj : objs)
	{
		obj->setProjectionMatrix(c.getProjectionMatrix());
	}



	//xzPlane->updateModelMatrix(Scale(150, 150, 150));
	xzPlane->updateModelMatrix(Scale(15, 15, 15));
	xzPlane->setTexture("ice.ppm");

	srand(static_cast<unsigned int>(time(0)));

	cube->transformModelMatrix(Translate(2, 1, -4));

	testSphere = new Sphere();

	testSphere->setModelMatrix(Translate(0,1,0)*mat4(1.0));


	//objs.push_back(testSphere);




	skybox->setNormal(currCam->getN());
	skybox->setV(currCam->getV());


	float sh = 50.0;

	vec4 a(1.0*rand() / RAND_MAX, 1.0*rand() / RAND_MAX, 1.0*rand() / RAND_MAX, 1);
	vec4 s(1.0*rand() / RAND_MAX, 1.0*rand() / RAND_MAX, 1.0*rand() / RAND_MAX, 1);
	vec4 d(1.0*rand() / RAND_MAX, 1.0*rand() / RAND_MAX, 1.0*rand() / RAND_MAX, 1);

	sphere->setMaterial(a, d, s, sh);
	cube->setMaterial(s,a,d,2);


	a = vec4(0, 1, 0, 1);
	d = vec4(1.0, 0.0, 0.0, 1.0);

	vec4 full(1.0, 1.0, 1.0, 1.0);
	//240-248-255	
	vec4(240.0 / 255.0, 248.0 / 255.0, 1.0);
	xzPlane->setMaterial(vec4(240.0 / 255.0, 248.0 / 255.0, 1.0), vec4(240.0 / 255.0, 248.0 / 255.0, 1.0), vec4(240.0 / 255.0, 248.0 / 255.0, 1.0),1);
	// a d s sh

	vec4 color(1.0,0.5,0.5, 1);
	flashLight = Light(currCam->getEye(), vec4(0,0,0,1.0), color, color);

	vec4 color2(255.0 / 255.0, 128.0 / 255.0, 0, 1);
	sun = Light(vec4(0, 0, 0, 0), color2, color2, color2);
	whiteLite = Light(vec4(0,0,0,1), vec4(1, 1, 1, 1), vec4(1, 1, 1, 1), vec4(1, 1, 1, 1));
	

	house->setTexture("house.ppm");
	house->setMaterial(vec4(1.0, 1.0, 1.0), vec4(1.0, 1.0, 1.0), vec4(1.0, 1.0, 1.0), 2);

	roof->setMaterial(vec4(1.0, 1.0, 1.0), vec4(1.0, 1.0, 1.0), vec4(1.0, 1.0, 1.0), 100);

	door->setTexture("door.ppm");
	door->setMaterial(vec4(1.0, 1.0, 1.0), vec4(1.0, 1.0, 1.0), vec4(1.0, 1.0, 1.0), 0);
	door->updateModelMatrix(Scale(0.5,2,0.5)*Translate(-20, 0, -20));

	vec4 * p = house->getPoints();


	glClearColor( 1.0, 1.0, 1.0, 1.0 );
	
}


bool view = true;
//----------------------------------------------------------------------------
// switch to VAO, make sure to change to the right program, and give values to all of the uniform variables in the shader program
void display( void )
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );  //clear out the color of the framebuffer and the depth info from the depth buffer

	flashLight.setPosition(currCam->getEye());
	
	skybox->setNormal(currCam->getN());
	skybox->setV(currCam->getV());
	skybox->draw();

	//LookAt(vec4(0, 0, 0, 1), vec4(0, 0, 0, 1) - currNormal, currV);

	for (Drawable* obj : objs)
	{
		if (obj != xzPlane)
		{
			obj->setLight(flashLight, 0);
			obj->setLight(whiteLite, 1);
			obj->updateViewMatrix(currCam->getViewMatrix());
			obj->draw();
		}
		
	}


	xzPlane->setLight(flashLight, 0);
	xzPlane->setLight(whiteLite, 1);
	xzPlane->updateViewMatrix(currCam->getViewMatrix());
	xzPlane->draw();


	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR) {
		std::cout << "OpenGL error: " << err << "     " << gluErrorString(err) << "|" << std::endl;
	}

	glutSwapBuffers();
}

void mymouse(GLint button, GLint state, GLint x, GLint y)
{

	glutPostRedisplay();
}

//----------------------------------------------------------------------------
bool currStatic = false;
int numSteps = 0;
vec4 setNorm = vec4();
void keyboard( unsigned char key, int x, int y )
{
    switch( key ) {

	case 'x':
		currCam->rotateU(2);
		glutPostRedisplay();
		break;
	case 'X':
		currCam->rotateU(-2);
		glutPostRedisplay();
		break;
	case 'c':
		currCam->rotateV(-2);
		glutPostRedisplay();
		break;
	case 'C':
		currCam->rotateV(2);
		glutPostRedisplay();
		break;
	case 'z':
		currCam->rotateN(-2);
		glutPostRedisplay();
		break;
	case 'Z':
		currCam->rotateN(2);
		glutPostRedisplay();
		break;
	case ' ':
		flashLight.toggle();
		glutPostRedisplay();
		break;
	case 'l':
		if (!snowballExists)
		{
			snowballExists = true;
			numSteps = 0;
			setNorm = -0.10 * currCam->getN();
			makeSnowball();

			glutTimerFunc(10, timerCallback, 0);
		}
		
		break;
	case 't':
		if (currTexture == 0)
		{
			currTexture = 1;
		}
		else
		{
			currTexture = 0;
		}
		cube->setTexture(textures[currTexture]);
		glutPostRedisplay();
		break;
	case 'T':
		if (currTexture == 0)
		{
			currTexture = 1;
		}
		else
		{
			currTexture = 0;
		}
		cube->setTexture(textures[currTexture]);
		glutPostRedisplay();
		break;
	case 033:  // Escape key
	case 'q': case 'Q':
	    exit( EXIT_SUCCESS );
	    break;
    }
}

void keyboardSpecial(int key, int x, int y)
{
	vec4 rayOrigin;
	vec4 ray;
	switch (key) {
	case GLUT_KEY_UP:
		currCam->moveForward();
		break;
	case GLUT_KEY_DOWN:
		currCam->moveBackward();
		break;
	case GLUT_KEY_RIGHT:
		currCam->moveRight();
		break;
	case GLUT_KEY_LEFT:
		currCam->moveLeft();
		break;
	}
	glutPostRedisplay();
}

void close(){
	//glDeleteBuffers(1, &buffer);  //delete the buffers (free up space on GPU)

}




void timerCallback(int value)
{
	snowball->applyTransformation(Translate(setNorm[0], setNorm[1], setNorm[2]));
	if (numSteps < 500)
	{
		numSteps++;
		glutTimerFunc(10, timerCallback, 0);
		
	}
	else
	{
		snowballExists = false;
		auto it = std::find(objs.begin(), objs.end(), snowball);
		objs.erase(it);
	}
	
	glutPostRedisplay();

}