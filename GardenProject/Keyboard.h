#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include "ChangeView.h"
#include "Flower.h"
#include "Tree.h"
#include "Mouse.h"
#include "Save.h"
#include "Snow.h"
#include "cout.h"
void getKeyboardPress(unsigned char key, int x, int y);
void getSpecialKeyPress(int key, int x, int y);

void initKeyboard();

extern bool CreatFlower;
extern bool CreatTree;