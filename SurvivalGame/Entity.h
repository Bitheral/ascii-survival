#pragma once

#include <iostream>;
#include "console.h";

using namespace std;

class Entity {
protected:
	int position[2] = { 0, 0 };
	int prevPosition[2] = { 0, 0 };
	char character = '?';
public:
	void render();
	void update();

	void Move(int, int);

	bool* in_area(int, int, int, int);
	bool* in_area(int*);

	char getCharacter();
	void setCharacter(char);

	int* getPosition();
	void setPosition(int x, int y);

	int* getPreviousPosition();
};

