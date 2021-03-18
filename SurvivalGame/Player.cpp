#include <conio.h>

#include "Player.h"

Player::Player() { 
	this->setColour(Console::WHITE);
	this->setDeadColour(Console::GRAY);
}

// Initialize player with desired position
Player::Player(int x, int y) : Player() { this->setPosition(x, y); }

void Player::update() {

	// Get key pressed
	char key = _getch();
	switch (key) {
		// Move up if W or Up Arrow pressed
		case 'W':
		case 'w':
		case 72:
			this->Move(0, -1);
			break;
		// Move down if S or Down Arrow pressed
		case 'S':
		case 's':
		case 80:
			this->Move(0, 1);
			break;
		// Move left if A or Left Arrow pressed
		case 'A':;
		case 'a':
		case 75:
			this->Move(-1, 0);
			break;
		// Move right if D or Right Arrow pressed
		case 'D':;
		case 'd':
		case 77:
			this->Move(1, 0);
			break;
		// Set quit to true if Q pressed
		case 'Q':
		case 'q':
			this->quit = true;
			break;
		// Set hitting to true if E pressed
		case 'E':
		case 'e':
			this->hitting = true;
			break;
	}
}

// Setters and Getters
void Player::setHitting(bool hit) { this->hitting = hit; }
bool Player::isHitting() { return this->hitting; }

bool Player::doQuit() { return this->quit; }