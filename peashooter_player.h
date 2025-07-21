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
	void spawn_pea_bullet(float speed);//�ڳ���������һ���㶹�ӵ�

	const float speed_pea = 0.75f;//�㶹�ӵ��ٶ�
	const float speed_pea_ex = 1.5f;//�㶹�ӵ��ٶȣ����⣩
	const int attack_ex_duration = 2500;//���⹥������ʱ��

	Timer timer_attack_ex;//���⹥��״̬��ʱ��(����ʱ��)
	Timer timer_spawn_pea_ex;//�㶹�ӵ����䶨ʱ��(����ʱ���ڵĹ������)
};


#endif // !_PEASHOOTER_PLAYER_H_