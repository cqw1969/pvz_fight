#include "game_scene.h"
void GameScene::on_enter() {
	std::cout << "������Ϸ���ڳ���" << std::endl;
}
void GameScene::on_update(int delta) {
	std::cout << "��Ϸ��������..." << std::endl;
}
void GameScene::on_draw() {
	outtextxy(10, 10, _T("��Ϸ���ڻ�ͼ����"));
}
void GameScene::on_input(const ExMessage& msg) {
	if (msg.message == WM_KEYDOWN) {
		scene_manager.switch_to(SceneManager::SceneType::Menu);
	}
}
void GameScene::on_exit() {
	std::cout << "��Ϸ�����˳�" << std::endl;
}

