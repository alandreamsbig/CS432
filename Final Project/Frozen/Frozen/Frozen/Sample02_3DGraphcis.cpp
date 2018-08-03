//SAMPLE CODE
//3D Graphics

#include <iostream>
#include <fstream>
#include <time.h>
#include "Angel.h"  //includes gl.h, glut.h and other stuff...
#include "Camera.h";
#include "Sphere.h";
#include "Triangle.h";
#include "Cube.h";
#include "Skybox.h";
#include "Plane.h";
#include "Light.h";
#include "Roof.h";
#include "campfire.h";
#include "SnowCloud.h";
#include "Smoke.h";
#include "treeTop.h";
#include "treeBottom.h";
#include "Tree.h";
#include "SphereOld.h";

vec4 black_opaque = vec4(0.0,0.0,0.0,1.0);
void timerCallback(int value);
void snowflaketimer(int value);
void headanimationtimer(int value);
int theta;
int numSnowClouds = 0;

//Foward declarations of functions

void init();
void display();
void resize(int w, int h);
void keyboard(unsigned char, int, int);
void keyboardSpecial(int key, int x, int y);
void close();
void mymouse(GLint button, GLint state, GLint x, GLint y);
void createCloud(int value);
void updateSmoke(int value);

std::string textures[] = { "crate1.ppm", "crate2.ppm" };
int currTexture = 0;
//----------------------------------------------------------------------------
int main( int argc, char **argv )
{
	srand(time(0));
    glutInit( &argc, argv );	//initialize glut
	#ifdef __APPLE__
    glutInitDisplayMode( GLUT_3_2_CORE_PROFILE|GLUT_RGBA | GLUT_SINGLE|GLUT_DEPTH);
#else
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE |GLUT_DEPTH);
#endif
    glutInitWindowSize( 900, 900 );	//set window size to be 512x512 pixels

    glutCreateWindow( "3D Graphics" );  //open a window with the title "2D Graphics"

	//initialize glew if necessary (don't need to on Macs)
#ifndef __APPLE__
	GLenum err = glewInit();
#endif

    init();  //do some initialize for our program

			 
	//set up the callback functions
    glutDisplayFunc( display );  //REQUIRED.  What to do when it's time to draw
	glutReshapeFunc(resize);
    glutKeyboardFunc( keyboard );  //What to do if a keyboard event is detected
	glutMouseFunc(mymouse);
	glutSpecialFunc(keyboardSpecial);
	glutWMCloseFunc(close);
	glutTimerFunc(10, timerCallback, 0);
	glutTimerFunc(10, snowflaketimer, 1);
	glutTimerFunc(100, headanimationtimer, 0);
	glutTimerFunc(25, updateSmoke, 3);
    glutMainLoop();  //start infinite loop, listening for events
    return 0;
}

//create class objects
Cube *door;

Camera c;
Camera staticCamera;
Camera *currCam;

Plane *xzPlane;
Light sun;
Skybox *skybox;


Light whiteLite;
Sphere *snowball;

Sphere *snowmanHead, *snowmanBottom, *snowmanBody;
SphereOld *sphere;

std::vector<Drawable*> objs;

Roof *roof;
Cube *house;

Drawable* snowballs[2048];
vec4 snowballNormals[2048];
int snowballSteps[2048];
int currSnowball = 0;

SnowCloud* snowCloud;
std::vector<SnowCloud*> snowClouds;

campfire* fire;
Smoke* smoke;
Tree* trees;

//create snowball and set the scaling and transformation
void makeSnowball()
{
	vec4 currLoc = currCam->getEye();

	vec3 trans = vec3(currLoc[0], currLoc[1], currLoc[2]);

	snowball = new Sphere();
	

	vec4 mat = vec4(219.0/255.0, 255.0 / 255.0, 255.0 / 255.0, 0.8);

	snowball->setMaterial(mat, mat, mat, 2);
	snowball->setModelMatrix(mat4(1.0));
	snowball->applyTransformation(Translate(trans)*Scale(.2, .2, .2));

	snowballs[currSnowball-1] = snowball;
	
}

