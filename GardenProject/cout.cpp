#include "cout.h"

void coutline()
{
	cout << "-----------------------------------------------------------------" << endl;
}

void coutstat()
{
	system("cls");
	cout << "欢迎来到MyGarden，作者5120379068" << endl;
	cout << "系统状态：" << endl;
	cout << "  花的数量：" << flower_display_list.size() << "\t\t";
	cout << "  树的数量：" << tree_display_list.size() << endl;
	cout << "  下雪效果：" << (is_snow ? "是" : "否") << "\t\t";
	cout << "  雪量大小：" << snowlevel << endl;
	cout << "  风场效果：" << (have_wind ? "是" : "否") << endl;
	coutline();
	cout << "操作提示：" << endl;
	cout << "【鼠标右键】按下后可旋转视角" << "\t";
	cout << "【鼠标左键】按下后可对地形做修改" << endl;
	cout << "【W,上方向键】向前行走" << "\t\t";
	cout << "【A,左方向键】向左行走" << endl;
	cout << "【S,下方向键】向后行走" << "\t\t";
	cout << "【D,右方向键】向右行走" << endl;
	cout << "【Q】向左旋转" << "\t\t\t";
	cout << "【E】向右旋转" << endl;
	cout << "【P】控制下雪特效" << "\t\t";
	cout << "【O】控制风场特效" << endl;
	cout << "【J】减小雪量" << "\t\t\t";
	cout << "【K】增大雪量" << endl;
	cout << "【Z】保存当前状态" << "\t\t";
	cout << "【L】读取已保存的状态" << endl;
	cout << "【I】雪崩塌效果" << "\t\t\t";
	cout << "【ESC】退出" << endl;
	if (CreatFlower == true)
	{
		coutline();
		cout << "当前为创建花朵状态" << endl;
		cout << "  花瓣数量：" << flower_display_list[flower_display_list.size() - 1]->petalNum << endl;
		cout << "  颜色：R(" << flower_display_list[flower_display_list.size() - 1]->mat_petal[0] << ")  G("
			<< flower_display_list[flower_display_list.size() - 1]->mat_petal[1] << ")  B("
			<< flower_display_list[flower_display_list.size() - 1]->mat_petal[2] << ")" << endl;
		cout << "【R,G,B】修改花瓣的RGB值" << endl;
		cout << "【N】增加花瓣数量" << endl;
		cout << "【M】减少花瓣数量" << endl;
		cout << "【鼠标单击】确认创建花朵" << endl;
	}
	else if (CreatTree == true)
	{
		coutline();
		cout << "当前为创建树状态" << endl;
		cout << "  树的层数：" << tree_display_list[tree_display_list.size() - 1]->nLevels << endl;
		cout << "【N】增加树的层数" << endl;
		cout << "【M】减少树的层数" << endl;
		cout << "【鼠标单击】确认创建树" << endl;
	}
	else
	{
		cout << "【F】创建一朵花" << "\t\t\t";
		cout << "【T】创建一棵树" << endl;
	}
}