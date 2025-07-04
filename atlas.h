#pragma once
#include <vector>
#include <graphics.h>
class Atlas//¹ÜÀíÍ¼Æ¬µÄ
{
public:
	Atlas()=default;
	~Atlas()=default;

	void load_from_file(LPCTSTR path_template,int num);
	void clear();
	int get_size();
	IMAGE* get_image(int index);
	void add_image(const IMAGE& img);

private:
	std::vector<IMAGE> img_list;
};