//initialize the object such as material,colors and textures
int numSnowflakes = 2048*2;
void init()
{
	theta = 0.0;
	
	glEnable(GL_DEPTH_TEST);

	currCam = &c;

	xzPlane = new Plane();

	skybox = new Skybox();
	house = new Cube();
	door = new Cube();
	
	snowball = new Sphere();
	roof = new Roof();
	trees = new Tree();
	sphere = new SphereOld();



	createCloud(NULL);

	objs.push_back(xzPlane);
	objs.push_back(door);


	objs.push_back(roof);
	objs.push_back(house);
	objs.push_back(trees);


	mat4 rY = Translate(2, 1, -4)*RotateY(90.0);


	snowmanBottom = new Sphere();
	snowmanBody = new Sphere();
	snowmanHead = new Sphere();


	snowmanBottom->setModelMatrix(Scale(1.25, 1, 1.25)*Translate(5, 1, 0));
	snowmanBody->setModelMatrix(Translate(6, 2.5, 0)*Scale(0.85));
	snowmanHead->setModelMatrix(Translate(6, 3.6, 0)*Scale(0.5) *RotateX(90));
	snowmanHead->setTexture("faceSnowNewTexture.ppm");
	sphere->setModelMatrix(Translate(6, 3.6, 0)*Scale(0.5));


	objs.push_back(snowmanBottom);
	objs.push_back(snowmanBody);
	objs.push_back(snowmanHead);
	objs.push_back(sphere);
	
	snowmanBottom->setMaterial(vec4(1.0,1.0,1.0), vec4(1.0, 1.0, 1.0), vec4(1.0, 1.0, 1.0), 5);
	snowmanBody->setMaterial(vec4(1.0, 1.0, 1.0), vec4(1.0, 1.0, 1.0), vec4(1.0, 1.0, 1.0), 5);
	snowmanHead->setMaterial(vec4(1.0, 1.0, 1.0), vec4(1.0, 1.0, 1.0), vec4(1.0, 1.0, 1.0), 5);
	
	
	fire = new campfire();
	objs.push_back(fire);

	
	staticCamera.setStatic(true);
	staticCamera.setEye(vec4(6, 3.6, 0, 1));
	staticCamera.setN(RotateY(135) * staticCamera.getN());
	staticCamera.createViewMatrix();
	staticCamera.toggleProjectionType();

	

	c.setEye(vec4(0,2,0,1));
	c.createViewMatrix();
	c.toggleProjectionType();

	for (Drawable* obj : objs)
	{
		obj->setProjectionMatrix(c.getProjectionMatrix());
	}

	snowCloud = new SnowCloud();
	snowCloud->setProjectionMatrix(c.getProjectionMatrix());
	snowClouds.push_back(snowCloud);
	numSnowClouds++;

	smoke = new Smoke();
	smoke->setProjectionMatrix(c.getProjectionMatrix());


	xzPlane->updateModelMatrix(Scale(5000));
	xzPlane->setTexture("ice.ppm");


	skybox->setNormal(currCam->getN());
	skybox->setV(currCam->getV());


	float sh = 50.0;

	vec4 a(1.0*rand() / RAND_MAX, 1.0*rand() / RAND_MAX, 1.0*rand() / RAND_MAX, 1);
	vec4 s(1.0*rand() / RAND_MAX, 1.0*rand() / RAND_MAX, 1.0*rand() / RAND_MAX, 1);
	vec4 d(1.0*rand() / RAND_MAX, 1.0*rand() / RAND_MAX, 1.0*rand() / RAND_MAX, 1);

	a = vec4(0, 1, 0, 1);
	d = vec4(1.0, 0.0, 0.0, 1.0);

	vec4 full(1.0, 1.0, 1.0, 1.0);
	//240-248-255	
	vec4(240.0 / 255.0, 248.0 / 255.0, 1.0);
	xzPlane->setMaterial(vec4(240.0 / 255.0, 248.0 / 255.0, 1.0), vec4(240.0 / 255.0, 248.0 / 255.0, 1.0), vec4(240.0 / 255.0, 248.0 / 255.0, 1.0),1);
	// a d s sh
	
	vec4 color2(255.0 / 255.0, 128.0 / 255.0, 0.95, 1);
	sun = Light(vec4(0, 0, 0, 0), color2, vec4(0,0,0,1), color2);

	vec4 color3 = vec4(.4, .4, .4, .4);
	whiteLite = Light(vec4(0,50,0,1), color3, color3, color3);
	//rgb(187.0/255.0, 233.0/255.0, 241.0/255.0)

	house->setTexture("house.ppm");
	house->setMaterial(vec4(1.0, 1.0, 1.0), vec4(1.0, 1.0, 1.0), vec4(1.0, 1.0, 1.0), 2);

	roof->setMaterial(vec4(1.0, 1.0, 1.0), vec4(1.0, 1.0, 1.0), vec4(1.0, 1.0, 1.0), 100);

	door->setTexture("door.ppm");

	//a d s
	door->setMaterial(vec4(1.0,1.0,1.0,0), vec4(0,0,0, 0), vec4(0,0,0,0), 0);

	fire->setMaterial(vec4(1.0, 1.0, 1.0, 1.0), vec4(0, 0, 0, 1), vec4(0, 0, 0, 1), 0);

	double scale = 3.0;
	door->updateModelMatrix(Translate(0, scale * .5001, -5.65)*Scale(scale/2.0, scale, scale/2.0)*RotateZ(90)*mat4(1.0));

	c.updateWindow(900,900);
	staticCamera.updateWindow(900,900);
	glClearColor( 1.0, 1.0, 1.0, 1.0 );
	
}


