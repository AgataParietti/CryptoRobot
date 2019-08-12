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

    void death() { isDead = true; }
    void renderRobot(sf::RenderWindow &map);
    bool gameOver(bool isDead);

    void setRobotTexture(const sf::Texture &playerTexture);
    void setRobotPos (float x, float y) {robot.setPosition(x,y); }


    bool getIsDead() const { return isDead;}
    sf::Vector2f getRobotSize() const;
    sf::FloatRect getRobotBounds() const { return robot.getGlobalBounds(); }
    sf::Vector2f getRobotPos() const { return robot.getPosition(); }

private:
    sf::Sprite robot;
    bool isDead = false;
    int numCoins = 0;
};

#endif //CRYPTOROBOT_ROBOT_H


