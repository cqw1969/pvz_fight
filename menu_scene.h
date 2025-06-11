#pragma once
#include "scene.h"
#include <iostream>
class MenuScene: public Scene
{
public:
	MenuScene()=default;
	~MenuScene()=default;
	
	void on_enter();
	void on_update();
	void on_draw();
	void on_input(const ExMessage& msg);
	void on_exit();

private:
};

