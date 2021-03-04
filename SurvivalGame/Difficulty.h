#ifndef DIFFICULTY_H
#define DIFFICULTY_H

#include <string>

using namespace std;

class Difficulty {
private:
	int enemiesAllowed, trapsAllowed;
	string name;
protected:
	int difficultyValue;
public:
	Difficulty() {}
	Difficulty(string nameIn, int enemyCount, int trapCount) {
		this->name = nameIn;
		this->enemiesAllowed = enemyCount;
		this->trapsAllowed = trapCount;
	}

	int getEnemyCount() {
		return this->enemiesAllowed;
	}

	int getTrapCount() {
		return this->trapsAllowed;
	}
};
#endif