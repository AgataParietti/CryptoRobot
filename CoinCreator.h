//
// Created by Agata Parietti on 2019-07-06.
//

#ifndef CRYPTOROBOT_COINCREATOR_H
#define CRYPTOROBOT_COINCREATOR_H

#include <SFML/Graphics.hpp>
#include "Coin.h"

enum CoinType {PowerUpCopin, NormalCoin };

class CoinCreator {
public:
    CoinCreator();
    virtual ~CoinCreator();

    std::unique_ptr<Coin> createCoin(CoinType type);

private:
    sf::Texture normalCoinTexture;
    sf::Texture powerUpCoinTexture;
};

#endif //CRYPTOROBOT_COINCREATOR_H
