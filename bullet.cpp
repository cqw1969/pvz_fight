#include "bullet.h"
#include "Particle.h"
void Bullet::set_damage(int val) {
	damage = val;
}
int Bullet::get_damage() {
	return damage;
}
void Bullet::set_position(float x, float y){
	position.x = x;
	position.y = y;
}
void Bullet::set_position(Vector2& pos) {
	position = pos;
}
const Vector2& Bullet::get_position() const {
	return position;
}

const Vector2& Bullet::get_size() const
{
	return size;
}

void Bullet::set_velocity(float x, float y)
{
	velocity.x = x;
	velocity.y = y;
}

void Bullet::set_velocity(Vector2& vel)
{
	velocity = vel;
}

void Bullet::set_collide_target(PlayerID target)
{
	target_id = target;
}

PlayerID Bullet::get_collide_target() const
{
	return target_id;
}

void Bullet::set_callback(std::function<void()> callback) {
	this->callback = callback;
}

void Bullet::set_valid(bool flag)
{
	valid = flag;
}

bool Bullet::get_valid() const
{
	return valid;
}

bool Bullet::check_can_remove() const
{
	return can_remove;
}

void Bullet::on_collide()
{
	if (callback) {
		callback();
	}
}

bool Bullet::check_collision(const Vector2& pos, const Vector2& size)
{
	return this->position.x + this->size.x / 2 >= pos.x
		&& this->position.x + this->size.x / 2 <= pos.x + size.x
		&& this->position.y + this->size.y / 2 >= pos.y
		&& this->position.y + this->size.y / 2 <= pos.y + size.y;
}

void Bullet::on_update(int delta){}
void Bullet::on_draw(const Camera& camera) const{
	if (is_debug) {
		setfillcolor(RGB(255, 255, 255));
		setlinecolor(RGB(255, 255, 255));
		rectangle((int)position.x, (int)position.y, (int)(position.x + size.x), (int)(position.y + size.y));
		solidcircle((int)(position.x + size.x / 2), (int)(position.y + size.y / 2), 5);
	}
}

bool Bullet::check_if_exceeds_screen()
{
	return (position.x + size.x <= 0 || position.x >= getwidth()
		|| position.y + size.y <= 0 || position.y >= getheight());
}
