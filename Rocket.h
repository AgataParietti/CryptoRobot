//
// Created by Agata Parietti on 2019-07-06.
//

#ifndef CRYPTOROBOT_ROCKET_H
#define CRYPTOROBOT_ROCKET_H

#include <SFML/Graphics.hpp>

class Rocket: public sf::Sprite {
public:
    Rocket();
    ~Rocket();

    float getRocketSpeedX() const;
    void setRocketSpeedX(float rocketSpeedX);

private:
    float rocketSpeedX;

};

#endif //CRYPTOROBOT_ROCKET_H
