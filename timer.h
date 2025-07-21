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
	void resume();	//����
	void on_update(int delta);

private:
	int pass_time = 0;						//�ѹ�ʱ��
	int wait_time = 0;							//�ȴ�ʱ��
	bool paused = false;					//�Ƿ���ͣ
	bool shotted = false;					//�Ƿ񴥷� (������û)
	bool one_shot = false;					//�Ƿ񵥴δ���
	std::function<void()> callback;	//�ص�����
};


#endif // !_TIMER_H_