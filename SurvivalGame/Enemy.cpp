#include "Enemy.h"

#include <cmath>

Enemy::Enemy() {

    // Set enemy colour to red
    this->setColour(Console::LIGHT_RED);
    this->setDeadColour(Console::RED);
}

// Initialize enemy with desired position
Enemy::Enemy(int x, int y) : Enemy() { this->setPosition(x, y); }

bool Enemy::inRange(Entity other) {
    // Get squared distance of this enemy
    // and other Entity, on x and y axis
    int xDistance = pow(this->currentPos.x - other.getPosition().x, 2);
    int yDistance = pow(this->currentPos.y - other.getPosition().y, 2);

    // Return true if square root of xDistance + yDistance
    // is less than the Enemy's diameter range
    return sqrt(xDistance + yDistance) <= this->rangeRadius * 2;
}

void Enemy::follow(Entity other) {

    int xDist, xDistSq, yDist, yDistSq;
    int distance, distanceSq;

    bool shouldMoveX;
    int moveBy = 0;

    // Euclidean Distance
    // Distance between this Entity and other Entity
    xDist = this->currentPos.x - other.getPosition().x;
    yDist = this->currentPos.y - other.getPosition().y;
    xDistSq = pow(xDist, 2);
    yDistSq = pow(yDist, 2);

    distanceSq = xDistSq + yDistSq;
    distance = sqrt(distanceSq);

    // shouldMoveX = abs(-7) > abs(4)
    // shouldMoveX = 7 > 4
    shouldMoveX = abs(xDist) > abs(yDist);

    if (shouldMoveX) {
        // Move left
        if (xDist > 0) { moveBy = -1; }

        // Move right
        else if (xDist < 0) { moveBy = 1; }
        this->Move(moveBy, 0);
    } else {
        // Move up
        if (yDist > 0) { moveBy = -1; }

        // Move down
        else if (yDist < 0) { moveBy = 1; }
        this->Move(0, moveBy);
    }
}