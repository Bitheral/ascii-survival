#include "Game.h"
#include <ctime>
#include <cstdlib>

string getCurrentDateTime() {

	// Code taken from
	// https://stackoverflow.com/a/3673291
	// 
	// Adjusted code to use localtime_s
	// due to security flaws
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


	// Due to rendering errors, limit was required
	// Disallow user to have too small of grid since
	// player will most likely die instantly, and disallow
	// grid to be too large due to render error
	if (width >= 21) { this->mapWidth = 42; }
	else if (width <= 18) { this->mapWidth = 38; }
	else { this->mapWidth = width * 2; }

	if (height >= 21) { this->mapHeight = 21; }
	else if (height <= 18) { this->mapHeight = 18; }
	else { this->mapHeight = height; }
	
	// Position grid on Console
	this->mapOffsetX = (Console::getTextBufferSize().X / 2) - (this->mapWidth / 2);
	this->mapOffsetY = 1;

	this->running = true;
	
	this->logFile.open("results.txt", ios::out | ios::app);

	int playerX = rand() % this->mapWidth;
	int playerY = rand() % this->mapHeight;
	this->player = Player(playerX + this->mapOffsetX, playerY + this->mapOffsetY);

	// Create enemies depending on difficulty settings
	for (int e = 0; e < this->difficulty.getEnemyCount(); e++) {
		int enemyX = rand() % this->mapWidth;
		int enemyY = rand() % this->mapHeight;
		enemies.push_back(Enemy(enemyX + this->mapOffsetX, enemyY + this->mapOffsetY));
	}

	// Create traps depending on difficulty settings
	for (int t = 0; t < this->difficulty.getTrapCount(); t++) {
		int trapX = rand() % this->mapWidth;
		int trapY = rand() % this->mapHeight;
		traps.push_back(Trap(trapX + this->mapOffsetX, trapY + this->mapOffsetY));
	}
}

void Game::drawMap() {
	// Render 2D grid
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
		"WASD or Arrow keys - Move",
		"E - Hit Enemy",
		"Q - Quit"
	};
	Console::setCursorPosition((32 - CONTROLS_COUNT) - 2, 0);
	for (int c = 0; c < CONTROLS_COUNT; c++) {
		cout << controls[c] << endl;
	}
}

void Game::render() {
	
	// Only render player if alive
	if (this->player.getState()) {
		this->player.render();
		this->player.clearSpace(this->player.inArea(this->player.getLastPosition(), this->mapOffsetX, this->mapOffsetY, this->mapWidth, this->mapHeight));
		this->player.showHealth("Player", 2, this->mapOffsetY);
	}

	for (int e = 0; e < this->enemies.size(); e++) {
		Enemy &enemy = this->enemies[e];
		enemy.render();

		// Only render clearSpace if enemy is alive
		// Rendering clearSpace when enemy is dead
		// causes player to 'disappear' if player 
		// position is on enemy last position
		if (enemy.getState()) {
			enemy.clearSpace(enemy.inArea(enemy.getLastPosition(), this->mapOffsetX, this->mapOffsetY, this->mapWidth, this->mapHeight));
		}

		// Render enemy's healthbar if the enemy
		// is in the same position as the player
		if (enemy.getPosition().x == this->player.getPosition().x &&
			enemy.getPosition().y == this->player.getPosition().y) {
			enemy.showHealth("Enemy", 2, this->mapOffsetY + 1);
		}
	}

	for (int t = 0; t < this->traps.size(); t++) { this->traps[t].render(); }
	Console::setCursorPosition(this->player.getPosition().y, this->player.getPosition().x);
}

void Game::update() {

	// Only update player if player is alive
	if (this->player.getState()) {
		// Check if player is in grid
		if (this->player.inArea(this->player.getPosition(), this->mapOffsetX, this->mapOffsetY, this->mapWidth, this->mapHeight)) {
			this->player.update();
			this->player.regenerateHealth(1);
		} else {
			// Player is not in grid, force player
			// back in grid
			this->player.contain(this->mapOffsetX, this->mapOffsetY, this->mapWidth, this->mapHeight); 
		}
	} else {
		// Player has died, end game
		this->playerWon = false;
		this->running = false;
	}

	for (int e = 0; e < this->enemies.size(); e++) {
		Enemy &enemy = this->enemies[e];

		// Only update enemy if enemy is alive
		if (enemy.getState()) {

			// Check if enemy is in grid
			if (enemy.inArea(enemy.getPosition(), this->mapOffsetX, this->mapOffsetY, this->mapWidth, this->mapHeight)) {

				// Move enemy towards player if 
				// player is within range of enemy
				if (enemy.inRange(this->player)) {

					// Hit player if enemy is in
					// same location as player
					if (enemy.getPosition().x == this->player.getPosition().x &&
						enemy.getPosition().y == this->player.getPosition().y) {

						// Decrease health due to playerHit
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
			} else { 

				// Enemy is not in grid
				// force enemy back in grid
				enemy.contain(this->mapOffsetX, this->mapOffsetY, this->mapWidth, this->mapHeight); 
			}
		}
	}

	for (int t = 0; t < this->traps.size(); t++) {
		Trap &trap = this->traps[t];

		// Kill player if player is
		// in same position as trap
		if (trap.getPosition().x == this->player.getPosition().x &&
			trap.getPosition().y == this->player.getPosition().y) {
			this->player.setState(false);
		}

		for (int e = 0; e < this->enemies.size(); e++) {
			Enemy &enemy = this->enemies[e];
			// Check if Enemy is alive
			if(enemy.getState()) {

				// Kill enemy if enemy is
				// in same position as trap
				if (enemy.getPosition().x == trap.getPosition().x &&
					enemy.getPosition().y == trap.getPosition().y) {
					enemy.setState(false);
				}
			}
		}
	}

	int enemiesKilled = 0;
	// Check how many enemies
	// have been killed and 
	// set killedEnemies to enemiesKilled
	for(int e = 0; e < this->enemies.size(); e++) {
		if (!this->enemies[e].getState()) { enemiesKilled += 1;}
		this->killedEnemies = enemiesKilled;
	}


	// Player won if the amount of
	// killedEnemies is the same as
	// enemies vector size
	if (this->killedEnemies == this->enemies.size()) {
		this->playerWon = true;
		this->running = false;
	}
}

void Game::log(string playername, bool hasQuit) {
	string result = this->playerWon ? "Won" : "Lost";
	if(!hasQuit) {
		// Output to logfile how many enemies killed, with the playername
		this->logFile << "[" << getCurrentDateTime() << "] [" << playername << "] " << "You " << result << "! "  << this->killedEnemies << " Enemies killed" << endl;
	} else {
		// Output to logfile how many enemies killed before game quit with playername
		this->logFile << "[" << getCurrentDateTime() << "] [" << playername << "] " << this->killedEnemies << " Enemies killed (Player quit)" << endl; 
	}
}
void Game::stopLogging() { this->logFile.close(); }

// Getters
bool Game::isRunning() { return this->running; }
bool Game::hasPlayerWon() { return this->playerWon; }
Console::COLOUR Game::getColour() { return this->mapColour; }
Player Game::getPlayer() { return this->player; }
int Game::getKilledEnemies() { return this->killedEnemies; }