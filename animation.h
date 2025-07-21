#ifndef _ANIMATION_H
#define _ANIMATION_H

#include "util.h"
#include "atlas.h"
#include "camera.h"

#include <functional>
#include <graphics.h>

class Animation
{
public:
	Animation()=default;
	~Animation()=default;

	void reset();
	void set_atlas(Atlas* new_atlas);
	void set_loop(bool flag);
	void set_interval(int ms);
	int get_idx_frame();
	IMAGE* get_frame();
	bool check_finished();
	void on_update(int delta);
	void on_draw(const Camera& camera, int x, int y) const;
	void set_callback(std::function<void()> callback);
private:
	int timer=0;					//��ʱ��
	int interval=0;				//֡���
	int idx_frame=0;			//֡����
	bool is_loop=true;		//�Ƿ�ѭ������
	Atlas* atlas=nullptr;
	std::function<void()> callback;
};


#endif // !_ANIMATION_H