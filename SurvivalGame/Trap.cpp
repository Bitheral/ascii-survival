#include "Trap.h"

Trap::Trap() {
	this->setColour(Console::BLACK);
}

Trap::Trap(int x, int y) : Trap() {
	this->setPosition(x, y);
}