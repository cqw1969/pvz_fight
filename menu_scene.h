#ifndef _MENU_SCENE_H_
#define _MENU_SCENE_H_

#include "scene.h"
#include "atlas.h"
#include "timer.h"
#include "camera.h"
#include "animation.h"
#include "scene_manager.h"

extern IMAGE img_menu_background;
extern SceneManager scene_manager;

class MenuScene: public Scene
{
public:
	MenuScene()=default;
	~MenuScene()=default;
	
	void on_enter() override;
	void on_update(int delta) override;
	void on_draw(const Camera& camera) override;
	void on_input(const ExMessage& msg) override;
	void on_exit() override;
	
private:
	
};


#endif // !_MENU_SCENE_H_