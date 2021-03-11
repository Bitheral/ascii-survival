#include "Game.h"
#include <ctime>
#include <cstdlib>

string getCurrentDateTime() {

	time_t rawtime = time(NULL);
	struct tm timeinfo;
	char buffer[80];
	errno_t err;

	time(&rawtime);
	err = localtime_s(&timeinfo, &rawtime);

	strftime(buffer, sizeof(buffer), "%d-%m-%Y %H-%M-%S", &timeinfo);
	string str(buffer);
	return str;

}

Game::Game() {}

Game::Game(int width, int height, Difficulty difficultyIn) {
	this->gameStart = chrono::steady_clock::now();
	srand(static_cast<unsigned int>(time(0)));

	this->difficulty = difficultyIn;

	this->mapWidth = width * 2;
	this->mapHeight = height;
	this->mapOffsetX = (Console::getTextBufferSize().X / 2) - (this->mapWidth / 2);
	this->mapOffsetY = (Console::getTextBufferSize().Y / 5) - (this->mapHeight / 2);

	this->running = true;
	
	this->logFile.open("results.txt", ios::out | ios::app);

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
		Enemy enemy = this->enemies[e];
		enemy.render();
		enemy.clearSpace(enemy.inArea(enemy.getPreviousPosition(), this->mapOffsetX, this->mapOffsetY, this->mapWidth, this->mapHeight));
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
		this->log("Player tried to escape grid");
		this->player.contain(this->mapOffsetX, this->mapOffsetY, this->mapWidth, this->mapHeight);
	}

	for (int e = 0; e < this->enemies.size(); e++) {
		Enemy enemy = enemies[0];
		enemy.follow(this->mapWidth, this->mapHeight, this->player);
		Console::setCursorPosition(26, 0);
		Console::setColour(Console::BLACK, Console::WHITE);
		cout << "                                                " << endl << "                                       ";
		Console::setCursorPosition(26, 0);
		cout << "Enemy 0 pos: " << enemy.getPosition()[0] << ", " << enemy.getPosition()[1] << endl;
		cout << "Player pos: " << this->player.getPosition()[0] << ", " << this->player.getPosition()[1];
	}

	/*if(!this->player.getState()) {
		
	}*/

	if (this->player.doQuit()) {
	}
}

void Game::log(string message) {
	this->logFile << "[ " << getCurrentDateTime() << " ] " << message << endl;
}

void Game::stopLogging() {
	this->logFile.close();
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

Player Game::getPlayer() {
	return this->player;
}