#include "Camera.h"
#include "mat.h"
#include "Light.h"

Light light;


Camera::Camera()
{
	bool d = true;
	toggleCam(d);
}



void Camera::toggleCam(bool check1)
{


	eye = vec4(0, 2, 0, 1);
	n = vec4(0, 0, 1, 0);
	at = eye - n;
	v = vec4(0, 1, 0, 0);

	u = normalize(cross(v, n));

	if (check1 == true)
	{
		view_matrix = LookAt(eye, at, v);
	}
	if (check1 == false)
	{
		view_matrix = LookAt(eye, at, v)*Translate(0, 2, -10)*RotateX(90);
	}


	bool a = false;
	getProj(a);

}

void Camera::getProj(bool check)
{
	if (check == true)
	{
		proj_matrix = Ortho(-1, 1, -1, 1, 1, 3);
	}
	else if (check == false)
	{
		proj_matrix = Perspective(65, 1, 1, 100);
	}

}


void Camera::pitchUp()
{

	float rad = Step2 * 2 * 3.14 / 360;
	vec4 vPrime = v;
	vec4 nPrime = n;

	u = u;
	v = normalize(cos(rad)*vPrime - sin(rad)* nPrime);
	n = normalize(sin(rad)*vPrime + cos(rad)*nPrime);
	at = eye - n;
	view_matrix = LookAt(eye, at, v);
}

void Camera::pitchDown()
{
	float rad = -Step2 * 2 * 3.14 / 360;
	vec4 vPrime = v;
	vec4 nPrime = n;

	v = normalize(cos(rad)*vPrime - sin(rad)* nPrime);
	n = normalize(sin(rad)*vPrime + cos(rad)*nPrime);
	at = eye - n;
	view_matrix = LookAt(eye, at, v);
}

void Camera::YawClockwise()
{
	float rad = Step2 * 2 * 3.14 / 360;
	vec4 uPrime = u;
	vec4 nPrime = n;

	u = normalize(cos(rad)*uPrime - sin(rad)* nPrime);
	n = normalize(sin(rad)*uPrime + cos(rad)*nPrime);
	at = eye - n;
	view_matrix = LookAt(eye, at, v);
}

void Camera::YawCounterwise()
{
	float rad = -Step2 * 2 * 3.14 / 360;
	vec4 uPrime = u;
	vec4 nPrime = n;

	u = normalize(cos(rad)*uPrime - sin(rad)* nPrime);
	n = normalize(sin(rad)*uPrime + cos(rad)*nPrime);
	at = eye - n;
	view_matrix = LookAt(eye, at, v);
}

void Camera::RollClockwise()
{
	float rad = Step2 * 2 * 3.14 / 360;
	vec4 uPrime = u;
	vec4 vPrime = v;

	u = normalize(cos(rad)*uPrime - sin(rad)* vPrime);
	v = normalize(sin(rad)*uPrime + cos(rad)*vPrime);
	at = eye - n;
	view_matrix = LookAt(eye, at, v);
}

void Camera::RollCounterwise()
{
	float rad = -Step2 * 2 * 3.14 / 360;
	vec4 uPrime = u;
	vec4 vPrime = v;

	u = normalize(cos(rad)*uPrime - sin(rad)* vPrime);
	v = normalize(sin(rad)*uPrime + cos(rad)*vPrime);
	at = eye - n;
	view_matrix = LookAt(eye, at, v);
}

void Camera::MoveTowards()
{
	eye -= n*Step;
	at = eye - n;
	view_matrix = LookAt(eye, at, v);

}

void Camera::MoveAway()
{
	eye += n*Step;
	at = eye - n;
	view_matrix = LookAt(eye, at, v);

}

void Camera::MoveLeft()
{
	
	eye += u*Step;
	at = eye - n;
	view_matrix = LookAt(eye, at, v);
	light.setPosition(eye);
}

void Camera::MoveRight()
{
	eye -= u*Step;
	at = eye - n;
	view_matrix = LookAt(eye, at, v);
	light.setPosition(eye);
}