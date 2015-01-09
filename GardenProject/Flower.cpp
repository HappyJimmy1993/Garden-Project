#include "Flower.h"
const GLfloat Pi = 3.1415926536f;
vector<Flower*> flower_display_list;

void Flower::setAlpha(GLfloat alpha)
{
	mat_stem[3] = alpha;
	mat_blossom[3] = alpha;
	mat_petal[3] = alpha;
}

void Flower::change_petal_R(GLfloat value)
{
	mat_petal[0] = GLfloat(int((mat_petal[0] + value) * 10) % 11) / 10;
}
void Flower::change_petal_G(GLfloat value)
{
	mat_petal[1] = GLfloat(int((mat_petal[1] + value) * 10) % 11) / 10;
}
void Flower::change_petal_B(GLfloat value)
{
	mat_petal[2] = GLfloat(int((mat_petal[2] + value) * 10) % 11) / 10;
}
void Flower::change_petal_NUM(int value)
{
	petalNum += value;
	if (petalNum > 50) petalNum = 50;
	if (petalNum < 15) petalNum = 15;
}

Flower::Flower()
{
	nSlices = 64;
	nStacks = 64;
	stemRadius = 0.5;
	stemHeight = (GLfloat)5;
	blossomRadius = stemHeight / 10;
	petalLength = 4 * blossomRadius;
	petalNum = 30;

	mat_stem[0] = 0.2f;
	mat_stem[1] = 0.5f;
	mat_stem[2] = 0.1f;
	mat_stem[3] = 1;
	mat_blossom[0] = 0.7f;
	mat_blossom[1] = 0.65f;
	mat_blossom[2] = 0.15f;
	mat_blossom[3] = 1;
	mat_petal[0] = 0.65f;
	mat_petal[1] = 0.25f;
	mat_petal[2] = 0.15f;
	mat_petal[3] = 1;
}

void Flower::draw()
{
	GLfloat baseheight = get_ground_height(x, z) - 1;
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_NORMALIZE);
	//花干
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_stem);
	glPushMatrix();
	glTranslatef(x, baseheight, z);	
	glRotatef(-90, 1, 0, 0);
	glutSolidCone(stemRadius, stemHeight, nSlices, nStacks);
	glPopMatrix();

	//花托
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_blossom);
	glPushMatrix();
	glTranslatef(x, stemHeight + baseheight, z);
	glScalef(blossomRadius, blossomRadius*0.5, blossomRadius);
	glutSolidSphere(1, nSlices, nStacks);
	glPopMatrix();

	//花瓣
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_petal);

	double h, phi = 0;
	for (int k = 1; k <= petalNum; ++k)
	{
		glPushMatrix();
		h = -1.0 + 0.5*k / petalNum;
		//h = -0.8;
		phi = phi + 3.6 / sqrt((double)petalNum)*(1.0 / sqrt((double)1 - pow(h, 2.0)));
		phi = fmod((double)phi, (double)(2 * Pi));
		glTranslated(x, stemHeight + baseheight, z);
		glRotatef(270, 1, 0, 0);
		glRotatef(-90, 0, 1, 0);
		glRotatef(phi / (2.0*Pi)*360.0f, 1, 0, 0);
		glRotatef(acos(h) / (2.0*Pi)*360.0f, 0, 1, 0);
		glTranslatef(0, 0, petalLength / 2);
		glScalef(0.2, 0.5, 1);
		glutSolidSphere(petalLength / 2, nSlices, nStacks);
		glPopMatrix();
	}

	GLfloat blank[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blank);
	glDisable(GL_BLEND);
	glDisable(GL_NORMALIZE);
}
