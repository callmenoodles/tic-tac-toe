#include "GameManager.h"
#include <iostream>
#include <SDL_image.h>

GameManager::GameManager () {
	std::cout << "Choose your gamemode: \n" << std::endl;
	std::cout << "1. Player vs Player \n" << 
				 "2. Player vs AI (Easy) \n" << 
				 "3. Player vs AI (Normal) \n" << 
				 "4. Player vs AI (Impossible)" << std::endl;

	std::cin >> gamemode;
	
	init ();
}

void GameManager::init () {

	if (SDL_Init (SDL_INIT_EVERYTHING) < 0) {
		close ();
	}

	_window = SDL_CreateWindow ("Tic-Tac-Toe",
								SDL_WINDOWPOS_CENTERED,
								SDL_WINDOWPOS_CENTERED,
								SCREEN_W, SCREEN_H,
								SDL_WINDOW_SHOWN);

	if (_window == NULL) {
		printf ("Failed to create window: %s\n", SDL_GetError());
		close ();
	}

	_renderer = SDL_CreateRenderer (_window, -1, SDL_RENDERER_PRESENTVSYNC);
	
	if (_renderer == NULL) {
		printf ("Failed to create renderer: %s\n", SDL_GetError ());
		close ();
	}

	_texture = SDL_CreateTexture (_renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STATIC, SCREEN_W, SCREEN_H);

	if (_texture == NULL) {
		printf ("Failed to create texture: %s\n", SDL_GetError ());
		close ();
	}

	_buffer = new Uint32[SCREEN_SIZE];
	SDL_memset (_buffer, 0, SCREEN_SIZE * sizeof(Uint32));

	if (IMG_Init (IMG_INIT_PNG) != IMG_INIT_PNG) {
		printf ("Failed to initialize image: %s\n", SDL_GetError ());
	}

	// Board
	for (int i = 0;i < sizeof (board.boxes) / sizeof (char);i++) {
		players.push_back (new Player);
		players[i]->loadTexture ((std::string) "../deps/res/Cross.png", _renderer);

		AIs.push_back (new AI);
		AIs[i]->loadTexture ((std::string) "../deps/res/Circle.png", _renderer);
	}

	board.size = SCREEN_W - board.PADDING*2;
	board.box_size = board.size/3;
	
	for (int i = 0;i < players.size ();i++) {
		players[i]->size = board.box_size - board.PADDING;
		AIs[i]->size = board.box_size - board.PADDING;
	}
}

void GameManager::processEvents () {
	SDL_Event evnt;

	while (SDL_PollEvent (&evnt) == 1) {

		if (evnt.type == SDL_QUIT || evnt.key.keysym.sym == SDLK_ESCAPE) {
			close ();
			break;
		} 

		char X = 'X';
		char O = 'O';

		if (board.turn == 'X' && !board.isFull() && board.boxes[board.processEvents (evnt)-1] == NULL) {
			board.setBox (board.processEvents (evnt)-1, X);
			positionPlayer ();

			if (evnt.type == SDL_MOUSEBUTTONDOWN) {
				if (evnt.button.button == SDL_BUTTON_LEFT) {
					board.switchTurn ();
				}
			}
		} else if (board.turn == 'O' && gamemode == 1 && !board.isFull() && board.boxes[board.processEvents (evnt)-1] == NULL) {
			board.setBox (board.processEvents (evnt)-1, O);
			positionPlayer ();

			if (evnt.type == SDL_MOUSEBUTTONDOWN) {
				if (evnt.button.button == SDL_BUTTON_LEFT) {
					board.switchTurn ();
				}
			}
		}

		if (board.winner != NULL || board.isFull()) {
			board.processEvents (evnt);
		}
	} 
}

