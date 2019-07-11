//
// Created by Agata Parietti on 2019-07-06.
//

#include "BlockCreator.h"

BlockCreator::BlockCreator() {
    normalBlockTexture.loadFromFile("/Users/agata/Documents/GitHub/CryptoRobot/Textures/Block.png");
    movingBlockTexture.loadFromFile("/Users/agata/Documents/GitHub/CryptoRobot/Textures/Block2.png");
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
    result->setScale(0.5,0.5);
    return result;
};