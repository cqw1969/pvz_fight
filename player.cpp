#include "player.h"
Player::Player(){
	current_animation = &animation_idle_right;
}
void Player::on_update(int delta) {
	int derection = is_right_key_down - is_left_key_down;
	if (derection != 0) {//���簴�����Ҽ�
		is_facing_right=derection>0;
		current_animation=is_facing_right?&animation_run_right :&animation_run_left;
		float distance = derection * delta * run_velocity;
		on_run(distance);
	}
	else {//����û�����Ҽ�,���߰������Ҽ�����û���ƶ�
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
	if (velocity.y !=0) return;//ֻ���½��ٶ�Ϊ0ʱ�ſ�����,Ҳ��ֻ����ƽ̨�ϲ�����
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
	if (velocity.y > 0) {//��������
		for (const Platform& platfrom : platform_list) {
			const Platform::CollisionShape& shape = platfrom.shape;
			bool is_collide_x = (max(position.x + size.x, shape.right) - min(position.x, shape.left))
				<= size.x + (shape.right - shape.left);//Xmax-Xmin<=���ο��(�����ײ��)+�߶γ���(ƽ̨�ж���)  �ж�ˮƽ�������Ƿ��غ�  
			//��λ����ƽ̨��������ײ��(position.y + size.y)����ƽ̨ʱ ƽ̨�ߵ�Y����λ����Ҿ����ڲ�����ҵ�ǰ֡��Y�����ڣ�
			bool is_collide_y = (shape.y >= position.y && shape.y <= position.y + size.y);
			if (is_collide_x && is_collide_y) {//�����غ�  ��һ֡��λ����ƽ̨������ײ�䴩��ƽ̨
				float delta_pos_y = velocity.y * delta;//�����������(�Ѿ�������λ��)  �����п����Ǹ�ֵ
				float last_tick_foot_pos_y = position.y + size.y - delta_pos_y;//������һ֡�ŵ�λ��  ������ҡ������
				if (last_tick_foot_pos_y <= shape.y) {//������һ֡�ŵ�λ����ƽ̨��
					position.y = shape.y - size.y;//����λ��
					velocity.y = 0;//�����ٶ�
					break;
				}
			}
		}
	}
}
