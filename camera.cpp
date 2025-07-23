#include "camera.h"

Camera::Camera()//用以结束摇晃效果
{
    timer_shake.set_one_shot(true);
    timer_shake.set_callback([&]() {//这里的&(引用传递)用来改变定义域外部变量
        is_shaking = false;
        reset();
    });
}

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
    timer_shake.on_update(delta);//时间开始转动
    if (is_shaking) {
        //-50 + rand() % 100                将随机数范围从 0~99 平移为 - 50~49（即 - 50 到 + 49）
        //(-50 + rand() % 100) / 50.0f  将范围从 - 50~49 缩放到 - 1.0 到 0.98（近似 - 1.0~1.0）
        position.x = (-50 + rand() % 100) / 50.0f * shaking_strength;
        position.y = (-50 + rand() % 100) / 50.0f * shaking_strength;
    }
}

void Camera::shake(float strength, float duration)
{
    is_shaking = true;
    shaking_strength = strength;
    timer_shake.set_wait_time(duration);
    timer_shake.restart();
}

