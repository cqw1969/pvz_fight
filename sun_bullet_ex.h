#ifndef _SUN_BULLET_EX_H_
#define _SUN_BULLET_EX_H_

#include "bullet.h"
#include "animation.h"

extern Atlas atlas_sun_ex;
extern Atlas atlas_sun_ex_explode;
extern Camera main_camera;

class SunBulletEx :public Bullet
{
public:
	SunBulletEx();
	~SunBulletEx()=default;

	void on_collide() override;
	void on_update(int delta) override;
	void on_draw(const Camera& camera) const override;
	bool check_collision(const Vector2& pos, const Vector2& size) override;

private:
	Animation animation_idle;				//�޴��չ�ը��Ĭ�϶���
	Animation animation_explode;		//�޴��չ�ը����ը����
	Vector2 explode_render_offset;		//��ըʱ����Ⱦƫ��
};


#endif // !_SUN_BULLET_EX_H_