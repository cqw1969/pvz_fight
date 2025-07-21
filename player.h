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
	Animation animation_jump_effect;//跳跃特效
	Animation animation_land_effect;//着陆特效
	Animation animation_die_left;
	Animation animation_die_right;

	bool is_jump_effect_visible = false;//跳跃特效是否可见
	bool is_land_effect_visible = false;//着陆特效是否可见

	Vector2 position_jump_effect;//跳跃特效位置
	Vector2 position_land_effect;//着陆特效位置

	Animation* current_animation = nullptr;//当前播放的动画

	PlayerID id=PlayerID::P1;

	bool is_left_key_down = false;
	bool is_right_key_down = false;

	bool is_facing_right = true;

	int attack_cd = 500;
	bool can_attack = true;
	Timer timer_attack_cd;

	bool is_attacking_ex=false;//是否处于超级攻击状态

	IMAGE img_sketch;//剪影帧图片
	bool is_invulnerable = false;//是否无敌
	bool is_show_sketch_frame = false;//是否显示剪影帧
	Timer timer_invulnerable;//无敌计时器
	Timer timer_invulnerable_blink;//剪影帧计时器

	std::vector<Particle> particle_list;//特效粒子列表

	Timer timer_run_effect_generation;//奔跑特效粒子发射定时器
	Timer timer_die_effect_generation;//死亡特效粒子发射定时器

	bool is_cursor_visible = true;//是否显示光标
	Timer timer_cursor_visibility;//光标显示计时器

	Vector2 last_hunt_direction;//最后一次受击方向
};


#endif // !_PLAYER_H_