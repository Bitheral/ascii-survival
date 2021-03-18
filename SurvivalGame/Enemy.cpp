#include "Enemy.h"

#include <cmath>

Enemy::Enemy() {
    this->setColour(Console::LIGHT_RED);
    this->setDeadColour(Console::RED);
}

Enemy::Enemy(int x, int y) : Enemy() { this->setPosition(x, y); }

bool Enemy::in_range(Entity other) {
    int xDistance = pow(this->currentPos.x - other.getPosition().x, 2);
    int yDistance = pow(this->currentPos.y - other.getPosition().y, 2);
    return sqrt(xDistance + yDistance) <= this->rangeRadius * 2;
}

void Enemy::follow(Entity other) {

    int xDist, xDistSq, yDist, yDistSq;
    int distance, distanceSq;

    bool shouldMoveX;
    int moveBy = 0;

    xDist = this->currentPos.x - other.getPosition().x;
    yDist = this->currentPos.y - other.getPosition().y;
    xDistSq = pow(xDist, 2);
    yDistSq = pow(yDist, 2);

    distanceSq = xDistSq + yDistSq;
    distance = sqrt(distanceSq);

    shouldMoveX = abs(xDist) > abs(yDist);

    if (shouldMoveX) {
        if (xDist > 0) { moveBy = -1; }
        else if (xDist < 0) { moveBy = 1; }
        this->Move(moveBy, 0);
    } else {
        if (yDist > 0) { moveBy = -1; }
        else if (yDist < 0) { moveBy = 1; }
        this->Move(0, moveBy);
    }
}