//
// Created by Agata Parietti on 2019-07-11.
//

#include "Game.h"
#include <iostream>


Game::Game(): map("CryptoRobot", sf::Vector2u(1600, 1066)), robot(), background(), factory() {

    backgroundTexture.loadFromFile("Textures/Background.jpg");
    backgroundTexture.setRepeated(true);
    background.setTexture(backgroundTexture);

    robotTexture0.loadFromFile("Textures/RobotInit.png");
    robotTexture1.loadFromFile("Textures/Robot.png");
    robotTexture2.loadFromFile("Textures/RobotFire.png");
    robot.setRobotTexture(robotTexture0);

}

Game::~Game() {

}

void Game::update() {
    map.update();
    //createObj();
    background.move(-0.7, 0);
    moveRobot();
}

void Game::render() {
    map.clear();
    //map.draw(background);
    if (!robot.getIsDead()) {
        robot.renderRobot(*map.getRenderMap());
        /*for (auto &block : blocks)
            map.draw(*block);
        for (auto &movBlock : blocks)
            map.draw(*movBlock);
        for (auto &coin : coins)
            map.draw(*coin);
        for (auto &puCoin : coins)
            map.draw(*puCoin);
        for (auto &rocket: rockets)
            map.draw(*rocket);*/
    }
    map.display();
}

void Game::createObj() {
    std::unique_ptr<Block> block = factory.createBlock(BlockType::StillBlock);
    block->setPosition(300,400);
    blocks.emplace_back(move(block));

    std::unique_ptr<Block> movBlock = factory.createBlock(BlockType::MovingBlock);
    movBlock->setPosition(600,100);
    blocks.emplace_back(move(movBlock));

    std::unique_ptr<Coin> coin = factory.createCoin(CoinType::NormalCoin);
    coin->setPosition(600,600);
    coins.emplace_back(move(coin));

    std::unique_ptr<Coin> puCoin = factory.createCoin(CoinType::PowerUpCoin);
    puCoin->setPosition(1000,200);
    coins.emplace_back(move(puCoin));

    std::unique_ptr<Rocket> rocket = factory.createRocket();
    rocket->setPosition(800,700);
    rockets.emplace_back(move(rocket));

}

void Game::moveRobot() {
    robot.setRobotPos(robot.getRobotPos().x, robot.getRobotPos().y + g);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        robot.setRobotPos(robot.getRobotPos().x, robot.getRobotPos().y - jump);
        robot.setRobotTexture(robotTexture2);
        robotTexture2.setSmooth(true);
    }
    else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        robot.setRobotTexture(robotTexture1);
        robotTexture1.setSmooth(true);
    }
    if (robot.getRobotPos().y + robot.getRobotSize().y >= map.getMapSize().y - ground)
        robot.setRobotPos(robot.getRobotPos().x, map.getMapSize().y - (robot.getRobotSize().y + ground));
    if (robot.getRobotPos().y <= top )
        robot.setRobotPos(robot.getRobotPos().x, top );
}
