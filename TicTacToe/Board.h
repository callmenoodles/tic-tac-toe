#pragma once

#include "Player.h"
#include <SDL.h>
#include <vector>

class Board {
public:
	const static int PADDING = 30;
	int size;
	int box_size;
	bool random;
	char boxes[9];
	char turn = 'X';
	char turns = ('X' ^ 'O');
	bool full;
	
	char winner;
	std::vector<char> list;
	std::string list_str;
	int elements;
	int scoreX, scoreO;
		
public:
	Board ();

	int processEvents (SDL_Event evnt);
	void setBox (int count, char &value);
	int getBox (int count);
	void switchTurn ();
	void draw (SDL_Renderer* renderer);
	void checkWinner (std::string &string, char &winner, std::vector<char> &vector);
	void scanWinner ();
	bool isFull ();
	void clear ();

	~Board ();
};

