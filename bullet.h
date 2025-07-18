#pragma once
#include "vector2.h"
#include "player_id.h"
#include "camera.h"
#include <functional>
#include <graphics.h>
class Bullet
{
public:
	Bullet()=default;
	~Bullet()=default;

	void set_damage(int val);
	int get_damage();
	void set_position(float x, float y);
	void set_position(Vector2& position);
	const Vector2& get_position() const;
	const Vector2& get_size() const;
	void set_velocity(float x, float y);
	void set_velocity(Vector2& vel);
	void set_collide_target(PlayerID target);
	PlayerID get_collide_target() const;
	void set_callback(std::function<void()> callback);
	void set_valid(bool flag);
	bool get_valid() const;
	bool check_can_remove() const;

	virtual void on_collide();
	virtual bool check_collision(const Vector2& pos, const Vector2& size);
	virtual void on_update(int delta);
	virtual void on_draw(const Camera& camera) const;

protected://ȷ��������Է��ʻ���ĳ�Ա
	bool check_if_exceeds_screen();

	Vector2 size;
	Vector2 position;
	Vector2 velocity;
	int damage = 10;
	bool valid = true;							//�ӵ��Ƿ���Ч
	bool can_remove = false;			//�ӵ��Ƿ���Ա�ɾ��
	std::function<void()> callback;	//�ӵ���ײʱ�Ļص�����
	PlayerID target_id=PlayerID::P1;	//�ӵ���Ŀ�����
};

