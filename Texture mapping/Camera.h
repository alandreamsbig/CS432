#ifndef __CAMERA_H__
#define __CAMERA_H__
#include "Angel.h"

class Camera {
public:
	Camera();
	mat4 getViewMatrix() const { return viewMatrix;}
	mat4 getProjectionMatrix() const { return projectionMatrix; }
	void positionCamera(vec4, vec4, vec4, vec4);
	void setProjection(mat4 p) { projectionMatrix = p; }
	void changeProjection(int width, int height);
private:
	vec4 eye, u, v, n;
	mat4 viewMatrix, projectionMatrix;
};

#endif
