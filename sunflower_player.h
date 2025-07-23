#ifndef __SUNFLOWER_PLAYER_H__
#define __SUNFLOWER_PLAYER_H__

#include "player.h"
#include "sun_bullet.h"
#include "sun_bullet_ex.h"

extern Atlas atlas_sunflower_idle_left;
extern Atlas atlas_sunflower_idle_right;
extern Atlas atlas_sunflower_run_left;
extern Atlas atlas_sunflower_run_right;
extern Atlas atlas_sunflower_attack_ex_left;
extern Atlas atlas_sunflower_attack_ex_right;
extern Atlas atlas_sun_text;
extern Atlas atlas_sunflower_die_left;
extern Atlas atlas_sunflower_die_right;

extern Player* player_1;
extern Player* player_2;

class SunflowerPlayer : public Player
{
public:
	SunflowerPlayer(bool facing_right);
	~SunflowerPlayer()=default;
	void on_update(int delta) override;
	void on_draw(const Camera& camera) override;
	void on_attack() override;
	void on_attack_ex() override;


private:
	const float speed_sun_ex = 0.15f;//大型日光弹的下落速度
	const Vector2 velocity_sun = { 0.25f,-0.5f };//小型日光炸弹抛射速度

	Animation animation_sun_text;
	bool is_sun_text_visible = false;
};


#endif // !__SUNFLOWER_PLAYER_H__