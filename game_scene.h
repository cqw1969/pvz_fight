#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_

#include "util.h"
#include "scene.h"
#include "player.h"
#include "platform.h"
#include "scene_manager.h"
#include "status_bar.h"
#include <vector>

extern Player* player_1;
extern Player* player_2;

extern IMAGE img_sky;
extern IMAGE img_hills;
extern IMAGE img_platform_large;
extern IMAGE img_platform_small;

extern IMAGE img_1P_winner;
extern IMAGE img_2P_winner;
extern IMAGE img_winner_bar;

extern Camera main_camera;
extern std::vector<Platform> platform_list;

extern IMAGE* img_player_1_avatar;
extern IMAGE* img_player_2_avatar;

extern SceneManager scene_manager;

class GameScene : public Scene
{
public:
	GameScene() = default;
	~GameScene() = default;

	void on_enter() override;
	void on_update(int delta) override;
	void on_draw(const Camera& camera) override;
	void on_input(const ExMessage& msg) override;
	void on_exit() override;

private:
	const float speed_winner_bar = 3.0f;	//结算动效背景和文字的滑动速度
	const float speed_winner_text = 1.5f;	//结算动效文字的滑动速度

	POINT pos_img_sky = { 0 };
	POINT pos_img_hills = { 0 };

	StatusBar status_bar_1P;
	StatusBar status_bar_2P;

	bool is_game_over = false;

	POINT pos_img_winner_bar = { 0 };	//结算动效背景位置
	POINT pos_img_winner_text = { 0 };	//结算动效文字位置
	int pos_x_img_winner_bar_dst = 0;	//结算动效背景移动的目标位置
	int pos_x_img_winner_text_dst = 0;	//结算动效文字移动的目标位置
	Timer timer_winner_slide_in;		//结算动效背景和文字的滑入动画(定时器)
	Timer timer_winner_slide_out;		//结算动效背景和文字的滑出动画(定时器)
	bool is_slide_out_started = false;	//结算动效是否开始滑出
};


#endif // !_GAME_SCENE_H_