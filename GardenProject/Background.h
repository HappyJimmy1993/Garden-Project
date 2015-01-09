#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <GL/glut.h>
#include <GL/GLAUX.H>

#pragma comment(lib, "glaux.lib")
#define MAPSIZE		128
#define GROUNDSTEP		1
#define WALLSTEP		32
#define HEIGHT_RATIO	2.0f
#define TEXTURE_NUM		3



void load_height_graph();
int get_ground_height(int x, int y);
void change_ground_height(int x, int y, int value);
void draw_ground();
void draw_wall();
void draw_sky();

AUX_RGBImageRec* LoadBMP(char *Filename);
void load_graphs();

void initBackground();
void drawBackground();


extern void* height_graph;

extern GLuint texture[TEXTURE_NUM];