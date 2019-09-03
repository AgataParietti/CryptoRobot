//
// Created by Agata Parietti on 2019-07-08.
//

#include "Player.h"

Player::Player() {
    robot.setPosition(50, 100);
}

void Player::renderRobot(sf::RenderWindow &map) {
    map.draw(robot);
}

bool Player::gameOver() {
    if (lives <= 1)
        death();
    return isDead;
}

void Player::setRobotTexture(const sf::Texture &playerTexture){
    robot.setTexture(playerTexture);
    robot.setScale(0.20, 0.20);
}

sf::Vector2f Player::getRobotSize() const{
    float x = robot.getGlobalBounds().width;
    float y = robot.getGlobalBounds().height;
    return sf::Vector2f(x,y);
}

void Player::setNumCoins(int numCoins) {
    Player::numCoins = numCoins;
}

int Player::getNumCoins() const {
    return numCoins;
}

unsigned int Player::getLives() const {
    return lives;
}

void Player::setLives(unsigned int lives) {
    Player::lives = lives;
}







