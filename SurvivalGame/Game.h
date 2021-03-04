#ifndef GAME_H
#define GAME_H

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
	char mapChar = ' ';
	Console::COLOUR mapColour = Console::GREEN;

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
	Console::COLOUR getColour();
};

#endif