#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
class Player : public Entity {
private:
	bool quit = false;
public:
	Player();
	Player(int, int);

	void update();
	bool doQuit();
};

#endif