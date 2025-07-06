#pragma once
#include "scene.h"
#include "scene_manager.h"
#include <iostream>

extern SceneManager scene_manager;

class SelectorScene : public Scene
{
public:
	SelectorScene() = default;
	~SelectorScene() = default;

	void on_enter() override;
	void on_update(int delta) override;
	void on_draw() override;
	void on_input(const ExMessage& msg) override;
	void on_exit() override;

private:
};

