#include <graphics.h>
#include "scene.h"
#include "menu_scene.h"
int main() {
	//初始化
	ExMessage msg;
	const int FPS = 60;
	initgraph(1280, 720);
	BeginBatchDraw();
	Scene* scene = new MenuScene();
	scene->on_enter();
	while (true) {
		DWORD frame_start_time = GetTickCount();
		//读取操作
		while (peekmessage(&msg)) {
			scene->on_input(msg);
		}

		//处理数据
		scene->on_update();


		//绘制画面
		cleardevice();
		scene->on_draw();

		FlushBatchDraw();

		DWORD frame_end_time = GetTickCount();
		DWORD frame_delta_time=frame_end_time-frame_start_time;
		if(frame_delta_time<1000/FPS) {
			Sleep(1000/FPS-frame_delta_time);
		}
	}
	EndBatchDraw();
	//释放资源
}
