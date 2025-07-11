#pragma once
#include "player.h"
#include <iostream>

extern Atlas atlas_peashooter_idle_left;
extern Atlas atlas_peashooter_idle_right;
extern Atlas atlas_peashooter_run_left;
extern Atlas atlas_peashooter_run_right;

class PeashooterPlayer:public Player
{
public:
	PeashooterPlayer();
	~PeashooterPlayer()=default;

	void on_update(int delta) override;
};

