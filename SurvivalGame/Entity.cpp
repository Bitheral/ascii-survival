#include "Entity.h"
#include "Game.h"

void Entity::render() {
	// If Entity is alive, render with Entity's colour
	// If not, render with Entity's deadColour
	if (this->getState()) { Console::setColour(this->colour, this->colour); }
	else { Console::setColour(this->deadColour, this->deadColour); }

	Console::setCursorPosition(this->currentPos.y, this->currentPos.x);
	cout << ' ';
}

void Entity::showHealth(string name, int x, int y) {
	string healthStr = name + " Healthbar";

	Console::setCursorPosition(y, x);
	Console::setColour(Console::WHITE, Console::BLACK);
	cout << healthStr;
	Console::setCursorPosition(y, x + healthStr.length() + 2);

	// If Entity is alive, render healthbar
	// If not render as blank
	if (this->getState()) {

		// Render health
		for (int h = 0; h < this->health / 10; h++) {
			Console::setColour(this->colour, this->colour);
			cout << ' ';
		}

		// Render damage taken
		for (int d = this->health / 10; d < this->maxHealth / 10; d++) {
			Console::setColour(this->deadColour, this->deadColour);
			cout << ' ';
		}
	}
	else {
		Console::setCursorPosition(y, x);
		for (int i = 0; i < x + healthStr.length() + 2 + this->maxHealth / 10; i++) {
			Console::setColour(Console::BLACK, Console::BLACK);
			cout << ' ';
		}
	}
}

void Entity::contain(int x, int y, int width, int height) {
	// Contain Entity within grid
	if (this->getDistance(this->currentPos.x, x) > 0) { this->setPosition(x, this->currentPos.y); }
	else if (this->getDistance(this->currentPos.x, x + width) < 0) { this->setPosition(x + width, this->currentPos.y); }
	else if (this->getDistance(this->currentPos.y, y) > 0) { this->setPosition(this->currentPos.x, y); }
	else if (this->getDistance(this->currentPos.y, y + height) < 0) { this->setPosition(this->currentPos.x, y + height); }
}

void Entity::clearSpace(bool inArea) {
	// Checks if the current position is equal to last
	// 	   
	// Causes bug where Entity doesn't get rendered due
	// to rendering Green space after Entity colour space
	if (this->lastPos.x == this->currentPos.x && this->lastPos.y == this->currentPos.y) { return; }
	else {
		Console::setCursorPosition(this->lastPos.y, this->lastPos.x);
		if (inArea) { Console::setColour(Console::GREEN, Console::GREEN); }
		else { Console::setColour(Console::BLACK, Console::BLACK); }
		cout << ' ';
	}
}

bool Entity::inArea(Position position, int x, int y, int width, int height) {

	// Checks if the current position is within
	// a certain area depending on x, y, width and height
	bool isXInArea = x <= position.x;
	bool isWidthInArea = position.x <= (x + width);
	bool isYInArea = y <= position.y;
	bool isHeightInArea = position.y <= (y + height);

	return (isXInArea && isWidthInArea) && (isYInArea && isHeightInArea);
}

void Entity::setPosition(int x, int y) {

	// Set the last position to current position
	// and set current position to x and y
	this->lastPos.x = this->currentPos.x;
	this->lastPos.y = this->currentPos.y;
	this->currentPos.x = x;
	this->currentPos.y = y;
}

void Entity::decreaseHealth(int amount) { 

	// Decrements health while the Entity's
	// health is more than 0, if Entity's
	// health is less or equal to 0, kill
	// entity
	this->health = this->health - amount;
	if (this->health <= 0) { this->setState(false); }
}

void Entity::regenerateHealth(int amount) {

	// Increments health while the Entity's
	// health is less than maxHealth, if Entity's
	// health is more or equal to maxHealth, set
	// health to maxHealth

	this->health = this->health + amount;
	if (this->health >= this->maxHealth) { this->health = this->maxHealth; }
}


int Entity::getDistance(int from, int to) { return to - from; }
void Entity::Move(int x, int y) {
	// Set the position with incremental movement
	// E.g Move(2,0) - Moves Entity 2 spaces right
	this->setPosition(this->currentPos.x + x, this->currentPos.y + y);
}

// Getters and Setters
Console::COLOUR Entity::getColour() { return this->colour; }
void Entity::setColour(Console::COLOUR colour) { this->colour = colour; }

Console::COLOUR Entity::getDeadColour() { return this->deadColour; }
void Entity::setDeadColour(Console::COLOUR colour) { this->deadColour = colour; }

Position Entity::getLastPosition() { return this->lastPos; }
Position Entity::getPosition() { return this->currentPos; }

void Entity::setState(bool stateIn) { this->state = stateIn; }
bool Entity::getState() { return this->state; }

int Entity::getHealth() { return this->health; }