//
// Created by Agata Parietti on 2019-07-06.
//

#include "Block.h"

Block::Block() {
    isMoving=false;
}

Block::~Block() {

}

bool Block::getIsMoving() const {
    return isMoving;
}

void Block::setIsMoving() {
    isMoving = true;
}

