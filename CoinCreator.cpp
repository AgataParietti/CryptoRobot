//
// Created by Agata Parietti on 2019-07-06.
//

#include "CoinCreator.h"

CoinCreator::CoinCreator() {
    //TODO choose texture for coins
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
    //TODO result->setScale();
    return result;
}


