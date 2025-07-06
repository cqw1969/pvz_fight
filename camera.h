#pragma once
#include "vector2.h"
class Camera
{
public:
	Camera() = default;
	~Camera() = default;

	const Vector2& get_position() const;
	void reset();
	void on_update(int delta);

private:
	Vector2 position;
};

