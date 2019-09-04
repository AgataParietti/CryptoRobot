//
// Created by Agata Parietti on 2019-07-06.
//

#include "Rocket.h"

Rocket::Rocket() {
    rocketSpeedX=1.8;
 }

float Rocket::getRocketSpeedX() const {
    return rocketSpeedX;
}

void Rocket::setRocketSpeedX(float rocketSpeedX) {
    Rocket::rocketSpeedX = rocketSpeedX;
}




