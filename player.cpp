#include "player.h"
Player::Player(){
	current_animation = &animation_idle_right;
}
void Player::on_update(int delta) {
	int derection = is_right_key_down - is_left_key_down;
	if (derection != 0) {//假如按了左右键
		is_facing_right=derection>0;
		current_animation=is_facing_right?&animation_run_right :&animation_run_left;
		float distance = derection * delta * run_velocity;
		on_run(distance);
	}
	else {//假如没按左右键,或者按了左右键但是没有移动
		current_animation = is_facing_right ? &animation_idle_right : &animation_idle_left;
	}
	current_animation->on_update(delta);
	move_and_collide(delta);
}
void Player::on_draw(const Camera& camera) {
	current_animation->on_draw(camera,(int)position.x, (int)position.y);
}
void Player::on_input(const ExMessage& msg) {
	switch (msg.message) {
		case WM_KEYDOWN:
			switch (id) {
				case PlayerID::P1:
					switch (msg.vkcode) {
						case 0x41: // A
							is_left_key_down=true;
							break;
						case 0x44: // D
							is_right_key_down=true;
							break;
						case 0x57:// W
							on_jump();
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
	position.x += distance;
}

void Player::on_jump(){
	if (velocity.y !=0) return;//只有下降速度为0时才可以跳,也即只能在平台上才能跳
	velocity.y += jump_velocity;
}

void Player::set_id(PlayerID id) {
	this->id = id; 
}

void Player::set_position(float x, float y)
{
	position.x = x;
	position.y = y;
}

void Player::move_and_collide(int delta) {
	velocity.y += gravity * delta;
	position += velocity * (float)delta;
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
					break;
				}
			}
		}
	}
}
