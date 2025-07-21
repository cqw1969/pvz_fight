#ifndef _STATUS_BAR_H_
#define _STATUS_BAR_H_
#include "util.h"

class StatusBar
{
	public:
		StatusBar() = default;
		~StatusBar() = default;
		void set_hp(int val);
		void set_mp(int val);
		void set_position(POINT position);
		void set_position(int x,int y);
		void set_avatar(IMAGE* img);
		void on_draw();
	private:
		const int width = 275;//״̬�����

		int hp = 0;//����
		int mp = 0;//����
		POINT position = { 0 };//λ��
		IMAGE* img_avatar = nullptr;//ͷ��
};


#endif // !_STATUS_BAR_H_