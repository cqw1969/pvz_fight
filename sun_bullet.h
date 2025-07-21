#ifndef _SUN_BULLET_H_
#define _SUN_BULLET_H_

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

	Animation animation_idle;				//日光炸弹默认动画
	Animation animation_explode;		//日光炸弹爆炸动画
	Vector2 explode_render_offset;		//爆炸时的渲染偏移
};


#endif // !_SUN_BULLET_H_