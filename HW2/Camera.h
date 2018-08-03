#ifndef __CAMERA_H__
#define __CAMERA_H__
#include "Angel.h"
#include <vector>

using namespace std;

class Camera {

public:
	
	Camera();
	void pitchUp();
	void pitchDown();
	void YawClockwise();
	void YawCounterwise();
	void RollClockwise();
	void RollCounterwise();
	void MoveTowards();
	void MoveAway();
	void MoveLeft();
	void MoveRight();
	void getProj(bool check);

	mat3 modelmatrix;
	mat4 view_matrix;

	mat4 proj_matrix;

private:

	const float Step2 = 3.0;
	const float Step = 0.5;
	vec4 eye, at, up, u, v, n;
};

#endif
