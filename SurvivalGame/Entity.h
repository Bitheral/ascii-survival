#ifndef ENTITY_H
#define ENTITY_H


#include <iostream>;
#include "console.h";

using namespace std;

class Entity {
protected:
	int position[2] = { 0, 0 };
	int prevPosition[2] = { 0, 0 };
	Console::COLOUR colour;
	int state = true;
public:
	void render();
	void update();

	void Move(int, int);
	void contain(int, int, int, int);
	void clearSpace(bool);
	
	bool inArea(int*, int, int, int, int);

	int getDistance(int, int);

	Console::COLOUR getColour();
	void setColour(Console::COLOUR);

	int* getPosition();
	void setPosition(int x, int y);

	int* getPreviousPosition();

	void setState(bool);
	bool getState();
};

#endif

