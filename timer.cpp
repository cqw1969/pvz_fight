#include "timer.h"
void Timer::restart() {
	pass_time = 0;
	shotted = false;
}

void Timer::set_wait_time(int val)
{
	wait_time = val;
}

void Timer::set_one_shot(bool flag)
{
	one_shot = flag;
}

void Timer::set_callback(std::function<void()> callback) {
	this->callback = callback;
}

void Timer::pause()
{
	paused = true;
}

void Timer::resume()
{
	paused = false;
}

void Timer::on_update(int delta) {
	if (paused) {
		return;
	}
	pass_time += delta;
	if (pass_time >= wait_time) {
		if ((!one_shot || (one_shot && !shotted)) && callback) //如果是单次触发且未触发过(如果不是单次触发)，则触发回调函数
			callback();
		shotted=true;		//标记为已触发
		pass_time = 0;		//重来
	}
}
