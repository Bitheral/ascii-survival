#pragma once

#include <vector>

#include "console.h"
#include "Difficulty.h"
#include "Enemy.h"
#include "Player.h"
#include "Trap.h"
using namespace std;

class Game {
private:
	int mapWidth, mapHeight, mapOffsetX, mapOffsetY;
	int mapArea[4] = { 0, 0, 0, 0 };
	char mapChar = 180;

	Difficulty difficulty;

	Player player;
	vector<Enemy> enemies;
	vector<Trap> traps;

	bool running;

public:
	Game();
	Game(int, int, Difficulty);

	void drawMap();
	void render();
	void update();

	bool isRunning();
	char getFloorChar();
};

