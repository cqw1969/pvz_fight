#include "menu_scene.h"
void menuon_enter() {
	std::cout << "�������˵�" << std::endl;
}
void on_update() {
	std::cout << "���˵���������..." << std::endl;
}
void on_draw() {
	outtextxy(10, 10, _T("���˵���ͼ����"));
}
void on_input(const ExMessage& msg) {}
void on_exit() {
	std::cout << "���˵��˳�" << std::endl;
}
