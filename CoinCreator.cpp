//
// Created by Agata Parietti on 2019-07-06.
//

#include "CoinCreator.h"

CoinCreator::CoinCreator() {
    normalCoinTexture.loadFromFile("Textures/BitCoin1.png");
    powerUpCoinTexture.loadFromFile("Textures/PowerUp1.png");
}

CoinCreator::~CoinCreator() {

}

std::unique_ptr<Coin> CoinCreator::createCoin(CoinType type) {
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


