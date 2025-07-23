#ifndef __ATLAS_H__
#define __ATLAS_H__

#include <vector>
#include <graphics.h>
class Atlas//管理图片的
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


#endif // !__ATLAS_H__