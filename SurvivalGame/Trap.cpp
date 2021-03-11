#include "Trap.h"

Trap::Trap() {
	this->setCharacter('T');
	this->setColour(Console::GRAY);
}

Trap::Trap(int x, int y) : Trap() {
	this->setPosition(x, y);
}