//
// Created by Agata Parietti on 2019-07-06.
//

#include "CoinCreator.h"

CoinCreator::CoinCreator() {
    normalCoinTexture.loadFromFile("/Users/agata/Documents/GitHub/CryptoRobot/Textures/BitCoin1.png");
    powerUpCoinTexture.loadFromFile("/Users/agata/Documents/GitHub/CryptoRobot/Textures/PowerUp1.png");
}

CoinCreator::~CoinCreator() {

}

std::unique_ptr<Coin> CoinCreator::createCoin(CoinType type) {
    std::unique_ptr<Coin> result = std::unique_ptr<Coin>(new class Coin);
    if (type == CoinType::NormalCoin)
        result->setTexture(normalCoinTexture);
    else {
        result->setTexture(powerUpCoinTexture);
        result->setIsPowerUp();
    }
    result->setScale(0.1,0.1);
    return result;
}


