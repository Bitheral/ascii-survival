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

Game::Game(int width, int height, Difficulty difficultyIn) {
	srand(static_cast<unsigned int>(time(0)));

	this->difficulty = difficultyIn;

	if (width >= 21) { this->mapWidth = 42; }
	else if (width <= 18) { this->mapWidth = 38; }
	else { this->mapWidth = width * 2; }

	if (height >= 21) { this->mapHeight = 21; }
	else if (height <= 18) { this->mapHeight = 18; }
	else { this->mapHeight = height; }
	
	this->mapOffsetX = (Console::getTextBufferSize().X / 2) - (this->mapWidth / 2);
	this->mapOffsetY = 1;

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
			cout << ' ';
		}
		cout << endl;
	}
}

void Game::showControls() {
	Console::setColour(Console::WHITE, Console::BLACK);
	const int CONTROLS_COUNT = 3;
	string controls[CONTROLS_COUNT] = {
		"W, A, S, D - Move",
		"E - Hit Enemy",
		"Q - Quit"
	};
	Console::setCursorPosition((32 - CONTROLS_COUNT) - 2, 0);
	for (int c = 0; c < CONTROLS_COUNT; c++) {
		cout << controls[c] << endl;
	}
}

void Game::render() {
	
	if (this->player.getState()) {
		this->player.render();
		this->player.clearSpace(this->player.inArea(this->player.getLastPosition(), this->mapOffsetX, this->mapOffsetY, this->mapWidth, this->mapHeight));
		this->player.showHealth("Player", 2, this->mapOffsetY, this->player.getState());
	}

	for (int e = 0; e < this->enemies.size(); e++) {
		Enemy &enemy = this->enemies[e];
		enemy.render();
		if (enemy.getState()) {
			enemy.clearSpace(enemy.inArea(enemy.getLastPosition(), this->mapOffsetX, this->mapOffsetY, this->mapWidth, this->mapHeight));
		}

		if (enemy.getPosition().x == this->player.getPosition().x &&
			enemy.getPosition().y == this->player.getPosition().y) {
			enemy.showHealth("Enemy", 2, this->mapOffsetY + 1, enemy.getState());
		}
	}

	for (int t = 0; t < this->traps.size(); t++) { this->traps[t].render(); }
	Console::setCursorPosition(this->player.getPosition().y, this->player.getPosition().x);
}

void Game::update() {
	if (this->player.getState()) {
		if (this->player.inArea(this->player.getPosition(), this->mapOffsetX, this->mapOffsetY, this->mapWidth, this->mapHeight)) {
			this->player.update();
			this->player.regenerateHealth(1);
		}
		else { this->player.contain(this->mapOffsetX, this->mapOffsetY, this->mapWidth, this->mapHeight); }
	} else {
		this->playerWon = false;
		this->running = false;
	}

	for (int e = 0; e < this->enemies.size(); e++) {
		Enemy &enemy = this->enemies[e];
		if (enemy.getState()) {
			if (enemy.inArea(enemy.getPosition(), this->mapOffsetX, this->mapOffsetY, this->mapWidth, this->mapHeight)) {
				if (enemy.in_range(this->player)) {
					if (enemy.getPosition().x == this->player.getPosition().x &&
						enemy.getPosition().y == this->player.getPosition().y) {
						if (this->player.isHitting()) {
							enemy.decreaseHealth(2);
							this->player.setHitting(false);
						}
						this->player.decreaseHealth(2);
					} else {
						enemy.regenerateHealth(1);
						enemy.follow(this->player);
					}
				}
			} else { enemy.contain(this->mapOffsetX, this->mapOffsetY, this->mapWidth, this->mapHeight); }
		}
	}

	for (int t = 0; t < this->traps.size(); t++) {
		Trap &trap = this->traps[t];
		if (trap.getPosition().x == this->player.getPosition().x &&
			trap.getPosition().y == this->player.getPosition().y) {
			this->player.setState(false);
		}

		for (int e = 0; e < this->enemies.size(); e++) {
			Enemy &enemy = this->enemies[e];
			if(enemy.getState()) {
				if (enemy.getPosition().x == trap.getPosition().x &&
					enemy.getPosition().y == trap.getPosition().y) {
					enemy.setState(false);
				}
			}
		}
	}
	int enemiesKilled = 0;
	for(int e = 0; e < this->enemies.size(); e++) {
		if (!this->enemies[e].getState()) { enemiesKilled += 1;}
		this->killedEnemies = enemiesKilled;
	}

	if (this->killedEnemies == this->enemies.size()) {
		this->playerWon = true;
		this->running = false;
	}
}

void Game::log(string playername, bool hasQuit) {
	string result = this->playerWon ? "Won" : "Lost";
	if(!hasQuit) { this->logFile << "[" << getCurrentDateTime() << "] [" << playername << "] " << "You " << result << "! "  << this->killedEnemies << " Enemies killed" << endl; }
	else { this->logFile << "[" << getCurrentDateTime() << "] [" << playername << "] " << this->killedEnemies << " Enemies killed (Player quit)" << endl; }
}

void Game::stopLogging() { this->logFile.close(); }
bool Game::isRunning() { return this->running; }
bool Game::hasPlayerWon() { return this->playerWon; }
Console::COLOUR Game::getColour() { return this->mapColour; }
Player Game::getPlayer() { return this->player; }
int Game::getKilledEnemies() { return this->killedEnemies; }