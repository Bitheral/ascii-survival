#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
class Player : public Entity {

public:
	Player();
	Player(int, int);

	void update();
};

#endif