#include "Snow.h"
const GLfloat Pi = 3.1415926536f;
vector<Snow*> SnowList;
bool is_snow;
bool have_wind;
int snowcount;
int snowlevel;
int windcount;
int checktouchnum = 0;

Snow::Snow()
{
	x = (rand() % (MAPSIZE * 10)) / 10;
	y = 50;
	z = (rand() % (MAPSIZE * 10)) / 10;
	vx = 0;
	vy = -0.2 - (rand() % 100) / 1000;
	vz = 0;
	ax = 0;
	ay = -0.0005;
	az = 0;
	size = (float)(rand() % 100)/500;
	touched = false;
}

void Snow::draw()
{
	//glEnable(GL_TEXTURE_2D);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	//glBindTexture(GL_TEXTURE_2D, texture[2]);
	glNormal3f(0.0f, 0.0f, 1.0f);

	//glPointSize(2.0f);
	//glBegin(GL_POINTS);
	//glVertex3f(x,y,z);

	//glEnd();

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
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);

}

void Snow::update(int key)
{
	checktouch();
	if (touched == false)
	{
		x += vx;
		y += vy;
		z += vz;
		vx += ax;
		vy += ay;
		vz += az;
		if (x >= MAPSIZE) x = MAPSIZE - 1;
		if (x < 0) x = 0;
		if (z >= MAPSIZE) z = MAPSIZE - 1;
		if (z < 0) z = 0;

		if (have_wind)
		{
			ax = cos((float)(windcount + key) / 180 * 3.1415926) / 120;
			az = sin((float)(windcount + key) / 180 * 3.1415926) / 120;

		}
		else
		{
			ax = 0;
			az = 0;
			vx = vx / 2;
			vz = vz / 2;
		}

	}

}

void Snow::checktouch()
{
	if (checktouchnum > 0) return;
	if (y < 20)
	{
		int treenum = tree_display_list.size();
		int flowersize = flower_display_list.size();
		if (CreatFlower) flowersize--;
		if (CreatTree) treenum--;
		for (int i = 0; i < treenum; ++i)
		{
			Tree* tem = tree_display_list[i];
			if ((x > tem->x - tem->treeRadius) && (x < tem->x + tem->treeRadius) &&
				(z > tem->z - tem->treeRadius) && (z < tem->z + tem->treeRadius) &&
				(y < get_ground_height(x, z) + tem->trunkHeight))
			{
				float onelevel = tem->trunkHeight / (GLfloat)(tem->nLevels + 2);
				int level = (y - get_ground_height(x, z)) / onelevel - 1;
				if ((level <= tem->nLevels) && (level >= 1))
				{
					float temx = x + vx - tem->x;
					float temy = y - onelevel * (level + 1);
					float temz = z + vz - tem->z;
					float r = tem->treeRadius*(tem->nLevels + 1 - level) / (GLfloat)(tem->nLevels + 1);
					r = r * (onelevel - temy) / (tem->trunkHeight / (GLfloat)(tem->nLevels + 1));
					if (temx * temx + temz * temz < r * r) touched = true;
				}
			}

				//touched = true;
		}

		for (int i = 0; i < flowersize; ++i)
		{
			Flower* tem = flower_display_list[i];
			if ((x > tem->x - tem->petalLength) && (x < tem->x + tem->petalLength) &&
				(z > tem->z - tem->petalLength) && (z < tem->z + tem->petalLength) &&
				(y < get_ground_height(x, z) + tem->stemHeight + tem->petalLength*0.4) &&
				(y > get_ground_height(x, z) + tem->stemHeight))
				touched = true;
		}
	}

}

void creatsnow(int num)
{
	for (int i = 0; i < num; ++i)
	{
		Snow* tem = new Snow;
		//cout << tem->x << "    "<<tem->z << endl;
		SnowList.push_back(tem);
	}
}

void updatesnow()
{
	windcount += 5;
	windcount = windcount % 360;
	checktouchnum = max(checktouchnum - 1, 0);
	for (int i = 0; i < SnowList.size(); ++i)
	{
		if (checktouchnum > 0) SnowList[i]->touched = false;
		SnowList[i]->update(i);
		if (SnowList[i]->y < get_ground_height((int)SnowList[i]->x, (int)SnowList[i]->z))
		{
			Snow* tem = SnowList[i];
			add_snow_graph(tem->x, tem->z, 1);
			//cout << get_snow_height(tem->x, tem->z) << endl;
			SnowList.erase(SnowList.begin() + i);
			delete tem;
		}
	}
	if (is_snow)
	{
		creatsnow(snowlevel);
	}
	else
	{
		snow_stopped();
		//snowcount++;
		//if (snowcount > 10)
		//{
		//	
		//	snowcount = 0;
		//}
	}

}

void start_wind()
{
	windcount = 0;
	have_wind = true;
	cout << "start wind";
}
void stop_wind()
{
	have_wind = false;
	cout << "stop wind";
}

void snow_down()
{
	checktouchnum = 20;
}

void change_snow_level(int value)
{
	snowlevel += value;
	snowlevel = max(snowlevel, 10);
	snowlevel = min(snowlevel, 40);
}