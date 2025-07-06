#include "menu_scene.h"
void MenuScene::on_enter() {
	animation_peashooter_run_right.set_atlas(&atlas_peashooter_run_right);
	animation_peashooter_run_right.set_interval(75);
	animation_peashooter_run_right.set_loop(true);
	;
}
void MenuScene::on_update(int delta) {
	camera.on_update(delta);
	animation_peashooter_run_right.on_update(delta);
}
void MenuScene::on_draw() {
	const Vector2& pos_camera = camera.get_position();
	animation_peashooter_run_right.on_draw((int)100-pos_camera.x, (int)100-pos_camera.y);//世界坐标减去相机坐标
}
void MenuScene::on_input(const ExMessage& msg) {
	if (msg.message == WM_KEYDOWN) {
		scene_manager.switch_to(SceneManager::SceneType::Selector);
	}
}
void MenuScene::on_exit() {
	std::cout << "主菜单退出" << std::endl;
}

