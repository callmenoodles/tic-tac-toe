#include "AI.h"
#include <iostream>
#include <time.h>

AI::AI () {
	srand (time (NULL));
}

int AI::assignPosition (char boxes[], int elements, int gamemode) {
	options.clear ();
	finalMove = -1;
	winner = NULL;

	for (int i = 0;i < 9;i++) {
		if (boxes[i] == NULL) {
			options.push_back (i);
		}
	}

	for (int i = 0;i < 9;i++) {
		boxesClone[i] = boxes[i];
	} 

	lookAhead (gamemode);

	int random = rand ();

	if (gamemode == 3 && random <= RAND_MAX * failingChance/100) {
		blockPlayer ();
	} else if (gamemode == 4) {
		blockPlayer ();
	}

	if (finalMove != -1) {
		return finalMove;
	} else {
		return options[rand () % ((options.size ()-1)-0 + 1) + 0];
	}
}

void AI::checkWinner (std::string &string, char &winner, std::vector<char> &vector) {

	if (string == "XXX") {
		winner = 'X';
	} else if (string == "OOO") {
		winner = 'O';
	} else {
		vector.clear ();
	}
}

void AI::scanWinner () {

	// Horizontal Checking
	for (int i = 0;i < sizeof (boxesClone);i += 3) {
		list.clear ();

		for (int j = i;j < i+3;j++) {
			list.push_back (boxesClone[j]);
		}

		list_str = std::string (list.begin (), list.end ());

		checkWinner (list_str, winner, list);
	}

	// Vertical Checking
	for (int i = 0;i < sqrt (sizeof (boxesClone));i++) {
		list.clear ();

		for (int j = i;j <= i+6;j += 3) {
			list.push_back (boxesClone[j]);
		}

		list_str = std::string (list.begin (), list.end ());

		checkWinner (list_str, winner, list);
	}

	// Left Diagonal Checking
	for (int i = 0;i < sizeof (boxesClone);i += sqrt (sizeof (boxesClone))+1) {
		list.push_back (boxesClone[i]);
		list_str = std::string (list.begin (), list.end ());

		if (list.size () == sqrt (sizeof (boxesClone))) {
			checkWinner (list_str, winner, list);
		}
	}

	// Right Diagonal Checking
	for (int i = sqrt (sizeof (boxesClone))-1;i < sizeof (boxesClone)-1;i += sqrt (sizeof (boxesClone))-1) {
		list.push_back (boxesClone[i]);
		list_str = std::string (list.begin (), list.end ());

		if (list.size () == sqrt (sizeof (boxesClone))) {
			checkWinner (list_str, winner, list);
		}
	}
}

void AI::blockPlayer () {
	
	if (winner != 'O') {
		for (int i = 0;i < options.size ();i++) {
			boxesClone[options[i]] = 'X';

			scanWinner ();
			if (winner == 'X') {
				finalMove = options[i];
				boxesClone[options[i]] = NULL;
				break;
			} else {
				boxesClone[options[i]] = NULL;
			}
		}
	}
}

void AI::lookAhead (int gamemode) {
	
	for (int i = 0;i < options.size ();i++) {
		boxesClone[options[i]] = 'O';

		scanWinner ();
		if (winner == 'O') {
			finalMove = options[i];
			boxesClone[options[i]] = NULL;
			break;
		} else {
			boxesClone[options[i]] = NULL;
		}

	}
}

AI::~AI () {
	SDL_DestroyTexture (_texture);
}
