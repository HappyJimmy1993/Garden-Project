#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include "ChangeView.h"
#include "Keyboard.h"
#include "Flower.h"
#include "Tree.h"
#include "Background.h"
extern GLfloat mouse_angle_lr;				//左右旋转角度
extern GLfloat mouse_angle_ud;				//上下旋转角度
extern GLfloat mouse_last_x, mouse_last_y;	//上一帧的鼠标坐标
extern GLfloat mouse_x, mouse_y;	//上一帧的鼠标坐标
extern bool mouse_clicked_left;
extern bool mouse_clicked_right;	//鼠标左右单击


void getMouseClick(int button, int state, int x, int y);
void getMouseMove(int x, int y);


void get_Groung_position(int mousex, int mousey, int &gx, int &gy, int &gz);
void initMouse();