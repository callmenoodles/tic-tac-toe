#include "Entity.h"
#include <SDL_image.h>

Entity::Entity () {}

void Entity::loadTexture (std::string &filePath, SDL_Renderer* renderer) {
	SDL_Surface* surface = IMG_Load (filePath.c_str ());

	if (!surface) {
		printf ("Failed to create surface: %s\n", SDL_GetError ());
	}

	_texture = SDL_CreateTextureFromSurface (renderer, surface);

	if (!_texture) {
		printf ("Failed to create texture: %s\n", SDL_GetError ());
	}

	SDL_FreeSurface (surface);
}

void Entity::draw (SDL_Renderer* renderer) {
	_rect = {_x, _y, size, size};

	if (_texture) {
		SDL_RenderCopy (renderer, _texture, nullptr, &_rect);
	} else {
		SDL_SetRenderDrawColor (renderer, 100, 100, 100, 255);
		SDL_RenderFillRect (renderer, &_rect);
	}
}

Entity::~Entity () {}
