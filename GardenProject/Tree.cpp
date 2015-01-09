#include "Tree.h"
vector<Tree*> tree_display_list;

Tree::Tree()
{
	// initialise geometry parameters
	nSlices = 24;
	nStacks = 1;
	nLevels = 5;
	trunkRadius = 0.4;
	trunkHeight = 18;
	treeRadius = 4;
	// initialise material parameters
	mat_trunk[0] = 0.5f;
	mat_trunk[1] = 0.3f;
	mat_trunk[2] = 0.1f;
	mat_trunk[3] = 1;
	mat_tree[0] = 0.3f;
	mat_tree[1] = 0.55f;
	mat_tree[2] = 0.35f;
	mat_tree[3] = 1;
}

void Tree::draw()
{
	GLfloat baseheight = get_ground_height(x, z) - 1;

	glPushMatrix();
	glTranslatef(x, baseheight, z);
	glRotatef(-90, 1, 0, 0);

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_trunk);
	glutSolidCone(trunkRadius, trunkHeight, nSlices, nStacks);

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_tree);
	glTranslatef(0, 0, trunkHeight / (GLfloat)(nLevels + 2));
	for (int l = 1; l <= nLevels; l++)
	{
		glTranslatef(0, 0, trunkHeight / (GLfloat)(nLevels + 2));
		glutSolidCone(treeRadius*(nLevels + 1 - l) / (GLfloat)(nLevels + 1), trunkHeight / (GLfloat)(nLevels + 1), nSlices, nStacks);
	}
	glPopMatrix();

	GLfloat blank[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blank);

}

void Tree::change_tree_level(int value)
{
	nLevels += value;
	if (nLevels > 20) nLevels = 20;
	if (nLevels < 5) nLevels = 5;
}

