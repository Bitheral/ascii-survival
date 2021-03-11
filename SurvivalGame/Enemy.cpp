#include "Enemy.h"

#include <cmath>

Enemy::Enemy() {
    this->setCharacter('E');
    this->setColour(Console::RED);
}

Enemy::Enemy(int x, int y) : Enemy() {
    this->setPosition(x, y);
}

bool Enemy::in_range(Entity other) {
    int xDistance = pow(this->position[0] - other.getPosition()[0], 2);
    int yDistance = pow(this->position[1] - other.getPosition()[1], 2);
    return sqrt(xDistance + yDistance) <= this->range_radius * 2;
}

void Enemy::follow(int mapWidth, int mapHeight, Entity player) {

    int dx = player.getPosition()[0] - this->position[0];
    int dy = player.getPosition()[1] - this->position[1];
    bool moveXAxis;
    if (abs(dx) <= mapWidth && abs(dy) <= mapHeight) {
        moveXAxis = abs(dx) > abs(dy);
    }

    if (abs(dx) > 1 && abs(dy) > 1) {
        moveXAxis = rand() % 1;
    }
    
    if (moveXAxis) {
        this->Move(min(dx, -1) ? dx > 0 : max(dx, 1), 0);
    }
    else {
        this->Move(0, min(dy, -1) ? dx > 0 : max(dy, 1));
    }
}