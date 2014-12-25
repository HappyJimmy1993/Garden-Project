#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <vector>
#include "Background.h"
using namespace std;


class Tree
{
public:
	Tree();
	void draw();
	void setPosition(GLfloat x, GLfloat z){ this->x = x; this->z = z; }
	void getPosition(GLfloat& x, GLfloat& z){ x = this->x; z = this->z; }
	void change_tree_level(int value);

	GLfloat x, z;	
	int nSlices;
	int nStacks;
	int nLevels;
	GLfloat trunkRadius;
	GLfloat trunkHeight;
	GLfloat treeRadius;
	// material properties
	GLfloat mat_trunk[4];
	GLfloat mat_tree[4];
};

extern vector<Tree*> tree_display_list;