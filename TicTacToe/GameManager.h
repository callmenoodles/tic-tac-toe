#pragma once

#include "Board.h"
#include "Player.h"
#include "AI.h"
#include <SDL.h>
#include <vector>

class GameManager {

public:
	const static int SCREEN_W = 690;
	const static int SCREEN_H = 690;
	const static int SCREEN_SIZE = SCREEN_W * SCREEN_H;

private:
	int gamemode;

public:
	SDL_Window* _window;
	SDL_Renderer* _renderer;
	SDL_Texture* _texture;
	Uint32* _buffer;

	Board board;
	std::vector<Player*> players;
	std::vector<AI*> AIs;

public:
	GameManager ();

	void init ();
	void processEvents ();
	void positionPlayer ();
	void update ();
	void draw ();
	void close ();

	~GameManager ();
};

