#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <vector>
#include <time.h>
#include "Snowground.h"
#include "Tree.h"
#include "Flower.h"
#include "Keyboard.h"
using namespace std;
class Snow
{
public:
	Snow();
	void draw();
	void update(int key);
	void checktouch();

	float x, y, z;
	float vx, vy, vz;
	float ax, ay, az;

	float size;
	bool touched;
//	int TextureIndex;
	
	// material properties
//	GLfloat mat_stem[4];
//	GLfloat mat_blossom[4];
//	GLfloat mat_petal[4];
};

void creatsnow(int num);
void updatesnow();
void start_wind();
void stop_wind();
void snow_down();
void change_snow_level(int value);

extern bool is_snow;
extern int snowcount;
extern int snowlevel;
extern bool have_wind;
extern vector<Snow*> SnowList;