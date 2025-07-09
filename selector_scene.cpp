#include "selector_scene.h"
void SelectorScene::on_enter() {
	animation_peashooter.set_atlas(&atlas_peashooter_idle_right);
	animation_sunflower.set_atlas(&atlas_sunflower_idle_right);
	animation_peashooter.set_interval(100);
	animation_sunflower.set_interval(100);

	static const int OFFSET_X = 50;

	pos_img_VS.x = (getwidth() - img_VS.getwidth()) / 2;
	pos_img_VS.y = (getheight() - img_VS.getheight()) / 2;
	pos_img_tip.x = (getwidth() - img_selector_tip.getwidth()) / 2;
	pos_img_tip.y = getheight() - 125;
	pos_img_1P.x = (getwidth() / 2 - img_1P.getwidth()) / 2 - OFFSET_X;
	pos_img_1P.y = 35;
	pos_img_2P.x = getwidth() / 2 + (getwidth() / 2 - img_2P.getwidth()) / 2 + OFFSET_X;
	pos_img_2P.y = pos_img_1P.y;
	pos_img_1P_desc.x = (getwidth() / 2 - img_1P_desc.getwidth()) / 2 - OFFSET_X;
	pos_img_1P_desc.y = getheight() - 150;
	pos_img_2P_desc.x = getwidth() / 2 + (getwidth() / 2 - img_2P_desc.getwidth()) / 2 + OFFSET_X;
	pos_img_2P_desc.y = pos_img_1P_desc.y;
	pos_img_1P_gravestone.x = (getwidth() / 2 - img_gravestone_right.getwidth()) / 2 - OFFSET_X;
	pos_img_1P_gravestone.y = pos_img_1P.y + img_1P.getheight() + 35;
	pos_img_2P_gravestone.x = getwidth() / 2 + (getwidth() / 2 - img_gravestone_left.getwidth()) / 2 + OFFSET_X;
	pos_img_2P_gravestone.y = pos_img_1P_gravestone.y;
	pos_animation_1P.x = (getwidth() / 2 - atlas_peashooter_idle_right.get_image(0)->getwidth()) / 2 - OFFSET_X;
	pos_animation_1P.y = pos_img_1P_gravestone.y + 80;
	pos_animation_2P.x = getwidth() / 2 + (getwidth() / 2 - atlas_peashooter_idle_right.get_image(0)->getwidth()) / 2 + OFFSET_X;
	pos_animation_2P.y = pos_animation_1P.y;
	pos_img_1P_name.y = pos_animation_1P.y + 155;
	pos_img_2P_name.y = pos_img_1P_name.y;
	pos_1P_selector_btn_left.x = pos_img_1P_gravestone.x - img_1P_selector_btn_idle_left.getwidth();
	pos_1P_selector_btn_left.y = pos_img_1P_gravestone.y + (img_gravestone_right.getheight() - img_1P_selector_btn_idle_left.getheight()) / 2;
	pos_1P_selector_btn_right.x = pos_img_1P_gravestone.x + img_gravestone_right.getwidth();
	pos_1P_selector_btn_right.y = pos_1P_selector_btn_left.y;
	pos_2P_selector_btn_left.x = pos_img_2P_gravestone.x - img_2P_selector_btn_idle_left.getwidth();
	pos_2P_selector_btn_left.y = pos_1P_selector_btn_left.y;
	pos_2P_selector_btn_right.x = pos_img_2P_gravestone.x + img_gravestone_left.getwidth();
	pos_2P_selector_btn_right.y = pos_1P_selector_btn_left.y;
}
void SelectorScene::on_update(int delta) {
	animation_peashooter.on_update(delta);
	animation_sunflower.on_update(delta);

	selector_background_scorll_offset_x += 5;
	if (selector_background_scorll_offset_x > img_peashooter_selector_background_left.getwidth())
		selector_background_scorll_offset_x = 0;
}
void SelectorScene::on_draw(const Camera& camera) {
	IMAGE* img_p1_selector_background = nullptr;
	IMAGE* img_p2_selector_background = nullptr;

	switch (player_type_2) {
		case PlayerType::Peashooter:
			img_p1_selector_background = &img_peashooter_selector_background_right;
			break;
		case PlayerType::Sunflower:
			img_p1_selector_background = &img_sunflower_selector_background_right;
			break;
		default:
			img_p1_selector_background = &img_peashooter_selector_background_right;
			break;
	}
	switch (player_type_1) {
	case PlayerType::Peashooter:
		img_p2_selector_background = &img_peashooter_selector_background_left;
		break;
	case PlayerType::Sunflower:
		img_p2_selector_background = &img_sunflower_selector_background_left;
		break;
	default:
		img_p2_selector_background = &img_peashooter_selector_background_left;
		break;
	}
	

	putimage(0, 0, &img_selector_background); 
	//��ߵ���� ��β
	Util::putimage_alpha(selector_background_scorll_offset_x-img_p1_selector_background->getwidth(), 0, img_p1_selector_background);
	//��ߵ��ұ� �ɼ�
	Util::putimage_alpha(selector_background_scorll_offset_x, 0, 
		img_p1_selector_background->getwidth() - selector_background_scorll_offset_x, 0, img_p1_selector_background, 0, 0);
	//�ұߵ���� �ɼ�
	Util::putimage_alpha(getwidth() - img_p2_selector_background->getwidth(), 0, img_p2_selector_background->getwidth() -
		selector_background_scorll_offset_x, 0, img_p2_selector_background, selector_background_scorll_offset_x, 0);
	//�ұߵ��ұ� ��β
	Util::putimage_alpha(getwidth() - selector_background_scorll_offset_x, 0, img_p2_selector_background);

	Util::putimage_alpha(pos_img_VS.x, pos_img_VS.y, &img_VS); 
	Util::putimage_alpha(pos_img_1P.x, pos_img_1P.y, &img_1P);
	Util::putimage_alpha(pos_img_2P.x, pos_img_2P.y, &img_2P);
	Util::putimage_alpha(pos_img_1P_gravestone.x, pos_img_1P_gravestone.y, &img_gravestone_left);
	Util::putimage_alpha(pos_img_2P_gravestone.x, pos_img_2P_gravestone.y, &img_gravestone_right);

	switch (player_type_1) {
	case PlayerType::Peashooter:
		animation_peashooter.on_draw(camera, pos_animation_1P.x, pos_animation_1P.y);
		pos_img_1P_name.x = pos_img_1P_gravestone.x + (img_gravestone_right.getwidth() - textwidth(str_peashooter_name)) / 2;
		outtextxy_shaded(pos_img_1P_name.x, pos_img_1P_name.y, str_peashooter_name);
		break;
	case PlayerType::Sunflower:
		animation_sunflower.on_draw(camera, pos_animation_1P.x, pos_animation_1P.y);
		pos_img_1P_name.x = pos_img_1P_gravestone.x + (img_gravestone_right.getwidth() - textwidth(str_sunflower_name)) / 2;
		outtextxy_shaded(pos_img_1P_name.x, pos_img_1P_name.y, str_sunflower_name);
		break;
	}

	switch (player_type_2) {
	case PlayerType::Peashooter:
		animation_peashooter.on_draw(camera, pos_animation_2P.x, pos_animation_2P.y);
		pos_img_2P_name.x = pos_img_2P_gravestone.x + (img_gravestone_right.getwidth() - textwidth(str_peashooter_name)) / 2;
		outtextxy_shaded(pos_img_2P_name.x, pos_img_2P_name.y, str_peashooter_name);
		break;
	case PlayerType::Sunflower:
		animation_sunflower.on_draw(camera, pos_animation_2P.x, pos_animation_2P.y);
		pos_img_2P_name.x = pos_img_2P_gravestone.x + (img_gravestone_right.getwidth() - textwidth(str_sunflower_name)) / 2;
		outtextxy_shaded(pos_img_2P_name.x, pos_img_2P_name.y, str_sunflower_name);
		break;
	}

	Util::putimage_alpha(pos_1P_selector_btn_left.x, pos_1P_selector_btn_left.y, 
		is_btn_1P_left_down? &img_1P_selector_btn_down_left : &img_1P_selector_btn_idle_left);
	Util::putimage_alpha(pos_1P_selector_btn_right.x, pos_1P_selector_btn_right.y, 
		is_btn_1P_right_down? &img_1P_selector_btn_down_right : &img_1P_selector_btn_idle_right);
	Util::putimage_alpha(pos_2P_selector_btn_left.x, pos_2P_selector_btn_left.y, 
		is_btn_2P_left_down? &img_2P_selector_btn_down_left : &img_2P_selector_btn_idle_left);
	Util::putimage_alpha(pos_2P_selector_btn_right.x, pos_2P_selector_btn_right.y, 
		is_btn_2P_right_down? &img_2P_selector_btn_down_right : &img_2P_selector_btn_idle_right);

	Util::putimage_alpha(pos_img_1P_desc.x, pos_img_1P_desc.y, &img_1P_desc);
	Util::putimage_alpha(pos_img_2P_desc.x, pos_img_2P_desc.y, &img_2P_desc);
	Util::putimage_alpha(pos_img_tip.x, pos_img_tip.y, &img_selector_tip);
}
void SelectorScene::on_input(const ExMessage& msg) {
	switch (msg.message) {
		case WM_KEYDOWN:
			switch (msg.vkcode) {
				case 0x41: // A
					is_btn_1P_left_down = true;
					break;
				case 0x44: // D
					is_btn_1P_right_down = true;
					break;
				case VK_LEFT://��
					is_btn_2P_left_down = true;
					break;
				case VK_RIGHT://��
					is_btn_2P_right_down = true;
					break;
			}
			break;
		case WM_KEYUP:
			switch (msg.vkcode) {
			case 0x41: // A
				is_btn_1P_left_down = false;					//�������˴���Ϊ�˱���<0�����,�Ҵ˴�����Ϊ0,��Ϊ��С-1+InvalidҲֻ��Ϊ1,��Ϊȡģ,����Ҳ�����ﵽInvalid
				player_type_1 = (PlayerType)(((int)PlayerType::Invalid+ (int)player_type_1 - 1) % (int)PlayerType::Invalid);
				mciSendString(_T("play ui_switch from 0"), NULL, 0, NULL);
				break;
			case 0x44: // D
				is_btn_1P_right_down = false;
				player_type_1 = (PlayerType)(((int)PlayerType::Invalid + (int)player_type_1 + 1) % (int)PlayerType::Invalid);
				mciSendString(_T("play ui_switch from 0"), NULL, 0, NULL);
				break;
			case VK_LEFT://��
				is_btn_2P_left_down = false;
				player_type_2 = (PlayerType)(((int)PlayerType::Invalid + (int)player_type_2 - 1) % (int)PlayerType::Invalid);
				mciSendString(_T("play ui_switch from 0"), NULL, 0, NULL);
				break;
			case VK_RIGHT://��
				is_btn_2P_right_down = false;
				player_type_2 = (PlayerType)(((int)PlayerType::Invalid + (int)player_type_2 + 1) % (int)PlayerType::Invalid);
				mciSendString(_T("play ui_switch from 0"), NULL, 0, NULL);
				break;
			case VK_RETURN:
				scene_manager.switch_to(SceneManager::SceneType::Game);
				mciSendString(_T("play ui_switch from 0"), NULL, 0, NULL);
				break;
			}
			break;
		default:
			break;
	}
}
void SelectorScene::on_exit() {
}

void SelectorScene::outtextxy_shaded(int x, int y, LPCTSTR str)
{
	settextcolor(RGB(45, 45, 45));
	outtextxy(x + 3, y + 3, str);
	settextcolor(RGB(255, 255, 255));
	outtextxy(x, y, str);
}

