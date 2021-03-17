#ifndef ENTITY_H
#define ENTITY_H


#include <iostream>;
#include "console.h";

using namespace std;

struct Position {
	int x;
	int y;
};

class Entity {
protected:
	Position currentPos = { 0, 0 };
	Position lastPos = { 0, 0 };
	Console::COLOUR colour;
	Console::COLOUR deadColour;
	bool state = true;
	int maxHealth = 100;
	int health = maxHealth;

public:
	void render();

	void showHealth(string, int, int, bool);

	void Move(int, int);
	void contain(int, int, int, int);
	void clearSpace(bool);
	bool inArea(Position, int, int, int, int);

	void setPosition(int x, int y);

	int getDistance(int, int);

	Console::COLOUR getColour();
	void setColour(Console::COLOUR);

	Console::COLOUR getDeadColour();
	void setDeadColour(Console::COLOUR);

	Position getPosition();
	Position getLastPosition();

	void setState(bool);
	bool getState();

	void decreaseHealth(int);
	void regenerateHealth(int);
	int getHealth();

};

#endif

