#pragma once
#include "Angel.h"
#include "Light.h"
#include <string>
#include <vector>;

class Drawable
{
public:
	Drawable();

	virtual ~Drawable();

	unsigned char * ppmRead(char * filename, int * width, int * height);


	void updateEye(vec4 eye);

	virtual void changeBrightness( double delta );

	virtual void scale(double xscale, double yscale);
	void setProjectionMatrix(mat4 matrix);
	virtual void translate(double xtranslate, double ytranslate);
	virtual void rotate(int degrees);
	void setMaterial(vec4 a, vec4 d, vec4 s, float sh);
	virtual void rotateWithOriginTranslation(int degree);
	mat3 getModelMatrix();
	virtual vec2 calculateCenter();

	
	void setLight(Light l, int lightNum);
	void updateViewMatrix(mat4 newViewMatrix);
	Light lights[2];
	vec4 currEye;
	mat4 projection_matrix, view_matrix;

	GLuint specular_Loc, diffuse_Loc, ambient_Loc, normal_Loc, alpha_Loc;
	vec4 diffuse, specular, ambient;
	float shine;


	virtual void draw();

	GLuint objBuffer, VAO, program;
	std::string vShaderName, fShaderName;
	bool isUniform = false;
	int numVertices = 0;
	vec4 uniformColorVec;

};
