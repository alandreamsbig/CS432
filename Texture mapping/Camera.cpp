#include "Camera.h"

Camera::Camera() {
	eye = vec4(0, 2, 0, 0);
	n = vec4(0, 0, 1, 0);
	v = vec4(0, 1, 0, 0);
	u = vec4(1, 0, 0, 0);
	viewMatrix = LookAt(eye, eye - n, v);
}

void Camera::changeProjection(int width, int height) {
	GLfloat fov = 65;
	GLfloat nearp = 1.0;
	GLfloat farp = 100.0;
	mat4 proj = Perspective(fov, GLfloat(width) / height, nearp, farp);
	setProjection(proj);
}

void Camera::positionCamera(vec4 ei, vec4 ni, vec4 vi, vec4 ui) {
	eye = ei;
	n = ni;
	v = vi;
	u = ui;
	viewMatrix = LookAt(eye, eye - n, v);
}

