//
// Created by Agata Parietti on 2019-07-11.
//

#include "Game.h"
#include <iostream>


Game::Game(): map("CryptoRobot", sf::Vector2u (1600, 1066)) {

    backgroundTexture.loadFromFile("/Users/agata/Documents/GitHub/CryptoRobot/Textures/Background.jpg");
    backgroundTexture.setRepeated(true);
    background.setTexture(backgroundTexture);


}

Game::~Game() {

}

void Game::update() {
    map.update();
}

void Game::render() {
    map.clear();
    map.draw(background);
    map.displayMap();
}







