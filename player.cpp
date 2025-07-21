#include "player.h"
Player::Player(bool facing_right= true):is_facing_right (facing_right){
	current_animation = is_facing_right ? &animation_idle_right : &animation_idle_left;

	timer_attack_cd.set_wait_time(attack_cd);
	timer_attack_cd.set_one_shot(true);
	timer_attack_cd.set_callback([&]() {
		can_attack = true;
		});

	timer_invulnerable.set_wait_time(750);
	timer_invulnerable.set_one_shot(true);
	timer_invulnerable.set_callback([&]() {
		is_invulnerable = false;
		});

	timer_invulnerable_blink.set_wait_time(75);
	timer_invulnerable_blink.set_callback([&]() {
		is_show_sketch_frame = !is_show_sketch_frame;
		});

	timer_run_effect_generation.set_wait_time(75);
	timer_run_effect_generation.set_callback([&]() {
		Vector2 particle_position;
		IMAGE* frame = atlas_run_effect.get_image(0);
		particle_position.x = position.x + (size.x - frame->getwidth()) / 2;
		particle_position.y = position.y + size.y - frame->getheight();
		particle_list.emplace_back(particle_position, &atlas_run_effect, 45);
		});
	timer_die_effect_generation.set_wait_time(35);
	timer_die_effect_generation.set_callback([&]() {
		Vector2 particle_position;
		IMAGE* frame = atlas_run_effect.get_image(0);
		particle_position.x = position.x + (size.x - frame->getwidth()) / 2;
		particle_position.y = position.y + size.y - frame->getheight();
		particle_list.emplace_back(particle_position, &atlas_run_effect, 150);
		});

	animation_jump_effect.set_atlas(&atlas_jump_effect);
	animation_jump_effect.set_interval(25);
	animation_jump_effect.set_loop(false);
	animation_jump_effect.set_callback([&](){
		is_jump_effect_visible = false;
		});

	animation_land_effect.set_atlas(&atlas_land_effect);
	animation_land_effect.set_interval(50);
	animation_land_effect.set_loop(false);
	animation_land_effect.set_callback([&]() {
		is_land_effect_visible = false;
		});

	timer_cursor_visibility.set_wait_time(2500);
	timer_cursor_visibility.set_one_shot(true);
	timer_cursor_visibility.set_callback([&]() {
		is_cursor_visible = false;
		});
}

void Player::on_update(int delta) {
	int derection = is_right_key_down - is_left_key_down;
	if (derection != 0) {//假如按了左右键
		if(!is_attacking_ex)
			is_facing_right=derection>0;
			current_animation=is_facing_right?&animation_run_right :&animation_run_left;
		float distance = derection * delta * run_velocity;
		on_run(distance);
	}
	else {//假如没按左右键,或者按了左右键但是没有移动
			current_animation = is_facing_right ? &animation_idle_right : &animation_idle_left;
			timer_run_effect_generation.pause();
	}

	if (is_attacking_ex) 
		current_animation = is_facing_right ? &animation_attack_ex_right : &animation_attack_ex_left;

	if (hp <= 0)
		current_animation = last_hunt_direction.x < 0 ? &animation_die_left : &animation_die_right;

	current_animation->on_update(delta);
	animation_jump_effect.on_update(delta);
	animation_land_effect.on_update(delta);

	timer_attack_cd.on_update(delta);
	timer_invulnerable.on_update(delta);
	timer_invulnerable_blink.on_update(delta);
	timer_run_effect_generation.on_update(delta);
	timer_cursor_visibility.on_update(delta);

	if(hp<=0)
		timer_die_effect_generation.on_update(delta);

	particle_list.erase(std::remove_if(
		particle_list.begin(), particle_list.end(),
		[](const Particle& particle) {
			return !particle.check_valid();
		}), particle_list.end());
	for (Particle& particle : particle_list) {
		particle.on_update(delta);
	}

	if (is_show_sketch_frame)
		Util::sketch_image(current_animation->get_frame(), &img_sketch);

	move_and_collide(delta);
}
void Player::on_draw(const Camera& camera) {
	if (is_jump_effect_visible)
		animation_jump_effect.on_draw(camera, (int)position_jump_effect.x, (int)position_jump_effect.y);
	if(is_land_effect_visible)
		animation_land_effect.on_draw(camera, (int)position_land_effect.x, (int)position_land_effect.y);

	for (Particle& particle : particle_list) //为了让粒子不遮挡玩家
		particle.on_draw(camera);

	if (hp > 0 && is_invulnerable && is_show_sketch_frame)
		Util::putimage_alpha(camera, (int)position.x, (int)position.y, &img_sketch);
	else
		current_animation->on_draw(camera,(int)position.x, (int)position.y);

	if (is_cursor_visible) {
		switch (id) {
			case PlayerID::P1:
				Util::putimage_alpha(camera, (int)(position.x + (size.x - img_1P_cursor.getwidth()) / 2),
					(int)(position.y - img_1P_cursor.getheight()), &img_1P_cursor);
				break;
			case PlayerID::P2:
				Util::putimage_alpha(camera, (int)(position.x + (size.x - img_2P_cursor.getwidth()) / 2),
					(int)(position.y - img_2P_cursor.getheight()), &img_2P_cursor);
				break;
		}
	}

	if (is_debug) {
		setlinecolor(RGB(0, 125, 255));
		rectangle((int)position.x, (int)position.y, (int)(position.x + size.x), (int)(position.y + size.y));
	}
}
void Player::on_input(const ExMessage& msg) {
	switch (msg.message) {
		case WM_KEYDOWN:
			switch (id) {
				case PlayerID::P1:
					switch (msg.vkcode) {
					case 0x41: // A
						is_left_key_down = true;
						break;
					case 0x44: // D
						is_right_key_down = true;
						break;
					case 0x57:// W
						on_jump();
						break;
					case 0x46:// F
						if (can_attack) {
							on_attack();
							can_attack = false;
							timer_attack_cd.restart();
						}
						break;
					case 0x47:// G
						if (mp >= 100) {
							on_attack_ex();
							mp = 0;
						}
						break;
					}
					break;
				case PlayerID::P2:
					switch (msg.vkcode) {
						case VK_LEFT:
							is_left_key_down=true;
							break;
						case VK_RIGHT:
							is_right_key_down=true;
							break;
						case VK_UP:
							on_jump();
							break;
						case VK_OEM_PERIOD:// ' . '
							if (can_attack) {
								on_attack();
								can_attack = false;
								timer_attack_cd.restart();
							}
							break;
						case VK_OEM_2:	// ' / '
							if (mp >= 100) {
								on_attack_ex();
								mp = 0;
							}
							break;
					}
					break;
			}
			break;

		case WM_KEYUP:
			switch (id) {
				case PlayerID::P1:
					switch (msg.vkcode) {
						case 0x41: // A
							is_left_key_down = false;
							break;
						case 0x44: // D
							is_right_key_down = false;
							break;
						}
					break;
				case PlayerID::P2:
					switch (msg.vkcode) {
						case VK_LEFT:
							is_left_key_down = false;
							break;
						case VK_RIGHT:
							is_right_key_down = false;
							break;
						}
					break;
				}
			break;
	}
}

