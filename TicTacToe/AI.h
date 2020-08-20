#pragma once

#include "Entity.h"
#include "Board.h"
#include <vector>

class AI : public Entity {

private:
	std::vector<int> options;
	std::vector<char> list;
	std::string list_str;

	char boxesClone[9];
	char winner;
	int finalMove;
	double failingChance = 99;

public:
	AI ();

	int assignPosition (char boxes[], int elements, int gamemode);
	void checkWinner (std::string &string, char &winner, std::vector<char> &vector);
	void scanWinner ();
	void blockPlayer ();
	void lookAhead (int gamemode);

	~AI ();
};

