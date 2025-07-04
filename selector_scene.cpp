#include "selector_scene.h"
void SelectorScene::on_enter() {
	std::cout << "进入角色选择场景" << std::endl;
}
void SelectorScene::on_update() {
	std::cout << "角色选择正在运行..." << std::endl;
}
void SelectorScene::on_draw() {
	outtextxy(10, 10, _T("角色选择绘图内容"));
}
void SelectorScene::on_input(const ExMessage& msg) {
	if (msg.message == WM_KEYDOWN) {
		scene_manager.switch_to(SceneManager::SceneType::Game);
	}
}
void SelectorScene::on_exit() {
	std::cout << "角色选择场景退出" << std::endl;
}

