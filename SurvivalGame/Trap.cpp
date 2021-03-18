#include "Trap.h"

Trap::Trap() { this->setColour(Console::BLACK); }

// Initialize trap with desired position
Trap::Trap(int x, int y) : Trap() { this->setPosition(x, y);  }