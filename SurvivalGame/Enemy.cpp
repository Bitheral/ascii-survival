#include "Enemy.h"

#include <cmath>

Enemy::Enemy() {
    this->setColour(Console::LIGHT_RED);
    this->setDeadColour(Console::RED);
}

Enemy::Enemy(int x, int y) : Enemy() {
    this->setPosition(x, y);
}

bool Enemy::in_range(Entity other) {
    int xDistance = pow(this->currentPos.x - other.getPosition().x, 2);
    int yDistance = pow(this->currentPos.y - other.getPosition().y, 2);
    return sqrt(xDistance + yDistance) <= this->range_radius * 2;
}

void Enemy::follow(Entity other) {

    int xDist = this->currentPos.x - other.getPosition().x;
    int xDistSq = pow(xDist, 2);

    int yDist = this->currentPos.y - other.getPosition().y;
    int yDistSq = pow(yDist, 2);

    int distanceSq = xDistSq + yDistSq;
    int distance = sqrt(distanceSq);

    bool shouldMoveX;

    int less = -1;
    int more = 1;

    int moveBy = 0;

    shouldMoveX = abs(xDist) > abs(yDist);

    if (shouldMoveX) {
        if (xDist > 0) {
            moveBy = -1;
        }
        else if (xDist < 0) {
            moveBy = 1;
        }

        this->Move(moveBy, 0);
    }
    else {
        if (yDist > 0) {
            moveBy = -1;
        }
        else if (yDist < 0) {
            moveBy = 1;
        }

        this->Move(0, moveBy);
    }
}