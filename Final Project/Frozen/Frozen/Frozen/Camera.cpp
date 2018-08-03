#include "Camera.h"
#include <cmath>


//construct camera position 
Camera::Camera()
{
	
	eye = vec4(0,1,0,1);

	up = vec4(0, 1, 0, 0);
	n = vec4(0, 0, 1, 0);

	u = normalize(cross(up, n));
	v = normalize(cross(n, u));
	
	at = eye - n;

	createViewMatrix();
}

void Camera::printCamera()
{
	std::cout << "eye: " << eye << " up: " << up << " v: " << v << " n: " << n << std::endl;
}

//get camera V
vec4 Camera::getV()
{
	return v;
}

//create camera
Camera::Camera(vec4 eyeI, vec4 nI, vec4 upI)
{
	eye = eyeI;
	n = nI;
	up = upI;

	u = normalize(cross(up, n));
	v = normalize(cross(n, u));

	createViewMatrix();
}

//check for static camera
void Camera::setStatic(bool in)
{
	isStatic = in;
}



// LookAt(const vec4& eye, const vec4& at, vec4& up)

//create camera view matrix
void Camera::createViewMatrix()
{
	u[3] = 0.0;
	v[3] = 0.0;
	n[3] = 0.0;

	view_matrix = LookAt(eye, eye-n, normalize(v));
}

//camera destructor
Camera::~Camera()
{
}

//toggle perpective or projection camera
void Camera::toggleProjectionType()
{
	isPerspective = !isPerspective;
	getProjectionMatrix();
}

//get camera perspective point
vec4 Camera::getViewPerspecPoint(double x, double y)
{
	vec4 newPoint = vec4(0.0);
	newPoint[0] = rP * x;
	newPoint[1] = t * y;
	newPoint[2] = -nearP;
	newPoint[3] = 1.0;
	
	mat4 viewInverse = invert(view_matrix);

	viewInverse = { vec4(u[0], v[0], n[0], eye[0]), 
					vec4(u[1], v[1], n[1], eye[1]), 
					vec4(u[2], v[2], n[2], eye[2]), 
					vec4(0,		0,		0,		1) };

	vec4 pcam = newPoint;
	createViewMatrix();

	vec4 viewTransformedPoint = viewInverse*pcam ;

	return viewTransformedPoint;
}

//get the mouse click ray
vec4 Camera::getClickedPointRay(double x, double y)
{
	return getViewPerspecPoint(x,y) - eye ;
}

void Camera::setBounds(vec2 x, vec2 y, vec2 z)
{
	xBoundLower = x.x;
	xBoundUpper = x.y;

	yBoundLower = y.x;
	yBoundUpper = y.y;

	zBoundLower = z.x;
	zBoundUpper = z.y;
}


bool Camera::checkInside(vec4 eyeLocation) {

	vec4 up, down, left, right, forward, back;
	double scale = 0.8;

	up = eyeLocation + vec4(0, scale, 0, 1.0);
	down = eyeLocation + vec4(0, -scale,0, 1.0);

	left = eyeLocation + vec4(-scale, 0, 0, 1.0);
	right = eyeLocation + vec4(scale, 0,0,1.0);

	forward = eyeLocation + vec4(0, 0, -scale, 1.0);
	back = eyeLocation + vec4(0, 0, scale, 1.0);

	return isInside(eyeLocation) && isInside(up) && isInside(down) && isInside(left) && isInside(right) && isInside(forward) && isInside(back);
};

bool Camera::isInside(vec4 eyeLocation)
{
	double x = eyeLocation.x;
	double y = eyeLocation.y;
	double z = eyeLocation.z;

	if (x > xBoundLower && x < xBoundUpper)
	{
		if (y > yBoundLower && y < yBoundUpper)
		{
			if (z > zBoundLower && z < zBoundUpper)
			{
				return true;
			}
		}
	}

	return false;	
}


//get camera projection matrix
mat4 Camera::getProjectionMatrix()
{
	if (isPerspective)
	{
		mat4 currMatrix = Perspective(65, (double) width / height, nearP, farP);

		t = nearP * tan( ( (65.0 / 2.0) * (M_PI / 180.0)));
		rP = t * ((float)width / (float)height);

		mat4 min = mat4(0.0);
		min[0][0] = rP/nearP;
		min[1][1] =  t/ nearP;
		min[2][3] = -1;
		min[3][2] = (nearP - farP) / (2 * farP*nearP);
		min[3][3] = (nearP + farP) / (2 * farP*nearP);
		inverseProjection_matrix = min;

		projection_matrix = currMatrix;
		
		return currMatrix;
	}
	return Ortho(-1, 1, -1, 1, 1, 3);
}

//get inverse projection matrix
mat4 Camera::getProjectionMatrixInverse()
{
	return inverseProjection_matrix;
}

//get camera view matrix
mat4 Camera::getViewMatrix()
{
	return view_matrix;
}

//move camera to the right
void Camera::moveRight()
{
	if (!isStatic && checkInside(eye + 1.25 * u))
	{
		eye += .25 * u;
		createViewMatrix();
	}
}

