#pragma once
#include "Drawable.h"
#include "treeBottom.h";
#include "treeTop.h";

class Tree : //derived from drawable class
	public Drawable
{
public:

	//constructor
	Tree();

	//set tree projection matrix
	void setProjectionMatrix(mat4 newProj);

	void updateViewMatrix(mat4 newView);

	void draw();
	void cleanup();

	//destructor
	~Tree();

	void initOffsets();

	//number of trees
	int numTrees = 4096;
	mat4 model_matrix;

	vec4 treeOffsets[4096];

	treeBottom* treebottoms;
	treeTop* treetops;


};

