#include "Keyboard.h"
bool CreatFlower = false;
bool CreatTree = false;
void initKeyboard()
{
	glutKeyboardFunc(&getKeyboardPress);
	glutSpecialFunc(&getSpecialKeyPress);
}


void getKeyboardPress(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(0);
	case 'w':
		walk_up();
		break;
	case 's':
		walk_down();
		break;
	case 'a':
		//cout << "a";
		walk_left();
		break;
	case 'd':
		walk_right();
		break;
	case 'q':
		turn_left();
		break;
	case 'e':
		turn_right();
		break;
	case 'f':
		if ((CreatFlower == false) && (CreatTree == false))
		{
			Flower* tem = new Flower;
			int temx, temy, temz;
			get_Groung_position(mouse_x, mouse_y, temx, temy, temz);
			tem->setPosition(temx, temz);
			tem->setAlpha(0.35f);
			flower_display_list.push_back(tem);
			CreatFlower = true;
		}
		coutstat();
		break;
	case 't':
		if ((CreatFlower == false) && (CreatTree == false))
		{
			Tree* tem = new Tree;
			int temx, temy, temz;
			get_Groung_position(mouse_x, mouse_y, temx, temy, temz);
			tem->setPosition(temx, temz);
			tree_display_list.push_back(tem);
			CreatTree = true;
		}
		coutstat();
		break;
	case 'z':
		save_all();
		break;
	case 'l':
		load_all();
		break;
	case 'r':
		if (CreatFlower == true)
		{
			flower_display_list[flower_display_list.size() - 1]->change_petal_R(0.1f);
		}
		coutstat();
		break;
	case 'g':
		if (CreatFlower == true)
		{
			flower_display_list[flower_display_list.size() - 1]->change_petal_G(0.1f);
		}
		coutstat();
		break;

	case 'b':
		if (CreatFlower == true)
		{
			flower_display_list[flower_display_list.size() - 1]->change_petal_B(0.1f);
		}
		coutstat();
		break;

	case 'n':
		if (CreatFlower == true)
		{
			flower_display_list[flower_display_list.size() - 1]->change_petal_NUM(1);
		}
		if (CreatTree == true)
		{
			tree_display_list[tree_display_list.size() - 1]->change_tree_level(1);
		}
		coutstat();
		break;

	case 'm':
		if (CreatFlower == true)
		{
			flower_display_list[flower_display_list.size() - 1]->change_petal_NUM(-1);
		}
		if (CreatTree == true)
		{
			tree_display_list[tree_display_list.size() - 1]->change_tree_level(-1);
		}
		coutstat();
		break;

	case 'p':
		is_snow = 1 - is_snow;
		snowcount = 0;
		coutstat();
		break;

	case 'o':
		if (have_wind) stop_wind();
		else start_wind();
		coutstat();
		break;

	case 'i':
		snow_down();
		break;

	case 'j':
		change_snow_level(-5);
		coutstat();
		break;

	case 'k':
		change_snow_level(5);
		coutstat();
		break;
	}

	

}

void getSpecialKeyPress(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		walk_up();
		break;
	case GLUT_KEY_DOWN:
		walk_down();
		break;
	case GLUT_KEY_LEFT:
		walk_left();
		break;
	case GLUT_KEY_RIGHT:
		walk_right();
		break;
	}
}