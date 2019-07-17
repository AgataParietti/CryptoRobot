//
// Created by Agata Parietti on 2019-07-06.
//

#include "BlockCreator.h"

BlockCreator::BlockCreator() {
    stillBlockTexture.loadFromFile("Textures/Block.png");
    movingBlockTexture.loadFromFile("Textures/Block2.png");
}

BlockCreator::~BlockCreator() {

}

std::unique_ptr<Block> BlockCreator::createBlock(BlockType type) {
    std::unique_ptr<Block> result = std::unique_ptr<Block>(new Block());
    if( type == BlockType::StillBlock){
        result->setTexture(stillBlockTexture);
        result->setScale(0.3,0.3);
    }
    else {
        result->setTexture(movingBlockTexture);
        result->setIsMoving();
        result->setScale(0.4,0.4);

    }
    return result;
};