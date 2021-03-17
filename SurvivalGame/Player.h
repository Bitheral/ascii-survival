#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
class Player : public Entity {
private:
	bool quit = false;
	bool hitting = false;
public:
	Player();
	Player(int, int);

	void update();

	// Setters
	void setHitting(bool);

	// Getters
	bool isHitting();
	bool doQuit();
};

#endif