void Player::on_run(float distance){
	if(is_attacking_ex)
		return;

	position.x += distance;
	timer_run_effect_generation.resume();
}

void Player::on_jump(){
	if (velocity.y !=0|| is_attacking_ex) return;//只有下降速度为0时才可以跳,也即只能在平台上才能跳且不能在超级攻击中跳
	velocity.y += jump_velocity;

	is_jump_effect_visible = true;
	animation_jump_effect.reset();

	IMAGE* effect_frame = animation_jump_effect.get_frame();
	position_jump_effect.x=position.x + (size.x - effect_frame->getwidth()) / 2;
	position_jump_effect.y=position.y + size.y - effect_frame->getheight();
}

void Player::on_land()
{
	is_land_effect_visible = true;
	animation_land_effect.reset();

	IMAGE* effect_frame = animation_land_effect.get_frame();
	position_land_effect.x = position.x + (size.x - effect_frame->getwidth()) / 2;
	position_land_effect.y = position.y + size.y - effect_frame->getheight();
}

void Player::set_id(PlayerID id) {
	this->id = id; 
}

void Player::set_position(float x, float y)
{
	position.x = x;
	position.y = y;
}

const Vector2& Player::get_position() const {
	return position;
}
const Vector2& Player::get_size() const {
	return size;
}

void Player::make_invulnerable()
{
	is_invulnerable = true;
	timer_invulnerable.restart();
}

int Player::get_hp() const
{
	return hp;
}

int Player::get_mp() const
{
	return mp;
}

void Player::set_hp(int val)
{
	hp = val;
}

void Player::on_attack()
{
}

void Player::on_attack_ex()
{
}

void Player::move_and_collide(int delta) {
	float last_velocity_y=velocity.y;

	velocity.y += gravity * delta;
	position += velocity * (float)delta;

	if (hp <= 0) return;//假如死了就不再进行碰撞检测

	if (velocity.y > 0) {//假如下落
		for (const Platform& platfrom : platform_list) {
			const Platform::CollisionShape& shape = platfrom.shape;
			bool is_collide_x = (max(position.x + size.x, shape.right) - min(position.x, shape.left))
				<= size.x + (shape.right - shape.left);//Xmax-Xmin<=矩形宽度(玩家碰撞箱)+线段长度(平台判断线)  判断水平方向上是否重合  
			//当位置在平台上面且碰撞箱(position.y + size.y)穿过平台时 平台线的Y坐标位于玩家矩形内部（玩家当前帧的Y区间内）
			bool is_collide_y = (shape.y >= position.y && shape.y <= position.y + size.y);
			if (is_collide_x && is_collide_y) {//假如重合  这一帧的位置在平台上且碰撞箱穿过平台
				float delta_pos_y = velocity.y * delta;//计算下落距离(已经发生的位移)  这里有可能是负值
				float last_tick_foot_pos_y = position.y + size.y - delta_pos_y;//计算上一帧脚的位置  考虑玩家↑的情况
				if (last_tick_foot_pos_y <= shape.y) {//假如上一帧脚的位置在平台上
					position.y = shape.y - size.y;//重置位置
					velocity.y = 0;//重置速度

					if(last_velocity_y!=0)//假如上一帧的速度不为0且这一帧速度为0 说明玩家在平台上落地
						on_land();
					break;
				}
			}
		}
	}

	if (!is_invulnerable) {//当不处于无敌状态时才会进行碰撞检测
		for (Bullet* bullet : bullet_list) {
			if (!bullet->get_valid() || bullet->get_collide_target() != id) {//假如子弹无效或者子弹目标不为当前(被攻击)玩家
				continue;
			}

			if (bullet->check_collision(position, size)) {//这里的position就是当前与子弹碰撞的对象的位置,这里的bullet是敌方的子弹
				make_invulnerable();
				bullet->on_collide();
				bullet->set_valid(false);
				hp -= bullet->get_damage();
				last_hunt_direction = bullet->get_position() - position;
				if (hp <= 0) {//飞起来!
					velocity.x = last_hunt_direction.x < 0 ? 0.35f : -0.35f;
					velocity.y = -1.0f;
				}
			}
		}
	}
}
