#include "selector_scene.h"
void SelectorScene::on_enter() {
	std::cout << "�����ɫѡ�񳡾�" << std::endl;
}
void SelectorScene::on_update() {
	std::cout << "��ɫѡ����������..." << std::endl;
}
void SelectorScene::on_draw() {
	outtextxy(10, 10, _T("��ɫѡ���ͼ����"));
}
void SelectorScene::on_input(const ExMessage& msg) {
	if (msg.message == WM_KEYDOWN) {
		scene_manager.switch_to(SceneManager::SceneType::Game);
	}
}
void SelectorScene::on_exit() {
	std::cout << "��ɫѡ�񳡾��˳�" << std::endl;
}

