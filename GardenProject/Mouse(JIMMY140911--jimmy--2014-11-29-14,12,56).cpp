#include "mouse.h"
using namespace std;

GLfloat mouse_angle_lr ;				//左右旋转角度
GLfloat mouse_angle_ud;				//上下旋转角度
GLfloat mouse_last_x, mouse_last_y;	//上一帧的鼠标坐标
bool mouse_clicked_left = false;
bool mouse_clicked_right = false;	//鼠标左右单击
GLfloat mouse_angle_speed_lr = 0.005f;
GLfloat mouse_angle_speed_ud = 0.005f;

void initMouse()
{
	glutMouseFunc(&getMouseClick);
	glutMotionFunc(&getMouseMove);
}

void getMouseClick(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		switch (button)
		{
		case GLUT_LEFT_BUTTON:
			mouse_clicked_left = true;
			cout << "x:" << x << "\t y:" << y << endl;
			double modelview[16], projection[16];
			int viewport[4];
			float winX, winY, winZ;
			double object_x, object_y, object_z;     //3D坐标
			glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
			glGetDoublev(GL_PROJECTION_MATRIX, projection);
			glGetIntegerv(GL_VIEWPORT, viewport);
			winX = (float)x;
			winY = (float)viewport[3] - (float)y;
			glReadPixels(x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);
			gluUnProject((GLdouble)winX, (GLdouble)winY, (GLdouble)winZ, modelview, projection, viewport, &object_x, &object_y, &object_z); 
			cout << "x1:" << object_x << "\t y1:" << object_y << "\t z1:" << object_z << endl;
			//cout << "x2:" << x2 << "\t y2:" << y2 << "\t z2:" << z2 << endl;
			cout << "WinZ" << winZ << endl << endl;
			break;
		case GLUT_RIGHT_BUTTON:
			mouse_clicked_right = true;
			break;
		}
		mouse_last_x = x;
		mouse_last_y = y;
	}
	else if (state == GLUT_UP)
	{
		switch (button)
		{
		case GLUT_LEFT_BUTTON:
			mouse_clicked_left = false;
			break;
		case GLUT_RIGHT_BUTTON:
			mouse_clicked_right = false;
			break;
		}
	}

}

void getMouseMove(int x, int y)
{
	if (mouse_clicked_right)
	{
		GLfloat change_x = (x - mouse_last_x) * mouse_angle_speed_lr;
		GLfloat change_y = (y - mouse_last_y) * mouse_angle_speed_ud;
		mouse_last_x = x;
		mouse_last_y = y;
		viewstat.angle_lr += change_x;
		viewstat.angle_ud += change_y;
		ViewFresh();
	}
}