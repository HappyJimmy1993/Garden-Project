#include "Background.h"
using namespace std;



void* height_graph = malloc(MAPSIZE * MAPSIZE);

GLuint texture[TEXTURE_NUM];

void load_height_graph()
{
	fstream load_graph;
	load_graph.open("Data/height_graph.raw", ios::out | ios::binary | ios::in);
	memset(height_graph, (char)0, MAPSIZE*MAPSIZE*sizeof(char));
	if (load_graph.is_open()) {
		//fprintf(stdout, "Terrain file open success\n");
	}
	else {
		//fprintf(stderr, "Terrain file open fail\n");
	}
	load_graph.read((char*)height_graph, MAPSIZE * MAPSIZE);
}

int get_ground_height(int x, int y)
{
	int temx = x % MAPSIZE;
	int temy = y % MAPSIZE;
	int height = ((unsigned char*)height_graph)[temx + temy * MAPSIZE];
//	if (height > 100) cout << x << "\t" << y << "\t" << height << endl;
	return height / HEIGHT_RATIO;
}

void change_ground_height(int x, int y, int value)
{
	int temx = x % MAPSIZE;
	int temy = y % MAPSIZE;
	((unsigned char*)height_graph)[temx + temy * MAPSIZE] += value;
	//	if (height > 100) cout << x << "\t" << y << "\t" << height << endl;
}

void draw_ground()
{


	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_QUADS);
	for (int i = 0; i < MAPSIZE; i += GROUNDSTEP)
		for (int j = 0; j < MAPSIZE; j += GROUNDSTEP)
		{
			int temx = i;
			int temz = j;
			int temy = get_ground_height(temx, temz);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(temx, temy, temz);

			temx = i;
			temz = j + GROUNDSTEP;
			temy = get_ground_height(temx, temz);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(temx, temy, temz);

			temx = i + GROUNDSTEP;
			temz = j + GROUNDSTEP;
			temy = get_ground_height(temx, temz);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(temx, temy, temz);

			temx = i + GROUNDSTEP;
			temz = j;
			temy = get_ground_height(temx, temz);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(temx, temy, temz);
		}
	glEnd();
	glDisable(GL_TEXTURE_2D);
//	system("pause");
}

void draw_wall()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	{
		for (int i = 0; i < MAPSIZE; i += WALLSTEP) {
			glTexCoord2f(0.0f, 0.0f); glVertex3f(i, 0, 0);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(i + WALLSTEP, 0, 0);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(i + WALLSTEP, WALLSTEP, 0);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(i, WALLSTEP, 0);
		}
		for (int i = 0; i < MAPSIZE; i += WALLSTEP) {
			glTexCoord2f(0.0f, 0.0f); glVertex3f(MAPSIZE, 0, i);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(MAPSIZE, 0, i + WALLSTEP);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(MAPSIZE, WALLSTEP, i + WALLSTEP);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(MAPSIZE, WALLSTEP, i);
		}
		for (int i = 0; i < MAPSIZE; i += WALLSTEP) {
			glTexCoord2f(0.0f, 0.0f); glVertex3f(i + WALLSTEP, 0, MAPSIZE);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(i, 0, MAPSIZE);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(i, WALLSTEP, MAPSIZE);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(i + WALLSTEP, WALLSTEP, MAPSIZE);
		}
		for (int i = 0; i < MAPSIZE; i += WALLSTEP) {
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, i + WALLSTEP);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 0, i);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(0, WALLSTEP, i);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(0, WALLSTEP, i + WALLSTEP);
		}
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void draw_sky()
{
	glColor3f(0.3f, 0.6f, 0.9f);
	glPushMatrix();
	glTranslatef(64.0f, 0.0f, 64.0f);
	glutSolidSphere(1000.0f, 10, 10);
	glPopMatrix();
}

AUX_RGBImageRec* LoadBMP(char *Filename)
{
	FILE *File = NULL;
	if (!Filename) {
		return NULL;
	}
	File = fopen(Filename, "r");
	if (File) {
		fclose(File);
		return auxDIBImageLoad(Filename);
	}
	return NULL;
}

void load_graphs()
{
	AUX_RGBImageRec* TextureImage[TEXTURE_NUM];
	memset(TextureImage, 0, sizeof(void *));
	if (TextureImage[0] = LoadBMP("Data/grass.bmp")) {
		glGenTextures(1, &texture[0]);
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	if (TextureImage[0]) {
		if (TextureImage[0]->data) {
			free(TextureImage[0]->data);
		}
		free(TextureImage[0]);
	}


	if (TextureImage[1] = LoadBMP("Data/wall.bmp")) {
		glGenTextures(1, &texture[1]);
		glBindTexture(GL_TEXTURE_2D, texture[1]);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[1]->sizeX, TextureImage[1]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[1]->data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	if (TextureImage[1]) {
		if (TextureImage[1]->data) {
			free(TextureImage[1]->data);
		}
		free(TextureImage[1]);
	}

	if (TextureImage[2] = LoadBMP("Data/snow.bmp")) {
		glGenTextures(1, &texture[2]);
		glBindTexture(GL_TEXTURE_2D, texture[2]);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[2]->sizeX, TextureImage[2]->sizeY, 0, GL_RGBA, GL_UNSIGNED_BYTE, TextureImage[2]->data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	if (TextureImage[2]) {
		if (TextureImage[2]->data) {
			free(TextureImage[2]->data);
		}
		free(TextureImage[2]);
	}

}

void initBackground()
{
	load_height_graph();
	load_graphs();
}

void drawBackground()
{
	draw_ground();
	draw_wall();
	draw_sky();
}
