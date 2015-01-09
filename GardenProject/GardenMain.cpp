// Garden.cpp : 定义控制台应用程序的入口点。
//
#define GLUT_DISABLE_ATEXIT_HACK
//#pragma comment(lib, "glui32.lib") 
#include <stdlib.h>
#include <GL/GLAUX.H>
#include <GL/glut.h>
//#include <GL/glui.h>
#include <Windows.h>
#include <math.h>
#include <stdio.h>

#include "Mouse.h"
#include "Keyboard.h"
#include "Flower.h"
#include "Background.h"
#include "Tree.h"
#include "Snow.h"
using namespace std;
const int n = 20;
const GLfloat R = 0.5f;
const GLfloat Pi = 3.1415926536f;


void Allinit()
{
	initMouse();
	initKeyboard();
//	initFlower();
	initBackground();
	init_snow_graph();
	is_snow = true;
	have_wind = false;
	snowlevel = 20;
	coutstat();
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	GLfloat AmbientLight[4] = { 1, 1, 1, 1 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
}

void myReshape(GLint w, GLint h)
{
	if (h == 0) h = 1;
	glMatrixMode(GL_PROJECTION);
	glViewport(0, 0, w, h);
	glLoadIdentity();
	gluPerspective(45.0f, (GLdouble)w / (GLdouble)h, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	ViewFresh();
}

void myDisplay(void)
{

	glClearColor(0.0f, 0.5f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	GLfloat blank[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blank);
	
	//Tree tem;
	//tem.setPosition(10, 10);
	//tem.draw();
	drawBackground();
	draw_snow_ground();
	int flowersize = flower_display_list.size();
	for (int i = 0; i < flowersize; ++i)
		flower_display_list[i]->draw();

	int treesize = tree_display_list.size();
	for (int i = 0; i < treesize; ++i)
		tree_display_list[i]->draw();

	int snowsize = SnowList.size();
	for (int i = 0; i < snowsize; ++i)
		SnowList[i]->draw();

	updatesnow();

	
	// << "Change!" << endl;
	glFlush();
	glutSwapBuffers();
}

void myTimer(int value)
{

}

int main(int argc, char *argv[]) {
	srand((unsigned)time(0));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(400, 400);
	glutInitWindowSize(800, 600);
	int main_window = glutCreateWindow("MyGarden");
	//load_all();
	glutDisplayFunc(&myDisplay);
	glutReshapeFunc(&myReshape);

	//GLUI *glui = GLUI_Master.create_glui("GLUI");
	//int wireframe, segments;
	//new GLUI_Checkbox(glui, "Wireframe", &wireframe);
	//(new GLUI_Spinner(glui, "Segments:", &segments))
	//	->set_int_limits(3, 60);

	//glui->set_main_gfx_window(main_window);

	/* We register the idle callback with GLUI, *not* with GLUT */
	//GLUI_Master.set_glutIdleFunc(myDisplay);
	//cout << "\102";

	glutTimerFunc(1000, &myTimer, 0);
	glutIdleFunc(&myDisplay);
	Allinit();
	glutMainLoop();
	return 0;
}