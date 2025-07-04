#include "scene.h"
#include "menu_scene.h"
#include "game_scene.h"
#include "selector_scene.h"
#include "scene_manager.h"
#include <graphics.h>

Scene* menu_scene = nullptr;
Scene* game_scene = nullptr;
Scene* selector_scene = nullptr;
SceneManager scene_manager;

int main() {
	//初始化
	ExMessage msg;
	const int FPS = 60;
	initgraph(1280, 720);
	BeginBatchDraw();
	menu_scene = new MenuScene();
	game_scene = new GameScene();
	selector_scene=new SelectorScene();
	scene_manager.set_current_scene(menu_scene);
	while (true) {
		DWORD frame_start_time = GetTickCount();
		//读取操作
		while (peekmessage(&msg)) {
			scene_manager.on_input(msg);
		}

		//处理数据
		scene_manager.on_update();

		//绘制画面
		cleardevice();
		scene_manager.on_draw();
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
