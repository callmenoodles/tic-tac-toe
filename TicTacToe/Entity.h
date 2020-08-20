#pragma once

#include <SDL.h>
#include <string>

class Entity {
public:
	int _x;
	int _y;
	int size;

public:
	SDL_Texture* _texture;
	SDL_Rect _rect;

public:
	Entity ();

	void loadTexture (std::string &filePath, SDL_Renderer* renderer);
	void draw (SDL_Renderer* renderer);

	~Entity ();
};

