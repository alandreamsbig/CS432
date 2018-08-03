#pragma once
#include "Drawable.h"
class treeBottom : //derived from drawable class
	public Drawable
{
public:
	void cleanup();
	void initOffsets();
	void initColors();
	void initTexCoords();
	void applyTransformation(mat4 input);
	void setNumTrees(int num);
	
	//constructor
	treeBottom();
	
	//destructor
	~treeBottom();


	GLuint modelMatrix_loc, viewMatrix_loc, projectionMatrix_loc;
	GLuint vPosition_loc;
	GLuint vColor_loc, vTexCoord_loc;
	GLuint treeOffset_Loc;
	GLuint buffer;
	void draw();

	int numTrees = 4096;
	mat4 model_matrix;
	vec4 treeOffsets[4096 * 2];
	vec4 vertexColors[150];

	GLuint texture;
	void setOffsets(vec4 newOffsets[]);

	std::string currentTextureName = "crate2.ppm";

	//texture coordinates
	vec2 textureCoords[690];

	//create tree vertices from blender
	vec4 fullVertices[150] = {
		vec4(-0.018886,1.199839,-0.373037,1.0),
		vec4(0.161257,0.605610,-0.198870,1.0),
		vec4(-0.018886,0.605610,-0.264436,1.0),
		vec4(0.231064,1.199839,-0.282063,1.0),
		vec4(0.257109,0.605610,-0.032850,1.0),
		vec4(0.161257,0.605610,-0.198870,1.0),
		vec4(0.364060,1.199839,-0.051708,1.0),
		vec4(0.223820,0.605610,0.155942,1.0),
		vec4(0.257109,0.605610,-0.032850,1.0),
		vec4(0.223820,0.605610,0.155942,1.0),
		vec4(0.114110,1.199839,0.381218,1.0),
		vec4(0.076966,0.605610,0.279167,1.0),
		vec4(0.076966,0.605610,0.279167,1.0),
		vec4(-0.151881,1.199839,0.381218,1.0),
		vec4(-0.114738,0.605610,0.279166,1.0),
		vec4(-0.114738,0.605610,0.279166,1.0),
		vec4(-0.355642,1.199839,0.210242,1.0),
		vec4(-0.261591,0.605610,0.155942,1.0),
		vec4(-0.261591,0.605610,0.155942,1.0),
		vec4(-0.401831,1.199839,-0.051708,1.0),
		vec4(-0.294880,0.605610,-0.032850,1.0),
		vec4(-0.018886,1.199839,-0.373037,1.0),
		vec4(-0.151881,1.199839,0.381218,1.0),
		vec4(0.317871,1.199839,0.210242,1.0),
		vec4(-0.199028,0.605610,-0.198870,1.0),
		vec4(-0.018886,1.199839,-0.373037,1.0),
		vec4(-0.018886,0.605610,-0.264436,1.0),
		vec4(-0.294880,0.605610,-0.032850,1.0),
		vec4(-0.268836,1.199839,-0.282063,1.0),
		vec4(-0.199028,0.605610,-0.198870,1.0),
		vec4(0.231064,0.024393,-0.282063,1.0),
		vec4(-0.355642,0.024393,0.210242,1.0),
		vec4(-0.401831,0.024393,-0.051708,1.0),
		vec4(-0.294880,0.605610,-0.032850,1.0),
		vec4(-0.268836,0.024393,-0.282063,1.0),
		vec4(-0.401831,0.024393,-0.051708,1.0),
		vec4(-0.199028,0.605610,-0.198870,1.0),
		vec4(-0.018886,0.024393,-0.373037,1.0),
		vec4(-0.268836,0.024393,-0.282063,1.0),
		vec4(-0.355642,0.024393,0.210242,1.0),
		vec4(-0.294880,0.605610,-0.032850,1.0),
		vec4(-0.401831,0.024393,-0.051708,1.0),
		vec4(-0.114738,0.605610,0.279166,1.0),
		vec4(-0.355642,0.024393,0.210242,1.0),
		vec4(-0.151881,0.024393,0.381218,1.0),
		vec4(0.076966,0.605610,0.279167,1.0),
		vec4(-0.151881,0.024393,0.381218,1.0),
		vec4(0.114110,0.024393,0.381218,1.0),
		vec4(0.223820,0.605610,0.155942,1.0),
		vec4(0.114110,0.024393,0.381218,1.0),
		vec4(0.317871,0.024393,0.210242,1.0),
		vec4(0.257109,0.605610,-0.032850,1.0),
		vec4(0.317871,0.024393,0.210242,1.0),
		vec4(0.364060,0.024393,-0.051708,1.0),
		vec4(0.231064,0.024393,-0.282063,1.0),
		vec4(0.257109,0.605610,-0.032850,1.0),
		vec4(0.364060,0.024393,-0.051708,1.0),
		vec4(-0.018886,0.605610,-0.264436,1.0),
		vec4(0.231064,0.024393,-0.282063,1.0),
		vec4(-0.018886,0.024393,-0.373037,1.0),
		vec4(-0.018886,1.199839,-0.373037,1.0),
		vec4(0.231064,1.199839,-0.282063,1.0),
		vec4(0.161257,0.605610,-0.198870,1.0),
		vec4(0.231064,1.199839,-0.282063,1.0),
		vec4(0.364060,1.199839,-0.051708,1.0),
		vec4(0.257109,0.605610,-0.032850,1.0),
		vec4(0.364060,1.199839,-0.051708,1.0),
		vec4(0.317871,1.199839,0.210242,1.0),
		vec4(0.223820,0.605610,0.155942,1.0),
		vec4(0.223820,0.605610,0.155942,1.0),
		vec4(0.317871,1.199839,0.210242,1.0),
		vec4(0.114110,1.199839,0.381218,1.0),
		vec4(0.076966,0.605610,0.279167,1.0),
		vec4(0.114110,1.199839,0.381218,1.0),
		vec4(-0.151881,1.199839,0.381218,1.0),
		vec4(-0.114738,0.605610,0.279166,1.0),
		vec4(-0.151881,1.199839,0.381218,1.0),
		vec4(-0.355642,1.199839,0.210242,1.0),
		vec4(-0.261591,0.605610,0.155942,1.0),
		vec4(-0.355642,1.199839,0.210242,1.0),
		vec4(-0.401831,1.199839,-0.051708,1.0),
		vec4(0.364060,1.199839,-0.051708,1.0),
		vec4(0.231064,1.199839,-0.282063,1.0),
		vec4(0.317871,1.199839,0.210242,1.0),
		vec4(-0.018886,1.199839,-0.373037,1.0),
		vec4(-0.268836,1.199839,-0.282063,1.0),
		vec4(-0.401831,1.199839,-0.051708,1.0),
		vec4(-0.401831,1.199839,-0.051708,1.0),
		vec4(-0.355642,1.199839,0.210242,1.0),
		vec4(-0.018886,1.199839,-0.373037,1.0),
		vec4(-0.151881,1.199839,0.381218,1.0),
		vec4(0.114110,1.199839,0.381218,1.0),
		vec4(0.317871,1.199839,0.210242,1.0),
		vec4(0.317871,1.199839,0.210242,1.0),
		vec4(0.231064,1.199839,-0.282063,1.0),
		vec4(-0.018886,1.199839,-0.373037,1.0),
		vec4(-0.018886,1.199839,-0.373037,1.0),
		vec4(-0.355642,1.199839,0.210242,1.0),
		vec4(-0.151881,1.199839,0.381218,1.0),
		vec4(-0.199028,0.605610,-0.198870,1.0),
		vec4(-0.268836,1.199839,-0.282063,1.0),
		vec4(-0.018886,1.199839,-0.373037,1.0),
		vec4(-0.294880,0.605610,-0.032850,1.0),
		vec4(-0.401831,1.199839,-0.051708,1.0),
		vec4(-0.268836,1.199839,-0.282063,1.0),
		vec4(-0.268836,0.024393,-0.282063,1.0),
		vec4(-0.018886,0.024393,-0.373037,1.0),
		vec4(-0.401831,0.024393,-0.051708,1.0),
		vec4(0.231064,0.024393,-0.282063,1.0),
		vec4(0.364060,0.024393,-0.051708,1.0),
		vec4(0.317871,0.024393,0.210242,1.0),
		vec4(0.317871,0.024393,0.210242,1.0),
		vec4(0.114110,0.024393,0.381218,1.0),
		vec4(-0.151881,0.024393,0.381218,1.0),
		vec4(-0.151881,0.024393,0.381218,1.0),
		vec4(-0.355642,0.024393,0.210242,1.0),
		vec4(0.231064,0.024393,-0.282063,1.0),
		vec4(-0.401831,0.024393,-0.051708,1.0),
		vec4(-0.018886,0.024393,-0.373037,1.0),
		vec4(0.231064,0.024393,-0.282063,1.0),
		vec4(0.231064,0.024393,-0.282063,1.0),
		vec4(0.317871,0.024393,0.210242,1.0),
		vec4(-0.151881,0.024393,0.381218,1.0),
		vec4(-0.294880,0.605610,-0.032850,1.0),
		vec4(-0.199028,0.605610,-0.198870,1.0),
		vec4(-0.268836,0.024393,-0.282063,1.0),
		vec4(-0.199028,0.605610,-0.198870,1.0),
		vec4(-0.018886,0.605610,-0.264436,1.0),
		vec4(-0.018886,0.024393,-0.373037,1.0),
		vec4(-0.355642,0.024393,0.210242,1.0),
		vec4(-0.261591,0.605610,0.155942,1.0),
		vec4(-0.294880,0.605610,-0.032850,1.0),
		vec4(-0.114738,0.605610,0.279166,1.0),
		vec4(-0.261591,0.605610,0.155942,1.0),
		vec4(-0.355642,0.024393,0.210242,1.0),
		vec4(0.076966,0.605610,0.279167,1.0),
		vec4(-0.114738,0.605610,0.279166,1.0),
		vec4(-0.151881,0.024393,0.381218,1.0),
		vec4(0.223820,0.605610,0.155942,1.0),
		vec4(0.076966,0.605610,0.279167,1.0),
		vec4(0.114110,0.024393,0.381218,1.0),
		vec4(0.257109,0.605610,-0.032850,1.0),
		vec4(0.223820,0.605610,0.155942,1.0),
		vec4(0.317871,0.024393,0.210242,1.0),
		vec4(0.231064,0.024393,-0.282063,1.0),
		vec4(0.161257,0.605610,-0.198870,1.0),
		vec4(0.257109,0.605610,-0.032850,1.0),
		vec4(-0.018886,0.605610,-0.264436,1.0),
		vec4(0.161257,0.605610,-0.198870,1.0),
		vec4(0.231064,0.024393,-0.282063,1.0),
	};
};

