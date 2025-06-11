#include "menu_scene.h"
void MenuScene::on_enter() {
	std::cout << "进入主菜单" << std::endl;
}
void MenuScene::on_update() {
	std::cout << "主菜单正在运行..." << std::endl;
}
void MenuScene::on_draw() {
	outtextxy(10, 10, _T("主菜单绘图内容"));
}
void MenuScene::on_input(const ExMessage& msg) {}
void MenuScene::on_exit() {
	std::cout << "主菜单退出" << std::endl;
}

