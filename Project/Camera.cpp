#include "Camera.h"
#include <cmath>

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


vec4 Camera::getV()
{
	return v;
}

Camera::Camera(vec4 eyeI, vec4 nI, vec4 upI)
{
	eye = eyeI;
	n = nI;
	up = upI;

	u = normalize(cross(up, n));
	v = normalize(cross(n, u));

	createViewMatrix();
}

void Camera::setStatic(bool in)
{
	isStatic = in;
}



// LookAt(const vec4& eye, const vec4& at, vec4& up)
void Camera::createViewMatrix()
{
	u[3] = 0.0;
	v[3] = 0.0;
	n[3] = 0.0;

	view_matrix = LookAt(eye, eye-n, normalize(v));
}


Camera::~Camera()
{
}

void Camera::toggleProjectionType()
{
	isPerspective = !isPerspective;
	getProjectionMatrix();
}

vec4 Camera::getViewPerspecPoint(double x, double y)
{
	vec4 newPoint = vec4(0.0);
	newPoint[0] = rP * x;
	newPoint[1] = t * y;
	newPoint[2] = -nearP;
	newPoint[3] = 1.0;
	
	mat4 viewInverse = invert(view_matrix);

	viewInverse = { vec4(u[0], v[0], n[0], eye[0]), vec4(u[1], v[1], n[1], eye[1]), vec4(u[2], v[2], n[2], eye[2]), vec4(0,0,0,1) };

	vec4 pcam = newPoint;

	vec4 viewTransformedPoint = viewInverse*pcam ;

	return viewTransformedPoint;
}


vec4 Camera::getClickedPointRay(double x, double y)
{
	return getViewPerspecPoint(x,y) - eye ;
}


mat4 Camera::getProjectionMatrix()
{
	if (isPerspective)
	{
		mat4 currMatrix = Perspective(65, (double) width / height, 1.0, 100.0);

		nearP = 1.0;
		farP = 100.0;
		t = nearP * tan( ( (65.0 / 2.0) * (M_PI / 180.0)));
		rP = t * (500.0 / 500.0);

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

mat4 Camera::getProjectionMatrixInverse()
{
	return inverseProjection_matrix;
}

mat4 Camera::getViewMatrix()
{
	return view_matrix;
}

void Camera::moveRight()
{
	if (!isStatic)
	{
		eye += .25 * u;
		createViewMatrix();
	}
}

void Camera::moveLeft()
{
	if (!isStatic)
	{
		eye += -.25 * u;
		createViewMatrix();
	}
}

void Camera::moveForward()
{
	if (!isStatic)
	{
		eye += -0.25*n;
		createViewMatrix();
	}
}

void Camera::moveBackward()
{
	if (!isStatic)
	{
		eye += 0.25*n;
		createViewMatrix();
	}
}

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
