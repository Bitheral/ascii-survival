#include "Entity.h"
#include "Game.h"

void Entity::render() {
	Console::setColour(this->colour, this->colour);
	Console::setCursorPosition(this->position[1], this->position[0]);
	cout << this->getCharacter();
}

void Entity::contain(int x, int y, int width, int height) {
	int currentX = this->getPosition()[0];
	int currentY = this->getPosition()[1];

	if (this->getDistance(currentX, x) > 0) {
		this->setPosition(x, currentY);
	}
	else if (this->getDistance(currentX, x + width) < 0) {
		this->setPosition(x + width, currentY);
	}
	else if (this->getDistance(currentY, y) > 0) {
		this->setPosition(currentX, y);
	}
	else if (this->getDistance(currentY, y + height) < 0) {
		this->setPosition(currentX, y + height);
	}
}

void Entity::clearSpace(bool inArea) {

	int currentX = this->position[0];
	int currentY = this->position[1];
	int lastX = this->prevPosition[0];
	int lastY = this->prevPosition[1];

	Console::setCursorPosition(lastY, lastX);
	if (inArea) { Console::setColour(Console::GREEN, Console::GREEN); }
	else { Console::setColour(Console::BLACK, Console::BLACK); }
	cout << ' ';
}

void Entity::update() {

}

void Entity::Move(int x, int y) {
	int currentX = this->getPosition()[0];
	int currentY = this->getPosition()[1];

	this->setPosition(currentX + x, currentY + y);
}

bool Entity::inArea(int* position, int x, int y, int width, int height) {
	int posX = position[0];
	int posY = position[1];

	bool isXInArea = x <= posX;
	bool isWidthInArea = posX <= (x + width);
	bool isYInArea = y <= posY;
	bool isHeightInArea = posY <= (y + height);

	return (isXInArea && isWidthInArea) && (isYInArea && isHeightInArea);
}

int Entity::getDistance(int from, int to) {
	return to - from;
}

Console::COLOUR Entity::getColour() { return this->colour; }
void Entity::setColour(Console::COLOUR colour) { this->colour = colour;  }

char Entity::getCharacter() { return this->character; }
void Entity::setCharacter(char character) { this->character = character; }

int* Entity::getPreviousPosition() { return this->prevPosition; }

int* Entity::getPosition() { return this->position; }
void Entity::setPosition(int x, int y) {
	int currentX = this->getPosition()[0];
	int currentY = this->getPosition()[1];

	this->prevPosition[0] = currentX;
	this->prevPosition[1] = currentY;
	this->position[0] = x;
	this->position[1] = y;
}