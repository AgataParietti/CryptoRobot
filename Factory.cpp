//
// Created by Agata Parietti on 2019-08-12.
//

#include "Factory.h"

Factory::Factory() {
    stillBlockTexture.loadFromFile("Textures/Block.png");
    movingBlockTexture.loadFromFile("Textures/Block2.png");
    normalCoinTexture.loadFromFile("Textures/BitCoin1.png");
    powerUpCoinTexture.loadFromFile("Textures/PowerUp1.png");
    rocketTexture.loadFromFile("Textures/Rocket.png");
}

Factory::~Factory() {

}

std::unique_ptr<Block> Factory::createBlock(BlockType type) {
    std::unique_ptr<Block> result = std::unique_ptr<Block>(new Block());
    if (type == BlockType::StillBlock) {
        result->setTexture(stillBlockTexture);
        result->setScale(0.25, 0.25);
    } else {
        result->setTexture(movingBlockTexture);
        result->setIsMoving();
        result->setScale(0.35, 0.35);

    }
    return result;
}

std::unique_ptr<Coin> Factory::createCoin(CoinType type) {
    std::unique_ptr<Coin> result = std::unique_ptr<Coin>(new Coin());
    if (type == CoinType::NormalCoin) {
        result->setTexture(normalCoinTexture);
        result->setScale(0.15, 0.15);
    }
    else {
        result->setTexture(powerUpCoinTexture);
        result->setIsPowerUp();
        result->setScale(0.3,0.3);
    }

    return result;
}

std::unique_ptr<Rocket> Factory::createRocket() {
    std::unique_ptr<Rocket> result = std::unique_ptr<Rocket>(new Rocket());
    result->setTexture(rocketTexture);
    result->setScale(0.35, 0.35);
    return result;
}

