//
// Created by Agata Parietti on 2019-07-06.
//

#ifndef CRYPTOROBOT_BLOCKCREATOR_H
#define CRYPTOROBOT_BLOCKCREATOR_H

#include <SFML/Graphics.hpp>
#include "Block.h"

enum BlockType { MovingBlock, NormalBlock };

class BlockCreator {
public:
    BlockCreator();
    virtual ~BlockCreator();

    std::unique_ptr<Block> createBlock(BlockType type);

private:
    sf::Texture movingBlockTexture;
    sf::Texture normalBlockTexture;
};

#endif //CRYPTOROBOT_BLOCKCREATOR_H
