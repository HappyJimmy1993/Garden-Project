#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <GL/glut.h>
#include <iostream>
#include "Background.h"
using namespace std;

#define MAXHEIGHT 30

class ViewStatus
{
public:
	GLfloat angle_ud;
	GLfloat angle_lr;
	GLfloat angle_change_speed;
	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLfloat lookx;
	GLfloat looky;
	GLfloat lookz;
	GLfloat move_speed;
};

extern ViewStatus viewstat;



void ViewFresh();

void walk_left();
void walk_right();
void walk_up();
void walk_down();
void turn_left();
void turn_right();