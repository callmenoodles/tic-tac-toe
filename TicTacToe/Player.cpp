#include "Player.h"
#include <SDL_image.h>

Player::Player () {}

Player::~Player () {
	SDL_DestroyTexture (_texture);
}
