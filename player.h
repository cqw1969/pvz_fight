#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "camera.h"
#include "vector2.h"
#include "animation.h"
#include "player_id.h"
#include "bullet.h"
#include "platform.h"
#include "particle.h"
#include <graphics.h>

extern bool is_debug;

extern IMAGE img_1P_cursor;
extern IMAGE img_2P_cursor;

extern Atlas atlas_run_effect;
extern Atlas atlas_jump_effect;
extern Atlas atlas_land_effect;

extern Camera main_camera;

extern std::vector<Bullet*> bullet_list;
extern std::vector<Platform> platform_list;
class Player
{
public:
	Player(bool facing_right);
	~Player()=default;

	virtual void on_update(int delta);
	virtual void on_draw(const Camera& camera);
	virtual void on_input(const ExMessage& msg);
	virtual void on_run(float distance);
	virtual void on_jump();
	virtual void on_land();
	void set_id(PlayerID id);
	void set_position(float x, float y);
	const Vector2& get_position() const;
	const Vector2& get_size() const;
	void make_invulnerable();
	int get_hp() const;
	int get_mp() const;
	void set_hp(int val);

	virtual void on_attack();
	virtual void on_attack_ex();

protected://��ֹ�޷��������µ�animation����
	void move_and_collide(int delta);

	const float gravity = 1.6e-3f;//�������ٶ�(1.6*(e-3))
	const float run_velocity = 0.55f;//�����ٶ�
	const float jump_velocity = -0.85f;//��Ծ�ٶ�

	int mp = 0;//��ҵ�����ֵ
	int hp = 100;//��ҵ�����ֵ

	Vector2 size;//��Ҵ�С(����������ײ��)
	Vector2 position;
	Vector2 velocity;//�����ٶ�

	Animation animation_idle_left;
	Animation animation_idle_right;
	Animation animation_run_left;
	Animation animation_run_right;
	Animation animation_attack_ex_left;
	Animation animation_attack_ex_right;
	Animation animation_jump_effect;//��Ծ��Ч
	Animation animation_land_effect;//��½��Ч
	Animation animation_die_left;
	Animation animation_die_right;

	bool is_jump_effect_visible = false;//��Ծ��Ч�Ƿ�ɼ�
	bool is_land_effect_visible = false;//��½��Ч�Ƿ�ɼ�

	Vector2 position_jump_effect;//��Ծ��Чλ��
	Vector2 position_land_effect;//��½��Чλ��

	Animation* current_animation = nullptr;//��ǰ���ŵĶ���

	PlayerID id=PlayerID::P1;

	bool is_left_key_down = false;
	bool is_right_key_down = false;

	bool is_facing_right = true;

	int attack_cd = 500;
	bool can_attack = true;
	Timer timer_attack_cd;

	bool is_attacking_ex=false;//�Ƿ��ڳ�������״̬

	IMAGE img_sketch;//��Ӱ֡ͼƬ
	bool is_invulnerable = false;//�Ƿ��޵�
	bool is_show_sketch_frame = false;//�Ƿ���ʾ��Ӱ֡
	Timer timer_invulnerable;//�޵м�ʱ��
	Timer timer_invulnerable_blink;//��Ӱ֡��ʱ��

	std::vector<Particle> particle_list;//��Ч�����б�

	Timer timer_run_effect_generation;//������Ч���ӷ��䶨ʱ��
	Timer timer_die_effect_generation;//������Ч���ӷ��䶨ʱ��

	bool is_cursor_visible = true;//�Ƿ���ʾ���
	Timer timer_cursor_visibility;//�����ʾ��ʱ��

	Vector2 last_hunt_direction;//���һ���ܻ�����
};


#endif // !_PLAYER_H_