#include <conio.h>

#include "Player.h"

Player::Player() { 
	this->setColour(Console::WHITE);
	this->setDeadColour(Console::GRAY);
}
Player::Player(int x, int y) : Player() { this->setPosition(x, y); }

void Player::update() {

	char key = _getch();
	switch (key) {
	case 'W':
	case 'w':
	case 72:
		this->Move(0, -1);
		break;
	case 'S':
	case 's':
	case 80:
		this->Move(0, 1);
		break;
	case 'A':;
	case 'a':
	case 75:
		this->Move(-1, 0);
		break;
	case 'D':;
	case 'd':
	case 77:
		this->Move(1, 0);
		break;
	case 'Q':
	case 'q':
		this->quit = true;
		break;
	case 'E':
	case 'e':
		this->hitting = true;
		break;
	}
}

bool Player::doQuit() { return this->quit; }

void Player::setHitting(bool hit) { this->hitting = hit; }
bool Player::isHitting() { return this->hitting; }