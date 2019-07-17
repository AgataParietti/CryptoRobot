//
// Created by Agata Parietti on 2019-07-06.
//

#ifndef CRYPTOROBOT_COIN_H
#define CRYPTOROBOT_COIN_H

#include <SFML/Graphics.hpp>

class Coin: public sf::Sprite {
public:
    Coin();
    ~Coin();

    bool getIsPowerUp() const;
    void setIsPowerUp();

private:
    bool isPowerUp;
};

#endif //CRYPTOROBOT_COIN_H
