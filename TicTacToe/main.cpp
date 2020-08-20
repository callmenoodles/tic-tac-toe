#define SDL_MAIN_HANDLED

#include "GameManager.h"
#include "Board.h"
#include <SDL.h>
#include <iostream>

int main () {

	GameManager game;
	
	while (true) {
		game.processEvents ();
		game.update ();
	}
	
	system ("pause");
	return 0;
}