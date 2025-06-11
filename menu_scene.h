#pragma once
#include "scene.h"
#include <iostream>
class MenuScene: public Scene
{
public:
	MenuScene()=default;
	~MenuScene()=default;
	
	void on_enter() override;
	void on_update() override;
	void on_draw() override;
	void on_input(const ExMessage& msg) override;
	void on_exit() override;

private:
};

