#pragma once
#include "scene.h"
#include "atlas.h"
#include "timer.h"
#include "camera.h"
#include "animation.h"
#include "scene_manager.h"
#include <iostream>

extern Atlas atlas_peashooter_run_right;
extern SceneManager scene_manager;

class MenuScene: public Scene
{
public:
	MenuScene()=default;
	~MenuScene()=default;
	
	void on_enter() override;
	void on_update(int delta) override;
	void on_draw() override;
	void on_input(const ExMessage& msg) override;
	void on_exit() override;
	
private:
	Timer timer;
	Camera camera;
	Animation animation_peashooter_run_right;
};

