#pragma once
#include "scene.h"
#include "animation.h"
#include "scene_manager.h"

#pragma region {��Դ���ش���}
extern IMAGE img_VS; // VS ������ͼƬ
extern IMAGE img_1P; // 1P �ı�ͼƬ
extern IMAGE img_2P; // 2P �ı�ͼƬ
extern IMAGE img_1P_desc; // 1P ��λ����ͼƬ
extern IMAGE img_2P_desc; // 2P ��λ����ͼƬ
extern IMAGE img_gravestone_left; // �������Ĺ��ͼƬ
extern IMAGE img_gravestone_right; // �����ҵ�Ĺ��ͼƬ
extern IMAGE img_selector_tip; // ѡ�ǽ�����ʾ�ı�ͼƬ
extern IMAGE img_selector_background; // ѡ�ǽ��汳��ͼƬ
extern IMAGE img_1P_selector_btn_idle_left; // 1P ����ѡ��ťĬ��״̬ͼƬ
extern IMAGE img_1P_selector_btn_idle_right; // 1P ����ѡ��ťĬ��״̬ͼƬ
extern IMAGE img_1P_selector_btn_down_left; // 1P ����ѡ��ť����״̬ͼƬ
extern IMAGE img_1P_selector_btn_down_right; // 1P ����ѡ��ť����״̬ͼƬ
extern IMAGE img_2P_selector_btn_idle_left; // 2P ����ѡ��ťĬ��״̬ͼƬ
extern IMAGE img_2P_selector_btn_idle_right; // 2P ����ѡ��ťĬ��״̬ͼƬ
extern IMAGE img_2P_selector_btn_down_left; // 2P ����ѡ��ť����״̬ͼƬ
extern IMAGE img_2P_selector_btn_down_right; // 2P ����ѡ��ť����״̬ͼƬ
extern IMAGE img_peashooter_selector_background_left; // ѡ�ǽ��泯����������ֱ���ͼƬ
extern IMAGE img_peashooter_selector_background_right; // ѡ�ǽ��泯���ҵ������ֱ���ͼƬ
extern IMAGE img_sunflower_selector_background_left; // ѡ�ǽ��泯��������տ�����ͼƬ
extern IMAGE img_sunflower_selector_background_right; // ѡ�ǽ��泯���ҵ����տ�����ͼƬ
extern Atlas atlas_peashooter_idle_right; // �����ֳ����ҵ�Ĭ�϶���ͼ��
extern Atlas atlas_sunflower_idle_right; // ���տ������ҵ�Ĭ�϶���ͼ��
extern IMAGE img_avatar_peashooter; // ������ͷ��ͼƬ
extern IMAGE img_avatar_sunflower; // ���տ�ͷ��ͼƬ
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
		Invalid //��Ч����  ͬʱ�����������
	};
	POINT pos_img_VS = { 0 };												// VS ������ͼƬλ��
	POINT pos_img_tip = { 0 };												//��ʾ��Ϣ�ı�ͼƬλ��
	POINT pos_img_1P = { 0 };												// 1P �ı�ͼƬλ��
	POINT pos_img_2P = { 0 };												// 2P �ı�ͼƬλ��
	POINT pos_img_1P_desc = { 0 };										// 1P ��λ����ͼƬλ��
	POINT pos_img_2P_desc = { 0 };										// 2P ��λ����ͼƬλ��
	POINT pos_img_1P_name = { 0 };									//1P ��ɫ�����ı�λ��
	POINT pos_img_2P_name = { 0 };									//2P ��ɫ�����ı�λ��
	POINT pos_animation_1P = { 0 };									//1P ����λ��
	POINT pos_animation_2P = { 0 };									//2P ����λ��
	POINT pos_img_1P_gravestone = { 0 };							// 1P Ĺ��ͼƬλ��
	POINT pos_img_2P_gravestone = { 0 };							// 2P Ĺ��ͼƬλ��
	POINT pos_1P_selector_btn_left = { 0 };							// 1P ����ѡ��ťλ��
	POINT pos_1P_selector_btn_right = { 0 };						// 1P ����ѡ��ťλ��
	POINT pos_2P_selector_btn_left = { 0 };							// 2P ����ѡ��ťλ��
	POINT pos_2P_selector_btn_right = { 0 };						// 2P ����ѡ��ťλ��

	Animation animation_peashooter;									// �����ֶ���
	Animation animation_sunflower;									// ���տ�����

	PlayerType player_type_1=PlayerType::Peashooter;		// 1P ��ɫ����
	PlayerType player_type_2=PlayerType::Sunflower;			// 2P ��ɫ����

	LPCTSTR str_peashooter_name = _T("������");			// �����ֽ�ɫ��
	LPCTSTR str_sunflower_name = _T("���տ�");					// ���տ���ɫ��

	int selector_background_scorll_offset_x = 0;					// ѡ�ǽ��汳��ͼƬ����ƫ����

	bool is_btn_1P_left_down = false;									// 1P ����ѡ��ť����״̬
	bool is_btn_1P_right_down = false;									// 1P ����ѡ��ť����״̬
	bool is_btn_2P_left_down = false;									// 2P ����ѡ��ť����״̬
	bool is_btn_2P_right_down = false;									// 2P ����ѡ��ť����״̬

	void outtextxy_shaded(int x, int y, LPCTSTR str);			// ���ƴ�����Ӱ���ı�
};

