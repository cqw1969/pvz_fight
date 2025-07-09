#pragma once
#include "scene.h"
#include "animation.h"
#include "scene_manager.h"

#pragma region {资源加载代码}
extern IMAGE img_VS; // VS 艺术字图片
extern IMAGE img_1P; // 1P 文本图片
extern IMAGE img_2P; // 2P 文本图片
extern IMAGE img_1P_desc; // 1P 键位描述图片
extern IMAGE img_2P_desc; // 2P 键位描述图片
extern IMAGE img_gravestone_left; // 朝向左的墓碑图片
extern IMAGE img_gravestone_right; // 朝向右的墓碑图片
extern IMAGE img_selector_tip; // 选角界面提示文本图片
extern IMAGE img_selector_background; // 选角界面背景图片
extern IMAGE img_1P_selector_btn_idle_left; // 1P 向左选择按钮默认状态图片
extern IMAGE img_1P_selector_btn_idle_right; // 1P 向右选择按钮默认状态图片
extern IMAGE img_1P_selector_btn_down_left; // 1P 向左选择按钮按下状态图片
extern IMAGE img_1P_selector_btn_down_right; // 1P 向右选择按钮按下状态图片
extern IMAGE img_2P_selector_btn_idle_left; // 2P 向左选择按钮默认状态图片
extern IMAGE img_2P_selector_btn_idle_right; // 2P 向右选择按钮默认状态图片
extern IMAGE img_2P_selector_btn_down_left; // 2P 向左选择按钮按下状态图片
extern IMAGE img_2P_selector_btn_down_right; // 2P 向右选择按钮按下状态图片
extern IMAGE img_peashooter_selector_background_left; // 选角界面朝向左的婉逗射手背景图片
extern IMAGE img_peashooter_selector_background_right; // 选角界面朝向右的婉逗射手背景图片
extern IMAGE img_sunflower_selector_background_left; // 选角界面朝向左的龙日葵背景图片
extern IMAGE img_sunflower_selector_background_right; // 选角界面朝向右的龙日葵背景图片
extern Atlas atlas_peashooter_idle_right; // 婉逗射手朝向右的默认动画图集
extern Atlas atlas_sunflower_idle_right; // 龙日葵朝向右的默认动画图集
extern IMAGE img_avatar_peashooter; // 婉逗射手头像图片
extern IMAGE img_avatar_sunflower; // 龙日葵头像图片
#pragma endregion

extern SceneManager scene_manager;

class SelectorScene : public Scene
{
public:
	SelectorScene() = default;
	~SelectorScene() = default;

	void on_enter() override;
	void on_update(int delta) override;
	void on_draw(const Camera& camera) override;
	void on_input(const ExMessage& msg) override;
	void on_exit() override;

private:
	enum class PlayerType {
		Peashooter = 0, Sunflower, 
		Invalid //无效类型  同时代表最大数量
	};
	POINT pos_img_VS = { 0 };												// VS 艺术字图片位置
	POINT pos_img_tip = { 0 };												//提示信息文本图片位置
	POINT pos_img_1P = { 0 };												// 1P 文本图片位置
	POINT pos_img_2P = { 0 };												// 2P 文本图片位置
	POINT pos_img_1P_desc = { 0 };										// 1P 键位描述图片位置
	POINT pos_img_2P_desc = { 0 };										// 2P 键位描述图片位置
	POINT pos_img_1P_name = { 0 };									//1P 角色姓名文本位置
	POINT pos_img_2P_name = { 0 };									//2P 角色姓名文本位置
	POINT pos_animation_1P = { 0 };									//1P 动画位置
	POINT pos_animation_2P = { 0 };									//2P 动画位置
	POINT pos_img_1P_gravestone = { 0 };							// 1P 墓碑图片位置
	POINT pos_img_2P_gravestone = { 0 };							// 2P 墓碑图片位置
	POINT pos_1P_selector_btn_left = { 0 };							// 1P 向左选择按钮位置
	POINT pos_1P_selector_btn_right = { 0 };						// 1P 向右选择按钮位置
	POINT pos_2P_selector_btn_left = { 0 };							// 2P 向左选择按钮位置
	POINT pos_2P_selector_btn_right = { 0 };						// 2P 向右选择按钮位置

	Animation animation_peashooter;									// 婉逗射手动画
	Animation animation_sunflower;									// 龙日葵动画

	PlayerType player_type_1=PlayerType::Peashooter;		// 1P 角色类型
	PlayerType player_type_2=PlayerType::Sunflower;			// 2P 角色类型

	LPCTSTR str_peashooter_name = _T("婉逗射手");			// 婉逗射手角色名
	LPCTSTR str_sunflower_name = _T("龙日葵");					// 龙日葵角色名

	int selector_background_scorll_offset_x = 0;					// 选角界面背景图片滚动偏移量

	bool is_btn_1P_left_down = false;									// 1P 向左选择按钮按下状态
	bool is_btn_1P_right_down = false;									// 1P 向右选择按钮按下状态
	bool is_btn_2P_left_down = false;									// 2P 向左选择按钮按下状态
	bool is_btn_2P_right_down = false;									// 2P 向右选择按钮按下状态

	void outtextxy_shaded(int x, int y, LPCTSTR str);			// 绘制带有阴影的文本
};

