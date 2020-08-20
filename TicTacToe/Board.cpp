#include "GameManager.h"
#include <iostream>

Board::Board () {}

int Board::processEvents (SDL_Event evnt) {
	int x, y;
	SDL_GetMouseState (&x, &y);

	if (evnt.type == SDL_MOUSEBUTTONDOWN) {

		if (evnt.button.button == SDL_BUTTON_LEFT) {

			if (x > PADDING && x < PADDING + box_size && y > PADDING && y < PADDING + box_size && boxes[0] == NULL && winner == NULL)
				return 1;
			else if (x > PADDING + box_size && x < PADDING + box_size*2 && y > PADDING && y < PADDING + box_size && boxes[1] == NULL && winner == NULL)
				return 2;
			else if (x > PADDING + box_size*2 && x < PADDING + box_size*3 && y > PADDING && y < PADDING + box_size && boxes[2] == NULL && winner == NULL)
				return 3;
			else if (x > PADDING && x < PADDING + box_size && y > PADDING + box_size && y < PADDING + box_size*2 && boxes[3] == NULL && winner == NULL)
				return 4;
			else if (x > PADDING + box_size && x < PADDING + box_size*2 && y > PADDING + box_size && y < PADDING + box_size*2 && boxes[4] == NULL && winner == NULL)
				return 5;
			else if (x > PADDING + box_size*2 && x < PADDING + box_size*3 && y > PADDING + box_size && y < PADDING + box_size*2 && boxes[5] == NULL && winner == NULL)
				return 6;
			else if (x > PADDING && x < PADDING + box_size && y > PADDING + box_size*2 && y < PADDING + box_size*3 && boxes[6] == NULL && winner == NULL)
				return 7;
			else if (x > PADDING + box_size && x < PADDING + box_size*2 && y > PADDING + box_size*2 && y < PADDING + box_size*3 && boxes[7] == NULL && winner == NULL)
				return 8;
			else if (x > PADDING + box_size*2 && x < PADDING + box_size*3 && y > PADDING + box_size*2 && y < PADDING + box_size*3 && boxes[8] == NULL && winner == NULL)
				return 9;
		}
	}

	if (evnt.key.keysym.sym == SDLK_q) {
		clear ();
	}

	return 0;
}

void Board::setBox (int count, char &value) {
	boxes[count] = value;
}

void Board::switchTurn () {
	turn ^= turns;
}

void Board::draw (SDL_Renderer* renderer) {
	SDL_RenderDrawLine (renderer, PADDING + box_size, PADDING, PADDING + box_size, size + PADDING);
	SDL_RenderDrawLine (renderer, PADDING + box_size*2, PADDING, PADDING + box_size*2, size + PADDING);
	
	SDL_RenderDrawLine (renderer, PADDING, PADDING + box_size, size + PADDING, PADDING + box_size);
	SDL_RenderDrawLine (renderer, PADDING, PADDING + box_size*2, size + PADDING, PADDING + box_size*2);
}

void Board::checkWinner (std::string &string, char &winner, std::vector<char> &vector) {
	
	if (string == "XXX") {
		winner = 'X';
	} else if (string == "OOO") {
		winner = 'O';
	} else {
		vector.clear ();
	}
}

void Board::scanWinner () {
	
	// Horizontal Checking
	for (int i = 0;i < sizeof (boxes);i += 3) {
		list.clear ();

		for (int j = i;j < i+3;j++) {
			list.push_back (boxes[j]);
		}

		list_str = std::string (list.begin (), list.end ());

		checkWinner (list_str, winner, list);
	}

	// Vertical Checking
	for (int i = 0;i < sqrt (sizeof (boxes));i++) {
		list.clear ();

		for (int j = i;j <= i+6;j += 3) {
			list.push_back (boxes[j]);
		}

		list_str = std::string (list.begin (), list.end ());

		checkWinner (list_str, winner, list);
	}

	// Left Diagonal Checking
	for (int i = 0;i < sizeof (boxes);i += sqrt (sizeof (boxes))+1) {
		list.push_back (boxes[i]);
		list_str = std::string (list.begin (), list.end ());

		if (list.size () == sqrt (sizeof (boxes))) {
			checkWinner (list_str, winner, list);
		}
	}

	// Right Diagonal Checking
	for (int i = sqrt (sizeof (boxes))-1;i < sizeof (boxes)-1;i += sqrt (sizeof (boxes))-1) {
		list.push_back (boxes[i]);
		list_str = std::string (list.begin (), list.end ());

		if (list.size () == sqrt (sizeof (boxes))) {
			checkWinner (list_str, winner, list);
		}
	}

	if (winner == 'X') {
		std::cout << "Player X has won!" << std::endl;
	} else if (winner == 'O') {
		std::cout << "Player O has won!" << std::endl;
	} else if (winner != 'X' && winner != 'O' && isFull()) {
		std::cout << "It's a tie!" << std::endl;
	}
}

bool Board::isFull () {
	int amount = 0;

	for (int i = 0;i < 9;i++) {
		if (boxes[i] != NULL) {
			amount++;
		}
	}

	if (amount == 9) {
		return true;
	} else {
		return false;
	}
}

void Board::clear () {
	for (int i = 0;i < sizeof (boxes);i++) {
		boxes[i] = NULL;
	}

	turn = 'X';
	winner = NULL;
}

Board::~Board () {}