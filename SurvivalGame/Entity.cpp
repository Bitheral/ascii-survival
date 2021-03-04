#include "Entity.h"
#include "Game.h"

void Entity::render() {
	Game* tempGame = new Game();
	Console::COLOUR gameColour = tempGame->getColour();
	Console::setColour(this->colour, this->colour);
	Console::setCursorPosition(this->position[1], this->position[0]);
	cout << this->getCharacter();
	Console::setColour(gameColour, gameColour);
	Console::setCursorPosition(this->prevPosition[1], this->prevPosition[0]);
	cout << tempGame->getFloorChar();
	Console::setCursorPosition(this->position[1], this->position[0]);
	delete tempGame;
}

bool* Entity::in_area(int x, int w, int y, int h) {
	int xPos = this->position[0];
	int yPos = this->position[1];
	bool inArea[2] = { true, true };

	if (xPos < x || xPos > x + w - 1) {
		inArea[0] = false;
	}

	if (yPos < y || yPos > y + h - 1) {
		inArea[1] = false;
	}

	return inArea;
}

bool* Entity::in_area(int* area) {
	int xPos = this->position[0];
	int yPos = this->position[1];
	bool inArea[2] = { true, true };

	if (xPos < area[0] || xPos > area[0] + area[1] - 1) {
		inArea[0] = false;
	}

	if (yPos < area[2] || yPos > area[2] + area[3] - 1) {
		inArea[1] = false;
	}

	return inArea;
}

void Entity::update() {

}

void Entity::Move(int x, int y) {
	int currentX = this->getPosition()[0];
	int currentY = this->getPosition()[1];

	this->setPosition(currentX + x, currentY + y);
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