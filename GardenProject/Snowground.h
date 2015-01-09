#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <vector>
#include <time.h>
#include "Background.h"
#define SNOW_RATIO	4
using namespace std;

extern void* snow_graph;

void init_snow_graph();
void add_snow_graph(int x, int y, int value);
float get_snow_height(int x, int y);
void snow_stopped();

void draw_snow_ground();