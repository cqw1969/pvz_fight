#include "particle.h"

Particle::Particle(const Vector2& position, Atlas* atlas, int lifespan)
	: position(position), atlas(atlas), lifespan(lifespan){}

void Particle::set_atlas(Atlas* new_atlas) {
	atlas = new_atlas;
}
void Particle::set_position(const Vector2& new_position) {
	position = new_position;
}
void Particle::set_lifespan(int ms) {
	lifespan = ms;
}
bool Particle::check_valid() const {
	return valid;
}
void Particle::on_update(int delta) {
	timer += delta;
	if (timer >= lifespan)
	{
		timer = 0;
		idx_frame++;
		if (idx_frame >= atlas->get_size())
		{
			idx_frame = atlas->get_size()-1;
			valid = false;
		}
	}
}
void Particle::on_draw(const Camera& camera) const {
	Util::putimage_alpha(camera, (int)position.x, (int)position.y, atlas->get_image(idx_frame));
}

