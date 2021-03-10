#ifndef ENTITY_H
#define ENTITY_H


#include <iostream>;
#include "console.h";

using namespace std;

class Entity {
protected:
	int position[2] = { 0, 0 };
	int prevPosition[2] = { 0, 0 };
	char character = '?';
	Console::COLOUR colour;
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

	char getCharacter();
	void setCharacter(char);

	int* getPosition();
	void setPosition(int x, int y);

	int* getPreviousPosition();
};

#endif

