#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
class Enemy : public Entity {
private:
	int range_radius = 2;
	double speed = 0.25;
public:
	Enemy();
	Enemy(int, int);

	bool in_range(Entity);
	void follow(int, int, Entity);
};

#endif