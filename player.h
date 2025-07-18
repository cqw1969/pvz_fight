#pragma once
#include "camera.h"
#include "vector2.h"
#include "animation.h"
#include "player_id.h"
#include "bullet.h"
#include "platform.h"
#include <graphics.h>

extern std::vector<Bullet*> bullet_list;
extern std::vector<Platform> platform_list;
extern Camera main_camera;

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
	const Vector2& get_position() const;
	const Vector2& get_size() const;

	virtual void on_attack();
	virtual void on_attack_ex();

protected://防止无法访问以下的animation变量
	void move_and_collide(int delta);

	const float gravity = 1.6e-3f;//重力加速度(1.6*(e-3))
	const float run_velocity = 0.55f;//奔跑速度
	const float jump_velocity = -0.85f;//跳跃速度

	int mp = 0;//玩家的能量值
	int hp = 100;//玩家的生命值

	Vector2 size;//玩家大小(用来计算碰撞的)
	Vector2 position;
	Vector2 velocity;//总体速度

	Animation animation_idle_left;
	Animation animation_idle_right;
	Animation animation_run_left;
	Animation animation_run_right;
	Animation animation_attack_ex_left;
	Animation animation_attack_ex_right;

	Animation* current_animation = nullptr;//当前播放的动画

	PlayerID id=PlayerID::P1;

	bool is_left_key_down = false;
	bool is_right_key_down = false;

	bool is_facing_right = true;

	int attack_cd = 500;
	bool can_attack = true;
	Timer timer_attack_cd;

	bool is_attacking_ex=false;//是否处于超级攻击状态
};

