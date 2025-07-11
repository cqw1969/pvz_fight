#pragma once
#include "camera.h"
#include "vector2.h"
#include "animation.h"
#include "player_id.h"
#include "platform.h"
#include <graphics.h>

extern std::vector<Platform> platform_list;

class Player
{
public:
	Player();
	~Player()=default;

	virtual void on_update(int delta);
	virtual void on_draw(const Camera& camera);
	virtual void on_input(const ExMessage& msg);
	virtual void on_run(float distance);
	virtual void on_jump();
	void set_id(PlayerID id);
	void set_position(float x, float y);

protected://��ֹ�޷��������µ�animation����

	void move_and_collide(int delta);

	const float gravity = 1.6e-3f;//�������ٶ�(1.6*(e-3))
	const float run_velocity = 0.55f;//�����ٶ�
	const float jump_velocity = -0.85f;//��Ծ�ٶ�

	Vector2 size;//��Ҵ�С(����������ײ��)
	Vector2 position;
	Vector2 velocity;//�����ٶ�

	Animation animation_idle_left;
	Animation animation_idle_right;
	Animation animation_run_left;
	Animation animation_run_right;

	Animation* current_animation = nullptr;//��ǰ���ŵĶ���

	PlayerID id=PlayerID::P1;

	bool is_left_key_down = false;
	bool is_right_key_down = false;

	bool is_facing_right = true;
};

