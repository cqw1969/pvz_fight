#include "platform.h"

void Platform::on_draw(const Camera& camera) const
{
	Util::putimage_alpha(camera,render_position.x,render_position.y,img);

	if (is_debug) {
		setlinecolor(RGB(255, 0, 0));
		Util::line(camera, (int)shape.left, (int)shape.y, (int)shape.right, (int)shape.y);
	}
}
