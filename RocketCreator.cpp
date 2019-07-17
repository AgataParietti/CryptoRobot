//
// Created by Agata Parietti on 2019-07-06.
//

#include "RocketCreator.h"

RocketCreator::RocketCreator() {
    rocketTexture.loadFromFile("Textures/Rocket.png");
}

RocketCreator::~RocketCreator() {

}

std::unique_ptr<Rocket> RocketCreator::createRocket() {
    std::unique_ptr<Rocket> result = std::unique_ptr<Rocket>(new Rocket());
    result->setTexture(rocketTexture);
    result->setScale(0.35, 0.35);
    return result;
}