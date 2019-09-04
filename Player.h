//
// Created by Agata Parietti on 2019-07-08.
//

#ifndef CRYPTOROBOT_ROBOT_H
#define CRYPTOROBOT_ROBOT_H

#include <SFML/Graphics.hpp>

class Player {
public:
    Player();
    ~Player()= default;

    void renderRobot(sf::RenderWindow &map);
    bool gameOver();
    void rotateRobot (float angle) { robot.rotate(angle); }

    void setRobotTexture(const sf::Texture &playerTexture);
    void setRobotPos (float x, float y) {robot.setPosition(x,y); }
    void setNumCoins(int numCoins);
    void setLives(unsigned int lives);

    bool getIsDead() const { return isDead;}
    sf::Vector2f getRobotSize() const;
    sf::FloatRect getRobotBounds() const { return robot.getGlobalBounds(); }
    sf::Vector2f getRobotPos() const { return robot.getPosition(); }
    int getNumCoins() const;
    unsigned int getLives() const;


private:
    void death() { isDead = true; }

    sf::Sprite robot;
    bool isDead = false;
    int numCoins = 0;
    int lives = 3;
};

#endif //CRYPTOROBOT_ROBOT_H


