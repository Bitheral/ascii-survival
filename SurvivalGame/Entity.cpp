#include "Entity.h"
#include "Game.h"

void Entity::render() {
	if (this->getState()) { Console::setColour(this->colour, this->colour); }
	else { Console::setColour(this->deadColour, this->deadColour); }

	Console::setCursorPosition(this->currentPos.y, this->currentPos.x);
	cout << ' ';
}

void Entity::showHealth(string name, int x, int y, bool isAlive) {
	Console::setCursorPosition(y, x);
	string healthStr = name + " Healthbar";
	Console::setColour(Console::WHITE, Console::BLACK);
	cout << healthStr;
	Console::setCursorPosition(y, x + healthStr.length() + 2);
	if (isAlive) {
		for (int h = 0; h < this->health / 10; h++) {
			Console::setColour(this->colour, this->colour);
			cout << ' ';
		}

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
	if (this->getDistance(this->currentPos.x, x) > 0) {
		this->setPosition(x, this->currentPos.y);
	}
	else if (this->getDistance(this->currentPos.x, x + width) < 0) {
		this->setPosition(x + width, this->currentPos.y);
	}
	else if (this->getDistance(this->currentPos.y, y) > 0) {
		this->setPosition(this->currentPos.x, y);
	}
	else if (this->getDistance(this->currentPos.y, y + height) < 0) {
		this->setPosition(this->currentPos.x, y + height);
	}
}

void Entity::clearSpace(bool inArea) {
	if (this->lastPos.x == this->currentPos.x && this->lastPos.y == this->currentPos.y) {
		return;
	} else {
		Console::setCursorPosition(this->lastPos.y, this->lastPos.x);
		if (inArea) { Console::setColour(Console::GREEN, Console::GREEN); }
		else { Console::setColour(Console::BLACK, Console::BLACK); }
		cout << ' ';
	}
}

bool Entity::inArea(Position position, int x, int y, int width, int height) {
	bool isXInArea = x <= position.x;
	bool isWidthInArea = position.x <= (x + width);
	bool isYInArea = y <= position.y;
	bool isHeightInArea = position.y <= (y + height);

	return (isXInArea && isWidthInArea) && (isYInArea && isHeightInArea);
}

void Entity::setPosition(int x, int y) {
	this->lastPos.x = this->currentPos.x;
	this->lastPos.y = this->currentPos.y;
	this->currentPos.x = x;
	this->currentPos.y = y;
}

void Entity::decreaseHealth(int amount) { 
	this->health = this->health - amount;
	if (this->health <= 0) { this->setState(false); }
}

void Entity::regenerateHealth(int amount) {
	this->health = this->health + amount;
	if (this->health >= 100) { this->health = 100; }
}

int Entity::getDistance(int from, int to) { return to - from; }
void Entity::Move(int x, int y) { this->setPosition(this->currentPos.x + x, this->currentPos.y + y); }

Console::COLOUR Entity::getColour() { return this->colour; }
void Entity::setColour(Console::COLOUR colour) { this->colour = colour; }

Console::COLOUR Entity::getDeadColour() { return this->deadColour; }
void Entity::setDeadColour(Console::COLOUR colour) { this->deadColour = colour; }

Position Entity::getLastPosition() { return this->lastPos; }
Position Entity::getPosition() { return this->currentPos; }

void Entity::setState(bool stateIn) { this->state = stateIn; }
bool Entity::getState() { return this->state; }

int Entity::getHealth() { return this->health; }