#include "game_scene.h"
void GameScene::on_enter() {
	player_1->set_position(200, 50);
	player_2->set_position(975, 50);

	pos_img_sky.x = (getwidth() - img_sky.getwidth()) / 2;
	pos_img_sky.y = (getheight() - img_sky.getheight()) / 2;
	pos_img_hills.x = (getwidth() - img_hills.getwidth()) / 2;
	pos_img_hills.y = (getheight() - img_hills.getheight()) / 2;

	platform_list.resize(4);

	Platform& large_platform = platform_list[0];
	large_platform.img=&img_platform_large;
	large_platform.render_position.x = 122;
	large_platform.render_position.y = 455;
	large_platform.shape.left = (float)large_platform.render_position.x + 30;
	large_platform.shape.right =(float) large_platform.render_position.x+img_platform_large.getwidth()-30;
	large_platform.shape.y= (float)large_platform.render_position.y+60;

	Platform& small_platform_1 = platform_list[1];
	small_platform_1.img = &img_platform_small;
	small_platform_1.render_position.x = 175;
	small_platform_1.render_position.y = 360;
	small_platform_1.shape.left = (float)small_platform_1.render_position.x + 40;
	small_platform_1.shape.right = (float)small_platform_1.render_position.x + img_platform_small.getwidth() - 40;
	small_platform_1.shape.y = (float)small_platform_1.render_position.y + img_platform_small.getheight() / 2;

	Platform& small_platform_2 = platform_list[2];
	small_platform_2.img = &img_platform_small;
	small_platform_2.render_position.x = 855;
	small_platform_2.render_position.y = 360;
	small_platform_2.shape.left = (float)small_platform_2.render_position.x + 40;
	small_platform_2.shape.right = (float)small_platform_2.render_position.x + img_platform_small.getwidth() - 40;
	small_platform_2.shape.y = (float)small_platform_2.render_position.y + img_platform_small.getheight() / 2;

	Platform& small_platform_3 = platform_list[3];
	small_platform_3.img = &img_platform_small;
	small_platform_3.render_position.x = 515;
	small_platform_3.render_position.y = 225;
	small_platform_3.shape.left = (float)small_platform_3.render_position.x + 40;
	small_platform_3.shape.right = (float)small_platform_3.render_position.x + img_platform_small.getwidth() - 40;
	small_platform_3.shape.y = (float)small_platform_3.render_position.y + img_platform_small.getheight() / 2;
}
void GameScene::on_update(int delta) {
	player_1->on_update(delta);
	player_2->on_update(delta);
}
void GameScene::on_draw(const Camera& camera) {
	Util::putimage_alpha(camera, pos_img_sky.x, pos_img_sky.y, &img_sky);
	Util::putimage_alpha(camera, pos_img_hills.x, pos_img_hills.y, &img_hills);

	for (Platform& platform : platform_list) {
		platform.on_draw(camera);
	}

	if (is_debug) {
		settextcolor(RGB(255, 0, 0));
		outtextxy(15, 15, _T("Debug mode,Press Q"));
	}

	player_1->on_draw(camera);
	player_2->on_draw(camera);
}
void GameScene::on_input(const ExMessage& msg) {
	player_1->on_input(msg);
	player_2->on_input(msg);

	switch (msg.message) {
	case WM_KEYUP:
		if (msg.vkcode == 0x51) {//Q
			is_debug=!is_debug;
			break;
		}
	default:
		break;
	}
}
void GameScene::on_exit() {

}

