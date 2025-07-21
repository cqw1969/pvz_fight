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
	if (derection != 0) {//���簴�����Ҽ�
		if(!is_attacking_ex)
			is_facing_right=derection>0;
			current_animation=is_facing_right?&animation_run_right :&animation_run_left;
		float distance = derection * delta * run_velocity;
		on_run(distance);
	}
	else {//����û�����Ҽ�,���߰������Ҽ�����û���ƶ�
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

	for (Particle& particle : particle_list) //Ϊ�������Ӳ��ڵ����
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
	if (velocity.y !=0|| is_attacking_ex) return;//ֻ���½��ٶ�Ϊ0ʱ�ſ�����,Ҳ��ֻ����ƽ̨�ϲ������Ҳ����ڳ�����������
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

	if (hp <= 0) return;//�������˾Ͳ��ٽ�����ײ���

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

					if(last_velocity_y!=0)//������һ֡���ٶȲ�Ϊ0����һ֡�ٶ�Ϊ0 ˵�������ƽ̨�����
						on_land();
					break;
				}
			}
		}
	}

	if (!is_invulnerable) {//���������޵�״̬ʱ�Ż������ײ���
		for (Bullet* bullet : bullet_list) {
			if (!bullet->get_valid() || bullet->get_collide_target() != id) {//�����ӵ���Ч�����ӵ�Ŀ�겻Ϊ��ǰ(������)���
				continue;
			}

			if (bullet->check_collision(position, size)) {//�����position���ǵ�ǰ���ӵ���ײ�Ķ����λ��,�����bullet�ǵз����ӵ�
				make_invulnerable();
				bullet->on_collide();
				bullet->set_valid(false);
				hp -= bullet->get_damage();
				last_hunt_direction = bullet->get_position() - position;
				if (hp <= 0) {//������!
					velocity.x = last_hunt_direction.x < 0 ? 0.35f : -0.35f;
					velocity.y = -1.0f;
				}
			}
		}
	}
}
