#ifndef _PEA_BULLET_H_
#define _PEA_BULLET_H_

#include "bullet.h"
#include "animation.h"

extern IMAGE img_pea;
extern Atlas atlas_pea_break;

class PeaBullet :public Bullet
{
public:
	PeaBullet() ;
	~PeaBullet() = default;

	void on_collide() override;
	void on_update(int delta) override;
	void on_draw(const Camera& camera) const override;

private:
	Animation animation_break; //豌豆子弹破碎动画
};


#endif // !_PEA_BULLET_H_