#ifndef __PARTICLE_H__
#define __PARTICLE_H__
#include "util.h"
#include "atlas.h"
#include "vector2.h"
class Particle
{
public:
	Particle() = default;
	Particle(const Vector2& position, Atlas* atlas, int lifespan);
	~Particle()=default;

	void set_atlas(Atlas* new_atlas);
	void set_position(const Vector2& new_position);
	void set_lifespan(int ms);
	bool check_valid() const;
	void on_update(int delta);
	void on_draw(const Camera& camera) const;

private:
	int timer = 0;//粒子动画播放定时器
	int lifespan = 0;//电话持续时长
	int idx_frame = 0;//当前播放的帧
	Vector2 position;//粒子世界坐标位置
	bool valid = true;//粒子对象是否有效
	Atlas* atlas = nullptr;//粒子动画使用的图集
};


#endif // !__PARTICLE_H__