#ifndef _PEASHOOTER_PLAYER_H_
#define _PEASHOOTER_PLAYER_H_

#include "player.h"
#include "pea_bullet.h"
extern Atlas atlas_peashooter_idle_left;
extern Atlas atlas_peashooter_idle_right;
extern Atlas atlas_peashooter_run_left;
extern Atlas atlas_peashooter_run_right;
extern Atlas atlas_peashooter_attack_ex_left;
extern Atlas atlas_peashooter_attack_ex_right;
extern Atlas atlas_peashooter_die_left;
extern Atlas atlas_peashooter_die_right;

class PeashooterPlayer:public Player
{
public:
	PeashooterPlayer(bool facing_right);
	~PeashooterPlayer()=default;

	void on_update(int delta) override;
	void on_attack() override;
	void on_attack_ex() override;

private:
	void spawn_pea_bullet(float speed);//在场景中生成一个豌豆子弹

	const float speed_pea = 0.75f;//豌豆子弹速度
	const float speed_pea_ex = 1.5f;//豌豆子弹速度（特殊）
	const int attack_ex_duration = 2500;//特殊攻击持续时间

	Timer timer_attack_ex;//特殊攻击状态定时器(持续时间)
	Timer timer_spawn_pea_ex;//豌豆子弹发射定时器(持续时间内的攻击间隔)
};


#endif // !_PEASHOOTER_PLAYER_H_