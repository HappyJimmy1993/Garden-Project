#include "ChangeView.h"

ViewStatus viewstat = { 0.0f, 0.0f, 0.03f, 0.6f, 1.8f, 5.0f, 0.0f, 0.0f, -1.0f, 0.3f };

void ViewFresh()
{
	if (viewstat.angle_ud > 0.5f) viewstat.angle_ud = 0.5f;
	if (viewstat.angle_ud < -0.5f) viewstat.angle_ud = -0.5f;
	viewstat.lookx = sin(viewstat.angle_lr) * cos(viewstat.angle_ud);
	viewstat.looky = sin(viewstat.angle_ud);
	viewstat.lookz = -cos(viewstat.angle_lr) * cos(viewstat.angle_ud);
	glLoadIdentity();
	gluLookAt(viewstat.x, viewstat.y, viewstat.z,
		viewstat.x + viewstat.lookx, viewstat.y - viewstat.looky, viewstat.z + viewstat.lookz,
		0.0f, 1.0f, 0.0f);
	//myDisplay();
}

void walk_left()
{
	viewstat.x += viewstat.lookz * viewstat.move_speed;
	viewstat.z -= viewstat.lookx * viewstat.move_speed;
	ViewFresh();
}

void walk_right()
{
	viewstat.x -= viewstat.lookz * viewstat.move_speed;
	viewstat.z += viewstat.lookx * viewstat.move_speed;
	ViewFresh();
}

void walk_up()
{
	GLfloat moveahead = abs(cos(viewstat.angle_ud));
	viewstat.x += moveahead * viewstat.lookx * viewstat.move_speed;
	viewstat.z += moveahead * viewstat.lookz * viewstat.move_speed;
	GLfloat moveup = -sin(viewstat.angle_ud);
	viewstat.y += moveup * viewstat.move_speed;
	ViewFresh();
}

void walk_down()
{
	GLfloat moveahead = abs(cos(viewstat.angle_ud));
	viewstat.x -= moveahead * viewstat.lookx * viewstat.move_speed;
	viewstat.z -= moveahead * viewstat.lookz * viewstat.move_speed;
	GLfloat moveup = -sin(viewstat.angle_ud);
	viewstat.y -= moveup * viewstat.move_speed;
	ViewFresh();
}

void turn_left()
{
	viewstat.angle_lr -= viewstat.angle_change_speed;
	ViewFresh();
}

void turn_right()
{
	viewstat.angle_lr += viewstat.angle_change_speed;
	ViewFresh();
}