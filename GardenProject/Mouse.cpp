#include "mouse.h"
using namespace std;

GLfloat mouse_angle_lr ;				//左右旋转角度
GLfloat mouse_angle_ud;				//上下旋转角度
GLfloat mouse_last_x, mouse_last_y;	//上一帧的鼠标坐标
GLfloat mouse_x, mouse_y;
bool mouse_clicked_left = false;
bool mouse_clicked_right = false;	//鼠标左右单击
GLfloat mouse_angle_speed_lr = 0.005f;
GLfloat mouse_angle_speed_ud = 0.005f;

void initMouse()
{
	glutMouseFunc(&getMouseClick);
	glutMotionFunc(&getMouseMove);
	glutPassiveMotionFunc(&getMouseMove);
}

void get_Groung_position(int mousex, int mousey, int &gx, int &gy, int &gz)
{
	GLdouble modelview[16], projection[16];
	int viewport[4];
	GLfloat winX, winY, winZ;
	GLdouble object_x, object_y, object_z;     //3D坐标
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glGetIntegerv(GL_VIEWPORT, viewport);
	winX = (float)mousex;
	winY = (float)viewport[3] - (float)mousey;
	glReadPixels(mousex, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);
	gluUnProject((GLdouble)winX, (GLdouble)winY, (GLdouble)winZ, modelview, projection, viewport, &object_x, &object_y, &object_z);
	gx = object_x;
	gy = object_y;
	gz = object_z;
	//cout << "x1:" << object_x << "\t y1:" << object_y << "\t z1:" << object_z << endl;
	//cout << "x2:" << x2 << "\t y2:" << y2 << "\t z2:" << z2 << endl;
	//cout << "WinZ" << winZ << endl << endl;
}

void getMouseClick(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		switch (button)
		{
		case GLUT_LEFT_BUTTON:
			mouse_clicked_left = true;
			//cout << "x:" << x << "\t y:" << y << endl;

			if (CreatFlower == true)
			{
				int temx, temy, temz;
				get_Groung_position(x, y, temx, temy, temz);
				flower_display_list[flower_display_list.size() - 1]->setPosition(temx, temz);
				flower_display_list[flower_display_list.size() - 1]->setAlpha(1.0f);
				CreatFlower = false;
				coutstat();
			}
			if (CreatTree == true)
			{
				int temx, temy, temz;
				get_Groung_position(x, y, temx, temy, temz);
				tree_display_list[tree_display_list.size() - 1]->setPosition(temx, temz);
				CreatTree = false;
				coutstat();
			}
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
			if ((!CreatTree) && (!CreatFlower))
			{
				int temx, temy, temz;
				get_Groung_position(mouse_last_x, mouse_last_y, temx, temy, temz);
				//cout << mouse_last_x << " " << mouse_last_y<<endl;
				GLfloat change_y = -(y - mouse_last_y);
				change_ground_height(temx, temz, change_y / 20);
				//cout << change_y << endl;
			}
			break;
		case GLUT_RIGHT_BUTTON:
			mouse_clicked_right = false;
			break;
		}
	}

}

void getMouseMove(int x, int y)
{
	mouse_x = x;
	mouse_y = y;
	if (CreatFlower == true)
	{
		int temx, temy, temz;
		get_Groung_position(x, y, temx, temy, temz);
		flower_display_list[flower_display_list.size() - 1]->setPosition(temx, temz);
		glutPostRedisplay();
	}
	if (CreatTree == true)
	{
		int temx, temy, temz;
		get_Groung_position(x, y, temx, temy, temz);
		tree_display_list[tree_display_list.size() - 1]->setPosition(temx, temz);
		glutPostRedisplay();
	}
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
	if (mouse_clicked_left)
	{


	}
}