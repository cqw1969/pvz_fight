#include "game_scene.h"
void GameScene::on_enter() {
	is_game_over = false;
	is_slide_out_started = false;

	pos_img_winner_bar.x = -img_winner_bar.getwidth();
	pos_img_winner_bar.y = (getheight() - img_winner_bar.getheight()) / 2;
	pos_x_img_winner_bar_dst = (getwidth() - img_winner_bar.getwidth()) / 2;

	pos_img_winner_text.x = pos_img_winner_bar.x;
	pos_img_winner_text.y = (getheight() - img_1P_winner.getheight()) / 2;
	pos_x_img_winner_text_dst = (getwidth() - img_1P_winner.getwidth()) / 2;

	timer_winner_slide_in.restart();
	timer_winner_slide_in.set_wait_time(2500);//等待2.5秒后开始滑入
	timer_winner_slide_in.set_one_shot(true);
	timer_winner_slide_in.set_callback([&](){
		is_slide_out_started = true;
		});

	timer_winner_slide_out.restart();
	timer_winner_slide_out.set_wait_time(1000);//等待1秒后开始滑出
	timer_winner_slide_out.set_one_shot(true);
	timer_winner_slide_out.set_callback([&]() {
		scene_manager.switch_to(SceneManager::SceneType::Menu);
		});

	status_bar_1P.set_avatar(img_player_1_avatar);
	status_bar_2P.set_avatar(img_player_2_avatar);

	status_bar_1P.set_position(235, 625);
	status_bar_2P.set_position(675, 625);

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

	mciSendString(_T("play bgm_game repeat from 0"), NULL, 0, NULL);
}
void GameScene::on_update(int delta) {
	player_1->on_update(delta);
	player_2->on_update(delta);

	main_camera.on_update(delta);

	bullet_list.erase(std::remove_if(
		bullet_list.begin(), bullet_list.end(),
		[](const Bullet* bullet) {
			bool deletable = bullet->check_can_remove();
			if (deletable) delete bullet;
			return deletable;
		}),
		bullet_list.end());


	for (Bullet* bullet : bullet_list) {
		bullet->on_update(delta);
	}

	const Vector2& position_player_1 = player_1->get_position();
	const Vector2& position_player_2 = player_2->get_position();
	if (position_player_1.y >= getheight())
		player_1->set_hp(0);
	if (position_player_2.y >= getheight())
		player_2->set_hp(0);
	if (player_1->get_hp() <= 0 || player_2->get_hp() <= 0) {
		if (!is_game_over) {
			mciSendString(_T("stop bgm_game"), NULL, 0, NULL);
			mciSendString(_T("play ui_win from 0"), NULL, 0, NULL);
		}
		is_game_over = true;
	}

	status_bar_1P.set_hp(player_1->get_hp());
	status_bar_1P.set_mp(player_1->get_mp());
	status_bar_2P.set_hp(player_2->get_hp());
	status_bar_2P.set_mp(player_2->get_mp());

	if (is_game_over) {
		pos_img_winner_bar.x += (int)(speed_winner_bar * delta);
		pos_img_winner_text.x += (int)(speed_winner_text * delta);

		if (!is_slide_out_started) {//在游戏结束后 滑入动画进行时 还不能开始滑出的时候
			timer_winner_slide_in.on_update(delta);
			if (pos_img_winner_bar.x > pos_x_img_winner_bar_dst)
				pos_img_winner_bar.x = pos_x_img_winner_bar_dst;
			if (pos_img_winner_text.x > pos_x_img_winner_text_dst)
				pos_img_winner_text.x = pos_x_img_winner_text_dst;
		}
		else {
			timer_winner_slide_out.on_update(delta);
		}
	}

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

	for (Bullet* bullet : bullet_list) {
		bullet->on_draw(camera);
	}

	if (is_game_over) {
		Util::putimage_alpha(pos_img_winner_bar.x, pos_img_winner_bar.y, &img_winner_bar);
		Util::putimage_alpha(pos_img_winner_text.x, pos_img_winner_text.y,
			player_1->get_hp() > 0 ? &img_1P_winner : &img_2P_winner);
	}
	else {
		status_bar_1P.on_draw();
		status_bar_2P.on_draw();
	}
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
	delete player_1; player_1 = nullptr;
	delete player_2; player_2 = nullptr;

	is_debug = false;
	bullet_list.clear();
	main_camera.reset();
}

