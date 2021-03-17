#ifndef GAME_H
#define GAME_H

#include <vector>
#include <fstream>
#include <chrono>
#include <string>

#include "console.h"
#include "Difficulty.h"
#include "Enemy.h"
#include "Player.h"
#include "Trap.h"
using namespace std;

class Game {
private:
	int mapWidth, mapHeight, mapOffsetX, mapOffsetY;
	Console::COLOUR mapColour = Console::GREEN;

	Difficulty difficulty;

	Player player;
	vector<Enemy> enemies;
	vector<Trap> traps;

	int killedEnemies;

	chrono::steady_clock::time_point gameStart;

	ofstream logFile;

	bool running;
	bool playerWon;

public:
	Game();
	Game(int, int, Difficulty);

	void drawMap();
	void showControls();
	void render();
	void update();
	void log(string, bool);
	void stopLogging();

	bool isRunning();
	bool hasPlayerWon();
	Player getPlayer();

	Console::COLOUR getColour();
	int getKilledEnemies();
};

#endif