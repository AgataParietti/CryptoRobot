//
// Created by Agata Parietti on 2019-07-06.
//

#include "Block.h"

Block::Block() {
    isMoving = false;
    blockSpeedY = 0.8;
}

Block::~Block() {

}

bool Block::getIsMoving() const {
    return isMoving;
}

void Block::setIsMoving() {
    isMoving = true;
}

float Block::getBlockSpeedY() const {
    return blockSpeedY;
}

void Block::setBlockSpeedY(float speedY) {
    blockSpeedY = speedY;
}

