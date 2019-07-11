//
// Created by Agata Parietti on 2019-07-06.
//

#include "RocketCreator.h"

RocketCreator::RocketCreator() {
    rocketTexture.loadFromFile("/Users/agata/Documents/GitHub/CryptoRobot/Textures/Rocket.png");
}

RocketCreator::~RocketCreator() {

}

std::unique_ptr<Rocket> RocketCreator::createRocket() {
    std::unique_ptr<Rocket> result = std::unique_ptr<Rocket>(new class Rocket);
    result->setTexture(rocketTexture);
    result->setScale(0.2, 0.2);
    return result;
}


