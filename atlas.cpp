#include "atlas.h"

void Atlas::load_from_file(LPCTSTR path_template, int num)
{
	img_list.clear();
	img_list.resize(num);
	TCHAR path_file[256];
	for (int i = 0; i < num; i++)
	{
		_stprintf_s(path_file, path_template, i + 1);
		loadimage(&img_list[i],path_file);
	}
}

void Atlas::clear()
{
	img_list.clear();
}

int Atlas::get_size()
{
	return (int)img_list.size();
}

IMAGE* Atlas::get_image(int index)
{
	if (index < 0 || index >= img_list.size())
		return nullptr;
	return &img_list[index];
}

void Atlas::add_image(const IMAGE& img)
{
	img_list.push_back(img);
}
