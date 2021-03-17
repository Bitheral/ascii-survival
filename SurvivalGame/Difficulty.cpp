#include "Difficulty.h"

Difficulty::Difficulty(string nameIn, int enemyCount, int trapCount) {
	this->name = nameIn;
	this->enemiesAllowed = enemyCount;
	this->trapsAllowed = trapCount;
}

int Difficulty::getEnemyCount() { return this->enemiesAllowed; }
int Difficulty::getTrapCount() { return this->trapsAllowed;  }
string Difficulty::getName() { return this->name; }