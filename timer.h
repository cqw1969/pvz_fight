#ifndef _TIMER_H_
#define _TIMER_H_

#include <functional>
class Timer
{
public:
	Timer() = default;
	~Timer()=default;

	void restart();
	void set_wait_time(int val);
	void set_one_shot(bool flag);
	void set_callback(std::function<void()> callback);
	void pause();
	void resume();	//继续
	void on_update(int delta);

private:
	int pass_time = 0;						//已过时间
	int wait_time = 0;							//等待时间
	bool paused = false;					//是否暂停
	bool shotted = false;					//是否触发 (触发了没)
	bool one_shot = false;					//是否单次触发
	std::function<void()> callback;	//回调函数
};


#endif // !_TIMER_H_