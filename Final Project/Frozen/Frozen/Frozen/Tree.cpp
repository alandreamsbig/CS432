#include "Tree.h"


void Tree::cleanup()
{
	treebottoms->cleanup();
	treetops->cleanup();
}


//initialize tree offset
void Tree::initOffsets()
{
	for (int i = 0; i < numTrees; i++)
	{
		double x, y, z;
		double scale = 45;

		double t1, t2;
		t1 = 15 * rand() / RAND_MAX;
		t2 = 15* rand() / RAND_MAX;

		x = scale*rand() / RAND_MAX;
		z = scale*rand() / RAND_MAX;
		x += t1;
		z += t2;

		if (scale * rand() / RAND_MAX < scale / 2.0)
		{
			x = -x;
		}

		if (scale * rand() / RAND_MAX < scale / 2.0)
		{
			z = -z;
		}

		
		treeOffsets[i] = vec4(x,0,z, 0.0);
	}
}

//construct the tree
Tree::Tree()
{
	initOffsets();
	model_matrix = mat4(1.0);

	treebottoms = new treeBottom();
	treetops = new treeTop();


	treebottoms->setNumTrees(numTrees);
	treetops->setNumTrees(numTrees);

	treebottoms->setOffsets(treeOffsets);
	treetops->setOffsets(treeOffsets);

	treebottoms->applyTransformation(Scale(5,3,5));
	treetops->applyTransformation(Scale(5, 3, 5));

}

//set tree projection matrix
void Tree::setProjectionMatrix(mat4 newProj)
{
	treebottoms->setProjectionMatrix(newProj);
	treetops->setProjectionMatrix(newProj);
}

//update tree view matrix
void Tree::updateViewMatrix(mat4 newView)
{
	treebottoms->updateViewMatrix(newView);
	treetops->updateViewMatrix(newView);
}

//draw tree
void Tree::draw()
{
	treebottoms->updateViewMatrix(view_matrix);
	treetops->updateViewMatrix(view_matrix);
	treebottoms->setProjectionMatrix(projection_matrix);
	treetops->setProjectionMatrix(projection_matrix);

	treebottoms->draw();
	treetops->draw();
}

//tree destructor
Tree::~Tree()
{
}