bool view = true;
//----------------------------------------------------------------------------
// switch to VAO, make sure to change to the right program, and give values to all of the uniform variables in the shader program
void display( void )
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );  //clear out the color of the framebuffer and the depth info from the depth buffer


	skybox->setNormal(currCam->getN());
	skybox->setV(currCam->getV());
	skybox->draw();
	vec4 currEye = currCam->getEye();
	
	Light flashlight(vec4(0, 0, 0, 0), vec4(0, 0, 0, 0), vec4(0, 0, 0, 0), vec4(0, 0, 0, 0));
	flashlight.toggle();
	for (Drawable* obj : objs)
	{
		if (!(currCam == &staticCamera && (obj == snowmanHead || obj == sphere)))
		{
			if (obj != xzPlane && obj != snowCloud)
			{
				obj->setLight(flashlight, 0);
				obj->setLight(whiteLite, 1);
				obj->updateViewMatrix(currCam->getViewMatrix());
				obj->draw();
			}
		}
	}



	for (int i = 0; i < currSnowball; i++)
	{
		if (((Sphere*)snowballs[i])->getActivated())
		{
			snowballs[i]->updateViewMatrix(currCam->getViewMatrix());
			snowballs[i]->draw();
		}
	}

	xzPlane->setLight(flashlight, 0);
	xzPlane->setLight(whiteLite, 1);
	xzPlane->updateViewMatrix(currCam->getViewMatrix());
	xzPlane->draw();


	smoke->updateViewMatrix(currCam->getViewMatrix());
	smoke->draw();

	for (int i = 0; i < snowClouds.size(); i++)
	{
		snowClouds.at(i)->updateViewMatrix(currCam->getViewMatrix());
		snowClouds.at(i)->draw();
	}

	GLenum err;
	err = glGetError();
	while ((err = glGetError()) != GL_NO_ERROR) {
		std::cout << "OpenGL error: " << err << "     " << gluErrorString(err) << "|" << std::endl;
	}


	glutSwapBuffers();
}

//----------------------------------------------------------------------------
//get keyborad input
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
		if (currCam == &staticCamera)
		{
			currCam = &c;
		}
		else
		{
			currCam = &staticCamera;
		}
		glutPostRedisplay();
		break;
	case 'l':
		currSnowball++;
		snowballSteps[currSnowball-1] = 0;
		if (currCam == &c)
		{
			snowballNormals[currSnowball - 1] = -.25 * currCam->getN();
		}
		else
		{
			snowballNormals[currSnowball - 1] = -1.0 * currCam->getN();
		}
		makeSnowball();
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
	for (Drawable* obj : objs)
	{
		obj->cleanup();
	}
}



//activate snowball
void timerCallback(int value)
{
	vec4 currT;
	for (int i = 0; i < currSnowball; i++)
	{	
		currT = 0.95*snowballNormals[i] + (snowballSteps[i] / 500.0)*vec4(0, -0.1, 0, 1);
		((Sphere*)snowballs[i])->applyTransformation(Translate(currT[0], currT[1], currT[2]));
		if (((Sphere*)snowballs[i])->fixHeight())
		{
			snowballNormals[i] *= 0.99;
		}
		if (((Sphere*)snowballs[i])->getActivated() && snowballSteps[i] < 500)
		{
			snowballSteps[i]++;
		}
		else
		{
			((Sphere*)snowballs[i])->deactivate();
		}
	}



	glutTimerFunc(10, timerCallback, 0);

	glutPostRedisplay();

}
/*
	axis:
		0 is x
		1 is y
		2 is z
*/
float getForces(int axis)
{
	if (axis == 0)		// x movement
	{
		return 0.0;
	}
	else if (axis == 1) // y movement
	{
		return -1.0;
	}
	else				// z movement
	{
		return 0.0;
	}
}

