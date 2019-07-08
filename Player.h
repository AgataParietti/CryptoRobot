//
// Created by Agata Parietti on 2019-07-08.
//

#ifndef CRYPTOROBOT_ROBOT_H
#define CRYPTOROBOT_ROBOT_H

#include <SFML/Graphics.hpp>

class Player {
public:
    Player();
    ~Player();

    void death() { isDead= true; }
    void renderRobot();
    bool gameOver(bool isDead);

    void setRobotTexture(const sf::Texture &playerTexture);
    void setRobotPos (float x, float y) {robot.setPosition(x,y); }

    bool getIsDead() const { return isDead;}
    sf::Vector2f getRobotSize();
    sf::FloatRect getRobotBounds() { return robot.getGlobalBounds(); }
    sf::Vector2f getRobotPos (sf::Vector2f) { return robot.getPosition(); }

private:
    sf::Sprite robot;
    bool isDead;
};

#endif //CRYPTOROBOT_ROBOT_H


