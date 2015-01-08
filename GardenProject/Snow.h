#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <vector>
#include <time.h>
#include "Background.h"

using namespace std;
class Snow
{
public:
	Snow();
	void draw();
	void update();

	float x, y, z;
	float vx, vy, vz;
	float ax, ay, az;

	float size;

//	int TextureIndex;
	
	// material properties
//	GLfloat mat_stem[4];
//	GLfloat mat_blossom[4];
//	GLfloat mat_petal[4];
};

void creatsnow(int num);
void updatesnow();


extern vector<Snow*> SnowList;