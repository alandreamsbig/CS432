
#include<stdlib.h>
#include<stdio.h>
#include<GL/glut.h>
#include<math.h>
GLfloat v[4][3] = { { 0.0,0.0,1.0 },{ 0.0,0.94,-0.33 },
{ -0.81,-0.47,-0.33 },{ 0.81,-0.47,-0.33 } };
GLfloat colors[4][3] = { { 1.0,0.0,0.0 },{ 0.0,1.0,0.0 },{ 0.0,0.0,1.0 },{ 0.0,0.0,0.0 } };
int n, count;
GLfloat angle, angle2;
int moving, startx, starty;
void triangle(GLfloat *va, GLfloat *vb, GLfloat *vc)
{
	glColor3fv(colors[(count++) % 4]);
	glVertex3fv(va);
	glVertex3fv(vb);
	glVertex3fv(vc);
}

void normalize(GLfloat *p)
{
	double d = 0.0;
	int i;
	for (i = 0;i<3;i++)
		d += p[i] * p[i];
	d = sqrt(d);
	if (d>0.0) for (i = 0;i<3;i++) p[i] /= d;
}
void tetra(GLfloat *a, GLfloat *b, GLfloat *c, GLfloat *d)
{
	glColor3fv(colors[0]);
	triangle(a, b, c);
	glColor3fv(colors[1]);
	triangle(a, c, d);
	glColor3fv(colors[2]);
	triangle(a, d, b);
	glColor3fv(colors[3]);
	triangle(b, d, c);
}
void divide_tetra(GLfloat *a, GLfloat *b, GLfloat *c, int m)
{
	GLfloat mid[3][3];
	int j;
	if (m>0)
	{	/*compute six midpoints*/
		for (j = 0;j<3;j++) mid[0][j] = (a[j] + b[j]) / 2;
		normalize(mid[0]);
		for (j = 0;j<3;j++) mid[1][j] = (a[j] + c[j]) / 2;
		normalize(mid[1]);
		for (j = 0;j<3;j++) mid[2][j] = (c[j] + b[j]) / 2;
		normalize(mid[2]);


		divide_tetra(a, mid[1], mid[0], m - 1);
		divide_tetra(c, mid[2], mid[1], m - 1);
		divide_tetra(b, mid[0], mid[2], m - 1);
		divide_tetra(mid[0], mid[1], mid[2], m - 1);
	}
	else
		triangle(a, b, c);      //draw triangle at end of recursion//
}
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glRotatef(angle, 0, 1, 0);
	glRotatef(angle2, 0, 0, 1);
	glBegin(GL_TRIANGLES);
	divide_tetra(v[0], v[1], v[2], n);
	divide_tetra(v[3], v[2], v[1], n);
	divide_tetra(v[0], v[3], v[1], n);
	divide_tetra(v[0], v[2], v[3], n);
	glEnd();
	glFlush();
	glutSwapBuffers();
}
void myReshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0, 2.0, -2.0, 2.0, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}
void mouse(int btn, int state, int x, int y)
{
	if (btn == GLUT_LEFT_BUTTON&&state == GLUT_DOWN)
	{
		moving = 1;
		startx = x;
		starty = y;
	}
	if (btn == GLUT_LEFT_BUTTON&&state == GLUT_UP)
	{
		moving = 0;
	}
}
void motion(int x, int y)
{
	if (moving)
	{
		angle = angle + (x - startx);
		angle2 = angle2 + (y - starty);
		startx = x;
		starty = y;
		glutPostRedisplay();
	}
}
int main(int argc, char **argv)
{
	printf("enter the no of division ");
	scanf_s("%d", &n);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("3d gasket");
	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glEnable(GL_DEPTH_TEST);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glutMainLoop();
	return 0;
}
