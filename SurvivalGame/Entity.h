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
	Position currentPos = { 0, 0 }, lastPos = { 0, 0 };
	Console::COLOUR colour, deadColour;
	bool state = true;
	int maxHealth = 100;
	int health = maxHealth;

public:

	// Rendering functions
	void render();
	void showHealth(string, int, int, bool);
	void clearSpace(bool);

	// Distance-related functions
	void Move(int, int);
	int getDistance(int, int);

	// Grid collision function
	void contain(int, int, int, int);
	bool inArea(Position, int, int, int, int);

	/* Getters and setters */
	/***********************/
	Console::COLOUR getColour();
	void setColour(Console::COLOUR);

	Console::COLOUR getDeadColour();
	void setDeadColour(Console::COLOUR);

	void setPosition(int x, int y);
	Position getPosition();
	Position getLastPosition();

	void setState(bool);
	bool getState();

	void decreaseHealth(int);
	void regenerateHealth(int);
	int getHealth();
	/***********************/

};

#endif

