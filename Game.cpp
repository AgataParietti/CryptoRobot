//
// Created by Agata Parietti on 2019-07-11.
//

#include "Game.h"
#include <iostream>


Game::Game(): map("CryptoRobot", sf::Vector2u (1600, 1066)), robot(), background(), bCreator(), cCreator(), rCreator() {

    //backgroundTexture.loadFromFile("");
    //backgroundTexture.setRepeated(true);
    //background.setTexture(backgroundTexture);

    robotTexture1.loadFromFile("Textures/Robot.png");
    robotTexture2.loadFromFile("Textures/RobotFire.png");
    robot.setRobotTexture(robotTexture1);

}

Game::~Game() {

}

void Game::update() {
    map.update();
    createObj();
}

void Game::render() {
    map.clear();
    //map.draw(background);
    if (!robot.getIsDead()) {
        robot.renderRobot(*map.getRenderMap());
        for (auto &block : blocks)
            map.draw(*block);
        for (auto &movBlock : blocks)
            map.draw(*movBlock);
        for (auto &coin : coins)
            map.draw(*coin);
        for (auto &puCoin : coins)
            map.draw(*puCoin);
        for (auto &rocket: rockets)
            map.draw(*rocket);
    }
    map.display();
}

void Game::createObj() {
    std::unique_ptr<Block> block = bCreator.createBlock(BlockType::StillBlock);
    block->setPosition(300,400);
    blocks.emplace_back(move(block));

    std::unique_ptr<Block> movBlock = bCreator.createBlock(BlockType::MovingBlock);
    movBlock->setPosition(600,100);
    blocks.emplace_back(move(movBlock));

    std::unique_ptr<Coin> coin = cCreator.createCoin(CoinType::NormalCoin);
    coin->setPosition(600,600);
    coins.emplace_back(move(coin));

    std::unique_ptr<Coin> puCoin = cCreator.createCoin(CoinType::PowerUpCoin);
    puCoin->setPosition(1000,200);
    coins.emplace_back(move(puCoin));

    std::unique_ptr<Rocket> rocket = rCreator.createRocket();
    rocket->setPosition(800,700);
    rockets.emplace_back(move(rocket));

}