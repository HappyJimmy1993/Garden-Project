#include "Snow.h"
const GLfloat Pi = 3.1415926536f;
vector<Snow*> SnowList;


Snow::Snow()
{
	x = (rand() % (MAPSIZE * 10)) / 10;
	y = 50;
	z = (rand() % (MAPSIZE * 10)) / 10;
	vx = 0;
	vy = -0.1 - (rand() % 100) / 10000;
	vz = 0;
	ax = 0;
	ay = -0.0005;
	az = 0;
	size = (float)(rand() % 100)/500;
}

void Snow::draw()
{
	//glEnable(GL_TEXTURE_2D);

	//glBindTexture(GL_TEXTURE_2D, texture[2]);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x - size, y - size, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x - size, y + size, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + size, y + size, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + size, y - size, z);
	glEnd();

	//glColor3f(1.0f, 1.0f, 1.0f);
	//glPushMatrix();
	//glTranslatef(x, y, z);
	//glutSolidSphere(size, 10, 10);
	//glPopMatrix();

	//glDisable(GL_TEXTURE_2D);

}

void Snow::update()
{
	x += vx;
	y += vy;
	z += vz;
	vx += ax;
	vy += ay;
	vz += az;
}

void creatsnow(int num)
{
	for (int i = 0; i < num; ++i)
	{
		Snow* tem = new Snow;
		cout << tem->x << "    "<<tem->z << endl;
		SnowList.push_back(tem);
	}
}

void updatesnow()
{
	for (int i = 0; i < SnowList.size(); ++i)
	{
		SnowList[i]->update();
		if (SnowList[i]->y < get_ground_height((int)SnowList[i]->x, (int)SnowList[i]->z))
		{
			Snow* tem = SnowList[i];
			SnowList.erase(SnowList.begin() + i);
			delete tem;
		}
	}
}