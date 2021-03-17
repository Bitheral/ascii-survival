#ifndef DIFFICULTY_H
#define DIFFICULTY_H

#include <string>

using namespace std;

class Difficulty {
private:
	int enemiesAllowed, trapsAllowed;
	string name;
public:
	Difficulty();
	Difficulty(string nameIn, int enemyCount, int trapCount);

	int getEnemyCount();
	int getTrapCount();
	string getName();
};
#endif