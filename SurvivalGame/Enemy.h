#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
class Enemy : public Entity {
private:
	int rangeRadius = 2;
public:
	Enemy();
	Enemy(int, int);

	bool inRange(Entity);
	void follow(Entity);
};

#endif