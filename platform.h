#ifndef _PLATFORM_H_
#define _PLATFORM_H_

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


#endif // !_PLATFORM_H_