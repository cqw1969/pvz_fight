#pragma once
#include "timer.h"
#include "vector2.h"
class Camera
{
public:
	Camera();
	~Camera() = default;

	const Vector2& get_position() const;
	void reset();
	void on_update(int delta);
	void shake(float strength, float duration);

private:
	Vector2 position;
	Timer timer_shake;
	bool is_shaking = false;
	float shaking_strength = 0.0f;
};

