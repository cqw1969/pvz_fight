#include "camera.h"

const Vector2& Camera::get_position() const
{
    return position;
}

void Camera::reset() {
    //position = Vector2(0, 0);
    position.x = 0;
    position.y = 0;
}

void Camera::on_update(int delta)
{
    const Vector2 speed = { -0.35f,0 };
    position += speed * (float)delta;
}
