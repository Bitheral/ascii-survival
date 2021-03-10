#include "Game.h"

Game::Game() {}

Game::Game(int width, int height, Difficulty difficultyIn) {
	this->difficulty = difficultyIn;

	this->mapWidth = width * 2;
	this->mapHeight = height;
	this->mapOffsetX = (this->mapWidth / 2);
	this->mapOffsetY = (this->mapHeight / 2);

	this->mapArea[0] = this->mapOffsetX;
	this->mapArea[1] = this->mapWidth;
	this->mapArea[2] = this->mapOffsetY;
	this->mapArea[3] = this->mapHeight;

	this->running = true;

	int playerX = rand() % this->mapWidth;
	int playerY = rand() % this->mapHeight;
	this->player = Player(playerX + this->mapOffsetX, playerY + this->mapOffsetY);

	for (int e = 0; e < this->difficulty.getEnemyCount(); e++) {
		int enemyX = rand() % this->mapWidth;
		int enemyY = rand() % this->mapHeight;
		enemies.push_back(Enemy(enemyX + this->mapOffsetX, enemyY + this->mapOffsetY));
	}

	for (int t = 0; t < this->difficulty.getTrapCount(); t++) {
		int trapX = rand() % this->mapWidth;
		int trapY = rand() % this->mapHeight;
		traps.push_back(Trap(trapX + this->mapOffsetX, trapY + this->mapOffsetY));
	}
}

void Game::drawMap() {
	for (int y = 0; y <= this->mapHeight; y++) {
		for (int x = 0; x <= this->mapWidth; x++) {
			Console::setCursorPosition(y + this->mapOffsetY, x + this->mapOffsetX);
			Console::setColour(this->mapColour, this->mapColour);
			cout << this->mapChar;
		}
		cout << endl;
	}
}

void Game::render() {
	
	this->player.render();
	this->player.clearSpace(this->player.inArea(this->player.getPreviousPosition(), this->mapOffsetX, this->mapOffsetY, this->mapWidth, this->mapHeight));

	for (int e = 0; e < this->enemies.size(); e++) {
		this->enemies[e].render();
	}

	for (int t = 0; t < this->traps.size(); t++) {
		this->traps[t].render();
	}
}

void Game::update() {
	
	if (this->player.inArea(this->player.getPosition(), this->mapOffsetX, this->mapOffsetY, this->mapWidth, this->mapHeight)) {
		this->player.update();
	}
	else {
		this->player.contain(this->mapOffsetX, this->mapOffsetY, this->mapWidth, this->mapHeight);
	}
}

bool Game::isRunning() {
	return this->running;
}


Console::COLOUR Game::getColour() {
	return this->mapColour;
}

char Game::getFloorChar() {
	return this->mapChar;
}