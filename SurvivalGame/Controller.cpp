#include "Controller.h"
#include "Game.h"

void Controller::start() {
	const Difficulty EASY = Difficulty("Easy", 5, 4);
	const Difficulty MEDIUM = Difficulty("Medium", 10, 8);
	const Difficulty HARD = Difficulty("Hard", 15, 12);

	Game game = Game(15, 15, EASY);

	game.drawMap();

	while (game.isRunning()) {
		game.render();
		game.update();
	}

	Console::setCursorPosition(20, 0);
}