#include "menu_scene.h"
void MenuScene::on_enter() {
	std::cout << "�������˵�" << std::endl;
}
void MenuScene::on_update() {
	std::cout << "���˵���������..." << std::endl;
}
void MenuScene::on_draw() {
	outtextxy(10, 10, _T("���˵���ͼ����"));
}
void MenuScene::on_input(const ExMessage& msg) {}
void MenuScene::on_exit() {
	std::cout << "���˵��˳�" << std::endl;
}

