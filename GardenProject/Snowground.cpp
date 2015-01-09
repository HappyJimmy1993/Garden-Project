#include "Snowground.h"

void* snow_graph = malloc(MAPSIZE * MAPSIZE *sizeof(float));

void init_snow_graph()
{
	for (int i = 0; i < MAPSIZE * MAPSIZE ; ++i)
		((float*)snow_graph)[i] = 0.0f;

}

void add_snow_graph(int x, int y, int value)
{
	int temx = x % MAPSIZE;
	int temy = y % MAPSIZE;
	float height = ((float*)snow_graph)[temx + temy * MAPSIZE];
	((float*)snow_graph)[temx + temy * MAPSIZE] = min(height + value, 127);
}

float get_snow_height(int x, int y)
{
	int temx = x % MAPSIZE;
	int temy = y % MAPSIZE;
	float height = ((float*)snow_graph)[temx + temy * MAPSIZE];
	return height;
}

void snow_stopped()
{
	for (int i = 0; i < MAPSIZE * MAPSIZE; ++i)
	{
		float height = ((float*)snow_graph)[i];
		((float*)snow_graph)[i] = max(height - 0.01f, 0);
	}
}

void draw_snow_ground()
{
	float mat[4];
	mat[0] = 1.0f;
	mat[1] = 1.0f;
	mat[2] = 1.0f;
	mat[3] = 0.0f;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_NORMALIZE);
	for (int i = 0; i < MAPSIZE; ++i)
		for (int j = 0; j < MAPSIZE; ++j)
		{
		int temx = i;
		int temz = j;
		float temy = get_snow_height(temx, temz);
		float y0 = get_ground_height(temx, temz)+0.1;
		if (temy < SNOW_RATIO * 2 -1)
		{
			//cout << (float)temy / 10;
			//glColor4f(1.0f, 1.0f, 1.0f, 1-(float)temy / 10);
			mat[3] = min(temy / SNOW_RATIO, 1.0f);
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, mat);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(temx, y0, temz);

			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(temx, y0, temz + 1);

			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(temx + 1, y0, temz + 1);

			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(temx + 1, y0, temz);
			glEnd();
		}
		else
		{
			mat[3] = 1.0f;
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat);
			glPushMatrix();
			glTranslatef(temx+0.5, y0-0.4, temz+0.5);
			for (int i = SNOW_RATIO; i < temy; i += SNOW_RATIO)
			{
				glTranslatef(0, 0.1, 0);
				glutSolidCube(1.0f);
			}
			//glutSolidCube(1.0f);
			glPopMatrix();

			//glBegin(GL_QUADS);
			//glTexCoord2f(0.0f, 0.0f);
			//glVertex3f(temx, y0+, temz);

			//glTexCoord2f(1.0f, 0.0f);
			//glVertex3f(temx, y0, temz + 1);

			//glTexCoord2f(1.0f, 1.0f);
			//glVertex3f(temx + 1, y0, temz + 1);

			//glTexCoord2f(0.0f, 1.0f);
			//glVertex3f(temx + 1, y0, temz);
			//glEnd();
		}

		}

	glDisable(GL_NORMALIZE);
	glDisable(GL_BLEND);
}