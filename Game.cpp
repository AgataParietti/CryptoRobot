//
// Created by Agata Parietti on 2019-07-11.
//

#include "Game.h"
#include <iostream>


Game::Game(): map("CryptoRobot", sf::Vector2u(1600, 1066)), robot(), background(), factory(), speed(sf::Vector2f(1,0.8)),
                blockX(100), isCreated(false), isCoinCreated(false), countCreation(1), creationRate(1.2f), objectClk(),
                powerUpOn(false), n(1) {

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

    if (!robot.getIsDead())
        collision();
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
        if (countCreation % 1 == 0 && randomCreation() == 1) {
            std::unique_ptr<Coin> coin = factory.createCoin(CoinType::NormalCoin);
            coin->setPosition(sf::Vector2f(2*map.getMapSize().x,randomPosY()));
            coins.emplace_back(move(coin));
            isCreated = true;
            isCoinCreated = true;
            objectClk.restart();
            countCreation++;
        }
        if (countCreation % 5 == 0 && randomCreation() == 1 && !isCoinCreated && !powerUpOn) {
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
        if (countCreation % 2 == 0 && randomCreation() == 3 && !isCreated) {
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
        if (b -> getIsMoving()) {
            if(b->getPosition().y + b->getGlobalBounds().height >= map.getMapSize().y - ground || b->getPosition().y <= 0 )
                b->setBlockSpeedY( -b->getBlockSpeedY());
            b->move(-speed.x, b->getBlockSpeedY());
        }
        else
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

void Game::collision() {
    for (int i=0; i < blocks.size(); i++) {
        if (blocks[i]->getGlobalBounds().intersects(robot.getRobotBounds())) {
            if (isShieldOn) {
                isShieldOn = false;
                controlPU.restart();
            } else if (controlPU.getElapsedTime().asSeconds() >= toll)
                robot.gameOver(true);
        }
    }
    for (int j=0; j < rockets.size(); j++) {
        if (rockets[j]->getGlobalBounds().intersects(robot.getRobotBounds())) {
            if (isShieldOn) {
                isShieldOn = false;
                controlPU.restart();
            } else if (controlPU.getElapsedTime().asSeconds() >= toll)
                robot.gameOver(true);
        }
    }
    for (int k=0; k < coins.size(); k++) {
        if (coins[k]->getGlobalBounds().intersects(robot.getRobotBounds())) {
            if (!coins[k]->getIsPowerUp()) {
                //TODO aumenta lo score; observer
                coins.erase(coins.begin() + k);

            }
        }
        /*else {
            int random = randomPU();
            if (random == 0)
                powerUp.DoubleCoin();
            if (random == 1)
                powerUp.Immortality();
            if (random == 2)
                powerUp.Shield();
            coins.erase(coins.begin() + k);
            powerUpOn = true;
            //TODO notify();
        }*/
    }
}



int Game::randomPosY() {
    return (rand() % maxY);
}

int Game::randomCreation() {
    return (rand() % 4);
}

int Game::randomPU() {
    return (rand() % 3);
}



void Game::setIsShieldOn(bool isShieldOn) {
    Game::isShieldOn = isShieldOn;
}

void Game::setSpeed(const sf::Vector2f &speed) {
    Game::speed = speed;
}

void Game::setOldSpeed(const sf::Vector2f &oldSpeed) {
    Game::oldSpeed = oldSpeed;
}


