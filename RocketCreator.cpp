//
// Created by Agata Parietti on 2019-07-06.
//

#include "RocketCreator.h"

RocketCreator::RocketCreator() {
    //TODO choose rocket texture
}

RocketCreator::~RocketCreator() {

}

std::unique_ptr<Rocket> RocketCreator::createRocket(Rocket) {
    std::unique_ptr<Rocket> result = std::unique_ptr<Rocket>(new class Rocket);
    result->setTexture(rocketTexture);
    //TODO result->setScale();
    return result;
}