void GameManager::positionPlayer () {

	if (board.boxes[0] == 'X') {
		players[0]->_x = board.PADDING + board.PADDING/2;
		players[0]->_y = board.PADDING + board.PADDING/2;
	} else if (board.boxes[0] == 'O') {
		AIs[0]->_x = board.PADDING + board.PADDING/2;
		AIs[0]->_y = board.PADDING + board.PADDING/2;
	}

	if (board.boxes[1] == 'X') {
		players[1]->_x = board.PADDING + board.PADDING/2 + board.box_size;
		players[1]->_y = board.PADDING + board.PADDING/2;
	} else if (board.boxes[1] == 'O') {
		AIs[1]->_x = board.PADDING + board.PADDING/2 + board.box_size;
		AIs[1]->_y = board.PADDING + board.PADDING/2;
	}

	if (board.boxes[2] == 'X') {
		players[2]->_x = board.PADDING + board.PADDING/2 + board.box_size*2;
		players[2]->_y = board.PADDING + board.PADDING/2;
	} else if (board.boxes[2] == 'O') {
		AIs[2]->_x = board.PADDING + board.PADDING/2 + board.box_size*2;
		AIs[2]->_y = board.PADDING + board.PADDING/2;
	}

	if (board.boxes[3] == 'X') {
		players[3]->_x = board.PADDING + board.PADDING/2;
		players[3]->_y = board.PADDING + board.PADDING/2 + board.box_size;
	} else if (board.boxes[3] == 'O') {
		AIs[3]->_x = board.PADDING + board.PADDING/2;
		AIs[3]->_y = board.PADDING + board.PADDING/2 + board.box_size;
	}

	if (board.boxes[4] == 'X') {
		players[4]->_x = board.PADDING + board.PADDING/2 + board.box_size;
		players[4]->_y = board.PADDING + board.PADDING/2 + board.box_size;
	} else if (board.boxes[4] == 'O') {
		AIs[4]->_x = board.PADDING + board.PADDING/2 + board.box_size;
		AIs[4]->_y = board.PADDING + board.PADDING/2 + board.box_size;
	}

	if (board.boxes[5] == 'X') {
		players[5]->_x = board.PADDING + board.PADDING/2 + board.box_size*2;
		players[5]->_y = board.PADDING + board.PADDING/2 + board.box_size;
	} else if (board.boxes[5] == 'O') {
		AIs[5]->_x = board.PADDING + board.PADDING/2 + board.box_size*2;
		AIs[5]->_y = board.PADDING + board.PADDING/2 + board.box_size;
	}

	if (board.boxes[6] == 'X') {
		players[6]->_x = board.PADDING + board.PADDING/2;
		players[6]->_y = board.PADDING + board.PADDING/2 + board.box_size*2;
	} else if (board.boxes[6] == 'O') {
		AIs[6]->_x = board.PADDING + board.PADDING/2;
		AIs[6]->_y = board.PADDING + board.PADDING/2 + board.box_size*2;
	}

	if (board.boxes[7] == 'X') {
		players[7]->_x = board.PADDING + board.PADDING/2 + board.box_size;
		players[7]->_y = board.PADDING + board.PADDING/2 + board.box_size*2;
	} else if (board.boxes[7] == 'O') {
		AIs[7]->_x = board.PADDING + board.PADDING/2 + board.box_size;
		AIs[7]->_y = board.PADDING + board.PADDING/2 + board.box_size*2;
	}

	if (board.boxes[8] == 'X') {
		players[8]->_x = board.PADDING + board.PADDING/2 + board.box_size*2;
		players[8]->_y = board.PADDING + board.PADDING/2 + board.box_size*2;
	} else if (board.boxes[8] == 'O') {
		AIs[8]->_x = board.PADDING + board.PADDING/2 + board.box_size*2;
		AIs[8]->_y = board.PADDING + board.PADDING/2 + board.box_size*2;
	}
}
 
void GameManager::update () {
	board.scanWinner ();

	if (board.turn == 'O' && gamemode != 1 && !board.isFull() && board.winner == NULL) {
		char O = 'O';
		board.setBox (AIs[0]->assignPosition (board.boxes, board.elements, gamemode), O);
		positionPlayer ();
		board.turn = 'X';
	}

	SDL_RenderClear (_renderer);
	SDL_SetRenderDrawColor (_renderer, 10, 10, 10, 255);
	SDL_UpdateTexture (_texture, NULL, _buffer, SCREEN_W * sizeof (Uint32));

	draw ();

	SDL_RenderPresent (_renderer);
}

void GameManager::draw () {
	SDL_RenderClear (_renderer);
	SDL_SetRenderDrawColor (_renderer, 100, 100, 100, 255);

	board.draw (_renderer);

	for (int i = 0;i < sizeof (board.boxes)/sizeof (char);i++) {
		
		if (board.boxes[i] == 'X') {
			players[i]->draw (_renderer);
		} else if (board.boxes[i] == 'O') {
			AIs[i]->draw (_renderer);
		}
	}
}

void GameManager::close () {
	SDL_DestroyTexture (_texture);
	SDL_DestroyRenderer (_renderer);
	SDL_DestroyWindow (_window);
	delete[] _buffer;
	IMG_Quit ();
	SDL_Quit ();
	exit (1);
}

GameManager::~GameManager () {}
