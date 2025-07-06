#include "camera.h"

Camera::Camera()//���Խ���ҡ��Ч��
{
    timer_shake.set_one_shot(true);
    timer_shake.set_callback([&]() {//�����&(���ô���)�����ı䶨�����ⲿ����
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
    timer_shake.on_update(delta);//ʱ�俪ʼת��
    if (is_shaking) {
        //-50 + rand() % 100                ���������Χ�� 0~99 ƽ��Ϊ - 50~49���� - 50 �� + 49��
        //(-50 + rand() % 100) / 50.0f  ����Χ�� - 50~49 ���ŵ� - 1.0 �� 0.98������ - 1.0~1.0��
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