//move camera to the left
void Camera::moveLeft()
{
	if (!isStatic && checkInside(eye + -1.25 * u))
	{
		eye += -.25 * u;
		createViewMatrix();
	}
}

//move camera forward
void Camera::moveForward()
{
	if (!isStatic && checkInside(eye + -1.25*n))
	{
		eye += -0.25*n;
		createViewMatrix();
	}
}

//move camera backward
void Camera::moveBackward()
{
	if (!isStatic && checkInside(eye + 1.25*n))
	{
		eye += 0.25*n;
		createViewMatrix();
	}
}

//set the eye of the camera
void Camera::setEye(vec4 eyeInput)
{
	eye = eyeInput;
	createViewMatrix();
}

vec4 Camera::getEye()
{
	return eye;
}

vec4 Camera::getN()
{
	return n;
}

vec4 Camera::getAt()
{
	return at;
}

//Rotate camera along the U axis
void Camera::rotateU(double theta)
{
	if (!isStatic)
	{
		double thetaR = theta * 2 * M_PI / 360.0;
		v = cos(thetaR)*v - sin(thetaR)*n;
		n = sin(thetaR)*v + cos(thetaR)*n;
		n[3] = 0;
		createViewMatrix();
	}
}

//Rotate Camera along the V axis
void Camera::rotateV(double theta)
{
	if (!isStatic)
	{
		double thetaR = theta * 2 * M_PI / 360.0;
		u = cos(thetaR)*u - sin(thetaR)*n;
		n = sin(thetaR)*u + cos(thetaR)*n;
		n[3] = 0;
		createViewMatrix();
	}
}

//Rotate Camera along the N axis
void Camera::rotateN(double theta)
{
	if (!isStatic)
	{
		double thetaR = theta * 2 * M_PI / 360.0;
		u = cos(thetaR)*u - sin(thetaR)*v;
		v = sin(thetaR)*u + cos(thetaR)*v;
		createViewMatrix();
	}
}

