//
// Created by Agata Parietti on 2019-07-06.
//

#ifndef CRYPTOROBOT_ROCKETCREATOR_H
#define CRYPTOROBOT_ROCKETCREATOR_H

#include <SFML/Graphics.hpp>
#include "Rocket.h"

class RocketCreator {
public:
    RocketCreator();
    ~RocketCreator();

    std::unique_ptr<Rocket> createRocket();

private:
    sf::Texture rocketTexture;
};

#endif //CRYPTOROBOT_ROCKETCREATOR_H
