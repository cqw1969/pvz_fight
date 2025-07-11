#pragma once
#include "player.h"
#include <iostream>

extern Atlas atlas_sunflower_idle_left;
extern Atlas atlas_sunflower_idle_right;
extern Atlas atlas_sunflower_run_left;
extern Atlas atlas_sunflower_run_right;

class SunflowerPlayer : public Player
{
public:
	SunflowerPlayer();
	~SunflowerPlayer()=default;
	void on_update(int delta) override;

};

