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
	char mapChar = ' ';
	Console::COLOUR mapColour = Console::GREEN;

	Difficulty difficulty;

	Player player;
	vector<Enemy> enemies;
	vector<Trap> traps;

	chrono::steady_clock::time_point gameStart;

	ofstream logFile;

	bool running;

public:
	Game();
	Game(int, int, Difficulty);

	void drawMap();
	void render();
	void update();
	void log(string);
	void stopLogging();

	bool isRunning();
	char getFloorChar();
	Player getPlayer();
	Console::COLOUR getColour();
};

#endif