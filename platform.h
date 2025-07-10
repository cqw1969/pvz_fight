#pragma once
#include "util.h"
#include "camera.h"

extern bool is_debug;

class Platform
{
public:
	struct CollisionShape {
		float y,left,right;
	};

	CollisionShape shape;
	IMAGE* img=nullptr;
	POINT render_position = { 0 };

	Platform()=default;
	~Platform()=default;

	void on_draw(const Camera& camera) const;
};