//camera invert matrix
mat4 Camera::invert(mat4 m1) {

	mat4 m = mat4(1.0);

	m[0][0] = m1[1][2] * m1[2][3] * m1[3][1] - m1[1][3] * m1[2][2] * m1[3][1] + m1[1][3] * m1[2][1] * m1[3][2] - m1[1][1] * m1[2][3] * m1[3][2] - m1[1][2] * m1[2][1] * m1[3][3] + m1[1][1] * m1[2][2] * m1[3][3];
	m[0][1] = m1[0][3] * m1[2][2] * m1[3][1] - m1[0][2] * m1[2][3] * m1[3][1] - m1[0][3] * m1[2][1] * m1[3][2] + m1[0][1] * m1[2][3] * m1[3][2] + m1[0][2] * m1[2][1] * m1[3][3] - m1[0][1] * m1[2][2] * m1[3][3];
	m[0][2] = m1[0][2] * m1[1][3] * m1[3][1] - m1[0][3] * m1[1][2] * m1[3][1] + m1[0][3] * m1[1][1] * m1[3][2] - m1[0][1] * m1[1][3] * m1[3][2] - m1[0][2] * m1[1][1] * m1[3][3] + m1[0][1] * m1[1][2] * m1[3][3];
	m[0][3] = m1[0][3] * m1[1][2] * m1[2][1] - m1[0][2] * m1[1][3] * m1[2][1] - m1[0][3] * m1[1][1] * m1[2][2] + m1[0][1] * m1[1][3] * m1[2][2] + m1[0][2] * m1[1][1] * m1[2][3] - m1[0][1] * m1[1][2] * m1[2][3];
	m[1][0] = m1[1][3] * m1[2][2] * m1[3][0] - m1[1][2] * m1[2][3] * m1[3][0] - m1[1][3] * m1[2][0] * m1[3][2] + m1[1][0] * m1[2][3] * m1[3][2] + m1[1][2] * m1[2][0] * m1[3][3] - m1[1][0] * m1[2][2] * m1[3][3];
	m[1][1] = m1[0][2] * m1[2][3] * m1[3][0] - m1[0][3] * m1[2][2] * m1[3][0] + m1[0][3] * m1[2][0] * m1[3][2] - m1[0][0] * m1[2][3] * m1[3][2] - m1[0][2] * m1[2][0] * m1[3][3] + m1[0][0] * m1[2][2] * m1[3][3];
	m[1][2] = m1[0][3] * m1[1][2] * m1[3][0] - m1[0][2] * m1[1][3] * m1[3][0] - m1[0][3] * m1[1][0] * m1[3][2] + m1[0][0] * m1[1][3] * m1[3][2] + m1[0][2] * m1[1][0] * m1[3][3] - m1[0][0] * m1[1][2] * m1[3][3];
	m[1][3] = m1[0][2] * m1[1][3] * m1[2][0] - m1[0][3] * m1[1][2] * m1[2][0] + m1[0][3] * m1[1][0] * m1[2][2] - m1[0][0] * m1[1][3] * m1[2][2] - m1[0][2] * m1[1][0] * m1[2][3] + m1[0][0] * m1[1][2] * m1[2][3];
	m[2][0] = m1[1][1] * m1[2][3] * m1[3][0] - m1[1][3] * m1[2][1] * m1[3][0] + m1[1][3] * m1[2][0] * m1[3][1] - m1[1][0] * m1[2][3] * m1[3][1] - m1[1][1] * m1[2][0] * m1[3][3] + m1[1][0] * m1[2][1] * m1[3][3];
	m[2][1] = m1[0][3] * m1[2][1] * m1[3][0] - m1[0][1] * m1[2][3] * m1[3][0] - m1[0][3] * m1[2][0] * m1[3][1] + m1[0][0] * m1[2][3] * m1[3][1] + m1[0][1] * m1[2][0] * m1[3][3] - m1[0][0] * m1[2][1] * m1[3][3];
	m[2][2] = m1[0][1] * m1[1][3] * m1[3][0] - m1[0][3] * m1[1][1] * m1[3][0] + m1[0][3] * m1[1][0] * m1[3][1] - m1[0][0] * m1[1][3] * m1[3][1] - m1[0][1] * m1[1][0] * m1[3][3] + m1[0][0] * m1[1][1] * m1[3][3];
	m[2][3] = m1[0][3] * m1[1][1] * m1[2][0] - m1[0][1] * m1[1][3] * m1[2][0] - m1[0][3] * m1[1][0] * m1[2][1] + m1[0][0] * m1[1][3] * m1[2][1] + m1[0][1] * m1[1][0] * m1[2][3] - m1[0][0] * m1[1][1] * m1[2][3];
	m[3][0] = m1[1][2] * m1[2][1] * m1[3][0] - m1[1][1] * m1[2][2] * m1[3][0] - m1[1][2] * m1[2][0] * m1[3][1] + m1[1][0] * m1[2][2] * m1[3][1] + m1[1][1] * m1[2][0] * m1[3][2] - m1[1][0] * m1[2][1] * m1[3][2];
	m[3][1] = m1[0][1] * m1[2][2] * m1[3][0] - m1[0][2] * m1[2][1] * m1[3][0] + m1[0][2] * m1[2][0] * m1[3][1] - m1[0][0] * m1[2][2] * m1[3][1] - m1[0][1] * m1[2][0] * m1[3][2] + m1[0][0] * m1[2][1] * m1[3][2];
	m[3][2] = m1[0][2] * m1[1][1] * m1[3][0] - m1[0][1] * m1[1][2] * m1[3][0] - m1[0][2] * m1[1][0] * m1[3][1] + m1[0][0] * m1[1][2] * m1[3][1] + m1[0][1] * m1[1][0] * m1[3][2] - m1[0][0] * m1[1][1] * m1[3][2];
	m[3][3] = m1[0][1] * m1[1][2] * m1[2][0] - m1[0][2] * m1[1][1] * m1[2][0] + m1[0][2] * m1[1][0] * m1[2][1] - m1[0][0] * m1[1][2] * m1[2][1] - m1[0][1] * m1[1][0] * m1[2][2] + m1[0][0] * m1[1][1] * m1[2][2];

	m = (1.0 / determinant(m1))*m;

	return m;
}



double Camera::determinant(mat4 m) {
	double value;
	value =
		m[0][3] * m[1][2] * m[2][1] * m[3][0] - m[0][2] * m[1][3] * m[2][1] * m[3][0] - m[0][3] * m[1][1] * m[2][2] * m[3][0] + m[0][1] * m[1][3] * m[2][2] * m[3][0] +
		m[0][2] * m[1][1] * m[2][3] * m[3][0] - m[0][1] * m[1][2] * m[2][3] * m[3][0] - m[0][3] * m[1][2] * m[2][0] * m[3][1] + m[0][2] * m[1][3] * m[2][0] * m[3][1] +
		m[0][3] * m[1][0] * m[2][2] * m[3][1] - m[0][0] * m[1][3] * m[2][2] * m[3][1] - m[0][2] * m[1][0] * m[2][3] * m[3][1] + m[0][0] * m[1][2] * m[2][3] * m[3][1] +
		m[0][3] * m[1][1] * m[2][0] * m[3][2] - m[0][1] * m[1][3] * m[2][0] * m[3][2] - m[0][3] * m[1][0] * m[2][1] * m[3][2] + m[0][0] * m[1][3] * m[2][1] * m[3][2] +
		m[0][1] * m[1][0] * m[2][3] * m[3][2] - m[0][0] * m[1][1] * m[2][3] * m[3][2] - m[0][2] * m[1][1] * m[2][0] * m[3][3] + m[0][1] * m[1][2] * m[2][0] * m[3][3] +
		m[0][2] * m[1][0] * m[2][1] * m[3][3] - m[0][0] * m[1][2] * m[2][1] * m[3][3] - m[0][1] * m[1][0] * m[2][2] * m[3][3] + m[0][0] * m[1][1] * m[2][2] * m[3][3];
	return value;
}

void Camera::setN(vec4 newN)
{
	n = newN;
}
