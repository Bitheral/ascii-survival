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
	for (int y = 0; y < this->mapHeight; y++) {
		for (int x = 0; x < this->mapWidth; x++) {
			Console::setCursorPosition(y + this->mapOffsetY, x + this->mapOffsetX);
			cout << this->mapChar;
		}
		cout << endl;
	}
}

void Game::render() {

	this->player.render();

	/*for (int e = 0; e < this->enemies.size(); e++) {
		this->enemies[e].render();
	}

	for (int t = 0; t < this->traps.size(); t++) {
		this->traps[t].render();
	}*/
}

void Game::update() {

	this->player.update();

	for (int e = 0; e < this->enemies.size(); e++) {
		if (this->enemies[e].in_range(this->player)) {
			this->enemies[e].follow(this->mapWidth, this->mapHeight, this->player);
		}
	}

	for (int t = 0; t < this->traps.size(); t++) {
		int trapX = this->traps[t].getPosition()[0];
		int trapY = this->traps[t].getPosition()[1];

		int playerX = this->player.getPosition()[0];
		int playerY = this->player.getPosition()[1];

		bool trapPlayerX = trapX == playerX;
		bool trapPlayerY = trapY == playerY;

		if (trapPlayerX && trapPlayerY) {
			Console::setCursorPosition(30, 0);
			cout << "Player should die";
		}

		for (int e = 0; e < this->enemies.size(); e++) {
			int enemyX = this->enemies[e].getPosition()[0];
			int enemyY = this->enemies[e].getPosition()[1];

			bool enemyTrapX = trapX == enemyX;
			bool enemyTrapY = trapY == enemyY;

			if (enemyTrapX && enemyTrapY) {
				this->enemies.erase(this->enemies.begin() + e);
				Console::setCursorPosition(32, 0);
				cout << "Enemy died";
			}
		}
	}
}

bool Game::isRunning() {
	return this->running;
}

char Game::getFloorChar() {
	return this->mapChar;
}