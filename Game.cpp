//
// Created by Agata Parietti on 2019-07-11.
//

#include "Game.h"

Game::Game(): map("CryptoRobot", sf::Vector2u (1600, 900)), robot(), blockCreator(), coinCreator(), rocketCreator(),
    blockX(100), coinX(100), rocketY(100) {

    robotTexture1.loadFromFile("/Users/agata/Documents/GitHub/CryptoRobot/Textures/Robot.png");
}

Game::~Game() {
    blocks.clear();
    coins.clear();
    rockets.clear();
}

void Game::updateGame() {
    map.update();
    createObject();
}

void Game::renderGame() {
    map.clear();
    for (auto &block : blocks)
        map.draw(*block);
    for (auto &coin : coins)
        map.draw(*coin);
    for (auto &rocket : rockets)
        map.draw(*rocket);
    map.display();
}

void Game::createObject() {
    std::unique_ptr<Block> block = blockCreator.createBlock(BlockType::NormalBlock);
    block->setPosition(100, 150);
    std::unique_ptr<Coin> coin = coinCreator.createCoin(CoinType::NormalCoin);
    coin->setPosition(500, 350);
    std::unique_ptr<Coin> pucoin = coinCreator.createCoin(CoinType::PowerUpCopin);
    pucoin->setPosition(900, 500);
    std::unique_ptr<Rocket> rocket = rocketCreator.createRocket();
    rocket->setPosition(1300, 450);

    map.clear();
    map.draw(*block);
    map.draw(*coin);
    map.draw(*pucoin);
    map.draw(*rocket);
    map.display();

}