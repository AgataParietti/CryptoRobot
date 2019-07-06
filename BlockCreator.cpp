//
// Created by Agata Parietti on 2019-07-06.
//

#include "BlockCreator.h"

BlockCreator::BlockCreator() {
    //TODO choose texture for blocks
}

BlockCreator::~BlockCreator() {
}

std::unique_ptr<Block> BlockCreator::createBlock(BlockType type) {
    std::unique_ptr<Block> result = std::unique_ptr<Block>(new class Block);
    if( type == BlockType::NormalBlock)
        result->setTexture(normalBlockTexture);
    else {
        result->setTexture(movingBlockTexture);
        result->setIsMoving();
    }
    //TODO result->setScale();
    return result;
};