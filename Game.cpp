//
// Created by Agata Parietti on 2019-07-11.
//

#include "Game.h"
#include <iostream>


Game::Game(): map("CryptoRobot", sf::Vector2u(1600, 1066)), robot(), background(), factory(), speed(sf::Vector2f(0.7,0.8)),
                blockX(100), isCreated(false), isCoinCreated(false), countCreation(1), creationRate(1.4f), objectClk() {

    backgroundTexture.loadFromFile("Textures/Background.jpg");
    backgroundTexture.setRepeated(true);
    background.setTexture(backgroundTexture);
    background.setTextureRect(sf::IntRect(0, 0, (500 * map.getMapSize().x), map.getMapSize().y + static_cast<int>(ground)));
    //background.setScale(1, 1);

    robotTexture0.loadFromFile("Textures/RobotInit.png");
    robotTexture1.loadFromFile("Textures/Robot.png");
    robotTexture2.loadFromFile("Textures/RobotFire.png");
    robot.setRobotTexture(robotTexture0);

    srand((unsigned) time(nullptr));
    maxY = static_cast<int>(map.getMapSize().y - (ground + blockX));
}

Game::~Game() {

}

void Game::update() {
    map.update();
    background.move(-speed.x, 0);

    createObj();
    moveObject();
    moveRobot();
    deleteObject();
}

void Game::render() {
    map.clear();
    // map.draw(background);
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
    if (objectClk.getElapsedTime().asSeconds() >= creationRate) {
        if (countCreation % 2 == 0 && randomCreation() == 1) {
            std::unique_ptr<Coin> coin = factory.createCoin(CoinType::NormalCoin);
            coin->setPosition(sf::Vector2f(2*map.getMapSize().x,randomPosY()));
            coins.emplace_back(move(coin));
            isCreated = true;
            isCoinCreated = true;
            objectClk.restart();
            countCreation++;
        }
        if (countCreation % 5 == 0 && randomCreation() == 1 && !isCreated) {
            std::unique_ptr<Coin> coin = factory.createCoin(CoinType::PowerUpCoin);
            coin->setPosition(sf::Vector2f(2*map.getMapSize().x,randomPosY()));
            coins.emplace_back(move(coin));
            isCreated = true;
            isCoinCreated = true;
            objectClk.restart();
            countCreation++;
        }
        if (countCreation % 3 == 0 && randomCreation() == 2) {
            std::unique_ptr<Rocket> rocket = factory.createRocket();
            rocket->setPosition(sf::Vector2f(2*map.getMapSize().x,randomPosY()));
            rockets.emplace_back(move(rocket));
            isCreated = true;
            objectClk.restart();
            countCreation++;
        }
        if (countCreation % 7 == 0 && randomCreation() == 3) {
            std::unique_ptr<Block> block = factory.createBlock(BlockType::MovingBlock);
            block->setPosition(sf::Vector2f(2*map.getMapSize().x,randomPosY()));
            blocks.emplace_back(move(block));
            isCreated = true;
            objectClk.restart();
            countCreation++;
        }
        if (!isCreated) {
            std::unique_ptr<Block> block = factory.createBlock(BlockType::StillBlock);
            block->setPosition(sf::Vector2f(2*map.getMapSize().x, randomPosY()));
            blocks.emplace_back(move(block));
            isCreated = true;
            objectClk.restart();
            countCreation++;
        }
        isCreated = false;
        isCoinCreated = false;
    }

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

void Game::moveObject() {
    for (auto &b : blocks)
        b->move(-speed.x,0);
    for (auto &c : coins)
        c->move(-speed.x,0);
    for (auto &r : rockets)
        r->move(-speed.x*2.5 ,0);
}

void Game::deleteObject() {
    for (int i=0; i<blocks.size(); i++) {
        if (blocks[i]->getPosition().x + blocks[i]->getGlobalBounds().width < 0)
            blocks.erase(blocks.begin() + i);
    }

    for (int i=0; i<coins.size(); i++) {
        if (coins[i]->getPosition().x + coins[i]->getGlobalBounds().width < 0)
            coins.erase(coins.begin() + i);
    }

    for (int i=0; i<rockets.size(); i++) {
        if (rockets[i]->getPosition().x + rockets[i]->getGlobalBounds().width < 0)
            rockets.erase(rockets.begin() + i);
    }

}

int Game::randomPosY() {
    return (rand() % maxY);
}

int Game::randomCreation() {
    return (rand() % 4);
}
