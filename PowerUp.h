//
// Created by Agata Parietti on 2019-08-27.
//

#ifndef CRYPTOROBOT_POWERUP_H
#define CRYPTOROBOT_POWERUP_H

#include <SFML/Graphics.hpp>
#include "Game.h"

class PowerUp {
public:
    PowerUp();
    ~PowerUp() = default;

    void Immortality();
    void DoubleCoin();
    void Shield();
};

#endif //CRYPTOROBOT_POWERUP_H
