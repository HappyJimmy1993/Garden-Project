#include "Save.h"

void save_all()
{
	ofstream f1("Data/DataAll.dat");
	f1.close();

	fstream data;
	data.open("Data/DataAll.dat", ios::out | ios::binary | ios::in);
	int flowersize = flower_display_list.size();
	int treesize = tree_display_list.size();
	data.write((char *)&flowersize, sizeof(int));
	data.write((char *)&treesize, sizeof(int));
	for (int i = 0; i < flowersize; ++i)
		data.write((char*)flower_display_list[i], sizeof(Flower));
	for (int i = 0; i < treesize; ++i)
		data.write((char*)tree_display_list[i], sizeof(Tree));
	data.write((char*)height_graph, sizeof(int)* MAPSIZE*MAPSIZE);
			
	data.close();
	MessageBox(NULL, TEXT("保存成功!"), TEXT("提示消息"), MB_OK);
}

void load_all()
{
	fstream data;
	data.open("Data/DataAll.dat", ios::out | ios::binary | ios::in);
	int flowersize ;
	int treesize;
	data.read((char *)&flowersize, sizeof(int));
	data.read((char *)&treesize, sizeof(int));
	flower_display_list.clear();
	for (int i = 0; i < flowersize; ++i)
	{
		Flower *tem = new Flower;
		data.read((char*)tem, sizeof(Flower));
		flower_display_list.push_back(tem);
	}
	tree_display_list.clear();
	for (int i = 0; i < treesize; ++i)
	{
		Tree *tem = new Tree;
		data.read((char*)tem, sizeof(Tree));
		tree_display_list.push_back(tem);
	}
	data.read((char*)height_graph, sizeof(int)* MAPSIZE*MAPSIZE);

	data.close();
	MessageBox(NULL, TEXT("读取成功!"), TEXT("提示消息"), MB_OK);
}