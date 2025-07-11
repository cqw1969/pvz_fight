#include "peashooter_player.h"
PeashooterPlayer::PeashooterPlayer(){
	animation_idle_left.set_atlas(&atlas_peashooter_idle_left);
	animation_idle_right.set_atlas(&atlas_peashooter_idle_right);
	animation_run_left.set_atlas(&atlas_peashooter_run_left);
	animation_run_right.set_atlas(&atlas_peashooter_run_right);

	animation_idle_left.set_interval(75);
	animation_idle_right.set_interval(75);
	animation_run_left.set_interval(75);
	animation_run_right.set_interval(75);

	size.x = 96, size.y = 96;
}
void PeashooterPlayer::on_update(int delta) {
	Player::on_update(delta);
	std::cout << "���������ڸ���..." << std::endl;
}
