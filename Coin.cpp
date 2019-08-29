//
// Created by Agata Parietti on 2019-07-06.
//

#include "Coin.h"

Coin::Coin() {
    isPowerUp = false;
}

bool Coin::getIsPowerUp() const {
    return isPowerUp;
}

void Coin::setIsPowerUp() {
    isPowerUp = true;
}


