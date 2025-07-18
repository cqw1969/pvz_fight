#pragma once
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
	Animation animation_break; //Íã¶¹×Óµ¯ÆÆËé¶¯»­
};

