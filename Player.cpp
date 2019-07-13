//
// Created by Agata Parietti on 2019-07-08.
//

#include "Player.h"

Player::Player() {
    robot.setPosition(50, 100);
}

Player::~Player() {
}

void Player::renderRobot(sf::RenderWindow &map) {
    map.draw(robot);
}

bool Player::gameOver(bool isDead) {
    death();
    return isDead;
}

void Player::setRobotTexture(const sf::Texture &playerTexture){
    robot.setTexture(playerTexture);
    robot.setScale(1, 1);
}

sf::Vector2f Player::getRobotSize() const{
    float x= robot.getGlobalBounds().width;
    float y= robot.getGlobalBounds().height;
    return sf::Vector2f(x,y);
}