bool collision(int snowflake)
{
	

	return true;
}

//activate snowflakes 
void snowflaketimer(int value)
{
	for (int i = 0; i < snowClouds.size(); i++)
	{
		SnowCloud* currCloud = snowClouds.at(i);
		for (int j = 0; j < currCloud->numSnowflakes; j++)
		{
			if ( (currCloud->model_matrix * (vec4(0,-.1,0,1) + currCloud->snowflakeOffsets[j])).y > 0)
			{
				float f = 5.0*rand() / RAND_MAX;
				if (f <= 1.0) { currCloud->snowflakeOffsets[j].x -= 0.05; }
				else { currCloud->snowflakeOffsets[j].x += 0.05; }

				f = 5.0*rand() / RAND_MAX;
				if (f <= 1.0) { currCloud->snowflakeOffsets[j].z -= 0.05; }
				else { currCloud->snowflakeOffsets[j].z += 0.05; }
				
				currCloud->snowflakeOffsets[j].y -= 0.05;
			}
		}
	}
	
	

	glutTimerFunc(10, snowflaketimer, 1);

	
}

//activate snowman head animation when mouse click
double headTheta = 0;
double mult = 1.0;
bool headspin = true;
void headanimationtimer(int value)
{
	if (headspin)
	{
		if (headTheta > 90)
		{
			mult = -1.0 * mult;
			headTheta = 0;
		}

		snowmanHead->applyTransformation(Translate(6, 3.6, 0)*RotateY(mult * 2)*Translate(-6, -3.6, 0));
		staticCamera.setStatic(false);
		staticCamera.rotateV(mult * 2);
		staticCamera.setStatic(true);
		headTheta += 2;

	}
	
	

	glutTimerFunc(50, headanimationtimer, 0);
	glutPostRedisplay();
}
void mymouse(GLint button, GLint state, GLint x, GLint y)
{
	double xT, yT;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		xT = (2.0 * ((double)x / currCam->width)) - 1.0;
		yT = 1.0 - (2.0 * ((double)y / currCam->height));

		vec4 newPoint = vec4(1.0);
		newPoint[0] = xT;
		newPoint[1] = yT;
		newPoint[2] = -1.0;
		newPoint[3] = 1.0;

		vec4 worldPoint = currCam->getViewPerspecPoint(newPoint[0], newPoint[1]);
		vec4 pointRay = worldPoint - currCam->getEye();

		if (currCam == &c && sphere->processClick(currCam->getEye(), pointRay))
		{
			headspin = !headspin;
		}
	}

	glutPostRedisplay();
}




void resize(int w, int h) {

	c.updateWindow(w, h);
	staticCamera.updateWindow(w, h);

	if (w > h)
	{
		glViewport(0, 0, h, h);
	}
	else
	{
		glViewport(0, 0, w, w);
	}
	

}


void createCloud(int value)
{
	if (numSnowClouds < 5)
	{
		SnowCloud* sc = new SnowCloud();
		sc->setProjectionMatrix(c.getProjectionMatrix());
		snowClouds.push_back(sc);
		sc->applyTransformation(Translate(0, 25, 0));
		numSnowClouds++;
	}
	
	for(int i = 0; i < snowClouds.size(); i++)
	{
		if (snowClouds.at(i)->shouldDelete())
		{
			std::cout << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << "Deleted: " << i 
				<< std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl;
			snowClouds.erase(snowClouds.begin() + i);
			numSnowClouds--;
		}
	}

	glutTimerFunc(20000, createCloud, 2);
	glutPostRedisplay();
}


void updateSmoke(int value)
{

	particle* particles = smoke->getParticles();

	for (int i = 0; i < smoke->numSmokeParticles; i++)
	{
		if (particles[i].steps < particles[i].stepMax)
		{
			particles[i].position += particles[i].velocity;
			particles[i].steps += 1.0;
		}
		else
		{
			particles[i].position = vec4(particles[i].position.x, 0.001, particles[i].position.z, 1.0);

			particles[i].stepMax = 15.0*rand() / RAND_MAX;
			particles[i].steps = 0.0;
		}
	}


	glutTimerFunc(100, updateSmoke, 3);
	glutPostRedisplay();
}