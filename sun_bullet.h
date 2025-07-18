#pragma once
#include "bullet.h"
#include "animation.h"

extern Atlas atlas_sun;
extern Atlas atlas_sun_explode;
extern Camera main_camera;

class SunBullet :public Bullet
{
public:
	SunBullet();
	~SunBullet() = default;

	void on_collide() override;
	void on_update(int delta) override;
	void on_draw(const Camera& camera) const override;

private:
	const float gravity = 1e-3f;

	Animation animation_idle;				//�չ�ը��Ĭ�϶���
	Animation animation_explode;		//�չ�ը����ը����
	Vector2 explode_render_offset;		//��ըʱ����Ⱦƫ��
};

