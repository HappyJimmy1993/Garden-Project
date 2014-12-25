#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <vector>
#include "Background.h"
using namespace std;
class Flower
{
public:
	Flower();
	void draw();
	void setPosition(GLfloat x, GLfloat z){ this->x = x; this->z = z; }
	void getPosition(GLfloat& x, GLfloat& z){ x = this->x; z = this->z; }
	void setAlpha(GLfloat alpha);

	void change_petal_R(GLfloat value);
	void change_petal_G(GLfloat value);
	void change_petal_B(GLfloat value);
	void change_petal_NUM(int value);
	
	GLfloat x,z;
	int nSlices;
	int nStacks;
	int petalNum;
	double stemRadius;
	double stemHeight;
	double blossomRadius;
	double petalLength;

	// material properties
	GLfloat mat_stem[4];
	GLfloat mat_blossom[4];
	GLfloat mat_petal[4];
};

extern vector<Flower*> flower_display_list;
