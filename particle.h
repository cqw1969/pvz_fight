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
	int timer = 0;//���Ӷ������Ŷ�ʱ��
	int lifespan = 0;//�绰����ʱ��
	int idx_frame = 0;//��ǰ���ŵ�֡
	Vector2 position;//������������λ��
	bool valid = true;//���Ӷ����Ƿ���Ч
	Atlas* atlas = nullptr;//���Ӷ���ʹ�õ�ͼ��
};


#endif // !__PARTICLE_H__