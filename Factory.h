//
// Created by Agata Parietti on 2019-08-12.
//

#ifndef CRYPTOROBOT_FACTORY_H
#define CRYPTOROBOT_FACTORY_H

#include <SFML/Graphics.hpp>
#include "Block.h"
#include "Rocket.h"
#include "Coin.h"

#include <iostream>

enum class BlockType {MovingBlock,StillBlock};
enum CoinType {PowerUpCoin, NormalCoin };


class Factory {
public:
    Factory();
    virtual ~Factory() = default;

    virtual std::unique_ptr<Block> createBlock(BlockType type);
    virtual std::unique_ptr<Rocket> createRocket();
    virtual std::unique_ptr<Coin> createCoin(CoinType type);


private:
    sf::Texture blockTexture;
    sf::Texture rocketTexture;
    sf::Texture normalCoinTexture;
    sf::Texture powerUpCoinTexture;
};

#endif //CRYPTOROBOT_FACTORY_H
