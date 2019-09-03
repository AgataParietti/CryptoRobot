//
// Created by Agata Parietti on 2019-07-11.
//

#include "Game.h"
#include <iostream>


Game::Game(): map("CryptoRobot", sf::Vector2u(1600, 1000)), robot(), background(), factory(), speed(sf::Vector2f(0.7,0.8)),
                oldSpeed(speed), blockX(100), isCreated(false), isCoinCreated(false), isCollided(false), countCreation(1), creationRate(1.4f),
                objectClk(), controlPU(), scoreClk(), speedClk(), doubleClk(), collisionClk(), isImmortalityOn(false), isDoubleCoinOn(false),
                isShieldOn(false), n(1), score(0), txtCount(0) {

    backgroundTexture.loadFromFile("/Users/agata/Documents/GitHub/CryptoRobot/Textures/Background.png");
    backgroundTexture.setRepeated(true);
    background.setTexture(backgroundTexture);
    background.setTextureRect(sf::IntRect(0, 0, (500 * map.getMapSize().x), map.getMapSize().y + static_cast<int>(ground)));
    background.setScale(1, 1);

    robotTexture1.loadFromFile("/Users/agata/Documents/GitHub/CryptoRobot/Textures/Robot.png");
    robotTexture2.loadFromFile("/Users/agata/Documents/GitHub/CryptoRobot/Textures/RobotFire.png");
    robot.setRobotTexture(robotTexture1);
    robotTextureS1.loadFromFile("/Users/agata/Documents/GitHub/CryptoRobot/Textures/RobotS.png");
    robotTextureS2.loadFromFile("/Users/agata/Documents/GitHub/CryptoRobot/Textures/RobotFireS.png");

    gameOverTexture.loadFromFile("/Users/agata/Documents/GitHub/CryptoRobot/Textures/GameOver.png");
    gameOver.setTexture(gameOverTexture);
    gameOver.setPosition(225,100);
    gameOver.setScale(0.8,0.8);

    font1.loadFromFile("/Users/agata/Documents/GitHub/CryptoRobot/Font/SupersonicRocketship.ttf");
    fontb.loadFromFile("/Users/agata/Documents/GitHub/CryptoRobot/Font/Bitcoin.otf");

    srand((unsigned) time(nullptr));
    maxY = static_cast<int>(map.getMapSize().y - (top + blockX));

}

Game::~Game() {
    blocks.clear();
    rockets.clear();
    coins.clear();
}

void Game::update() {
    map.update();
    background.move(-speed.x, 0);

    if (robot.getIsDead() && txtCount == 0) {
        file.open("Score.txt", std::ios::out | std::ios::app);
        file << std::endl;
        file << "Score: " << score;
        file.close();
        txtCount++;
    }

    createObj();
    moveObject();
    moveRobot();
    deleteObject();
    handleTxt();

    setScore(score);
    setLives(robot.getLives());

    if (!isImmortalityOn) {
        if (!robot.getIsDead() && !isCollided) {
            collision();
        }
        else if (isCollided && robot.getLives() >= 1) {
            if (collisionClk.getElapsedTime().asSeconds() >= 0.5f) {
                robot.setLives(robot.getLives() - 1);
                notify();
                isCollided = false;
            }
        }
    }

    //ogni secondo aumenta lo score
    if (scoreClk.getElapsedTime().asSeconds() >= 1.f && !robot.getIsDead()) {
        score ++;
        scoreClk.restart();
        notify();
    }

    //quando score è multiplo di speedLimit, speed aumenta
    if((score >= n * speedMul) && speed.x != speedLimit) {
        speed.x += speedPlus;
        jump += 0.05;
        g += 0.025;
        if (score <= creationLimit)
            creationRate -= creationPlus;
        n++;
    }

    if(isImmortalityOn && scoreClk.getElapsedTime().asSeconds() >= 0.1f && !robot.getIsDead()){
        score ++;
        scoreClk.restart();
        notify();
    }

    if (isImmortalityOn && speedClk.getElapsedTime().asSeconds() >= 3.f) {
        isImmortalityOn = false;
        speed = oldSpeed;
        robot.setRobotPos(50,robot.getRobotPos().y);
        robot.rotateRobot(-90.f);
    }

    if (isDoubleCoinOn && doubleClk.getElapsedTime().asSeconds() >= 20.f) {
            isDoubleCoinOn = false;
    }
}

void Game::render() {
    map.clear();
    map.draw(background);
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
        map.draw(scoreTxt);
        map.draw(numScore);
        if (isDoubleCoinOn)
            map.draw(doubleCoin);
        map.draw(coinTxt);
        map.draw(numCoins);
        map.draw(liveTxt);
    }
    else {
        scoreTxt.setCharacterSize(80);
        numScore.setCharacterSize(80);
        coinTxt.setCharacterSize(80);
        numCoins.setCharacterSize(80);
        scoreTxt.setPosition(600, 400);
        numScore.setPosition(900, 400);
        coinTxt.setPosition(600,500);
        numCoins.setPosition(900, 500);
        scoreB.setPosition(500, 390);
        coinB.setPosition(500, 490);
        map.draw(scoreTxt);
        map.draw(numScore);
        map.draw(coinTxt);
        map.draw(numCoins);
        map.draw(gameOver);
        map.draw(scoreB);
        map.draw(coinB);
    }
    map.display();
}

void Game::createObj() {
    if (objectClk.getElapsedTime().asSeconds() >= creationRate) {
        if (countCreation % 1 == 0 && randomCreation() == 0) {
            std::unique_ptr<Coin> coin = factory.createCoin(CoinType::NormalCoin);
            coin->setPosition(sf::Vector2f(2*map.getMapSize().x,randomPosY()));
            coins.emplace_back(move(coin));
            isCreated = true;
            isCoinCreated = true;
            objectClk.restart();
            countCreation++;
        }
        if (countCreation % 5 == 0 && randomCreation() == 0 && !isCoinCreated && !isImmortalityOn && !isDoubleCoinOn
                && !isShieldOn) {

            std::unique_ptr<Coin> coin = factory.createCoin(CoinType::PowerUpCoin);
            coin->setPosition(sf::Vector2f(2*map.getMapSize().x,randomPosY()));
            coins.emplace_back(move(coin));
            isCreated = true;
            isCoinCreated = true;
            objectClk.restart();
            countCreation++;
        }
        if (countCreation % 3 == 0 && randomCreation() == 1) {
            std::unique_ptr<Rocket> rocket = factory.createRocket();
            rocket->setPosition(sf::Vector2f(2*map.getMapSize().x,randomPosY()));
            rockets.emplace_back(move(rocket));
            isCreated = true;
            objectClk.restart();
            countCreation++;
        }
        if (countCreation % 2 == 0 && randomCreation() == 2 && !isCreated) {
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
        if (isShieldOn)
            robot.setRobotTexture(robotTextureS2);
        else
            robot.setRobotTexture(robotTexture2);
        robotTexture2.setSmooth(true);
    }
    else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        if (isShieldOn)
            robot.setRobotTexture(robotTextureS1);
        else
            robot.setRobotTexture(robotTexture1);
        robotTexture1.setSmooth(true);
    }
    if (robot.getRobotPos().y + robot.getRobotSize().y >= map.getMapSize().y - ground)
        robot.setRobotPos(robot.getRobotPos().x, map.getMapSize().y - (robot.getRobotSize().y + ground));
    if (robot.getRobotPos().y <= top )
        robot.setRobotPos(robot.getRobotPos().x, top );
}

void Game::moveObject() {
    for (auto &b : blocks) {
        if (b->getIsMoving()) {
            if (b->getPosition().y + b->getGlobalBounds().height >= map.getMapSize().y - ground ||
                b->getPosition().y <= 0)
                b->setBlockSpeedY(-b->getBlockSpeedY());
            b->move(-speed.x, b->getBlockSpeedY());
        } else
            b->move(-speed.x, 0);
    }
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
    for (int i = 0; i < blocks.size(); i++) {
        if (blocks[i]->getGlobalBounds().intersects(robot.getRobotBounds())) {
            //Se il robot ha lo scudo e interseca un blocco non muore
            if (isShieldOn) {
                isShieldOn = false;
                controlPU.restart();
            } else if (controlPU.getElapsedTime().asSeconds() >= toll) {
                robot.gameOver();
                isCollided = true;
                collisionClk.restart();
            }
        }
    }

    for (int j = 0; j < rockets.size(); j++) {
        if (rockets[j]->getGlobalBounds().intersects(robot.getRobotBounds())) {
            //Se il robot ha lo scudo e interseca un razzo non muore
            if (isShieldOn) {
                isShieldOn = false;
                controlPU.restart();
            } else if (controlPU.getElapsedTime().asSeconds() >= toll) {
                robot.gameOver();
                isCollided = true;
                collisionClk.restart();
            }
        }
    }

    for (int k=0; k < coins.size(); k++) {
        if (coins[k]->getGlobalBounds().intersects(robot.getRobotBounds())) {
            //Se il robot interseca una moneta normale aumenta lo score e il numero di monete collezionate
            if (!coins[k]->getIsPowerUp()) {
                score++;
                if (isDoubleCoinOn) { // se il robot ha il  PU doppia moneta
                    robot.setNumCoins(robot.getNumCoins() + 2);
                    score++;
                }
                else
                    robot.setNumCoins(robot.getNumCoins() + 1);
                notify();
            }
            else {
                int random = randomPU();
                if (random == 0) { //si raddoppia il valore delle monete
                    isDoubleCoinOn = true;
                    doubleClk.restart();
                }

                if (random == 1) {  //Scudo
                    isShieldOn = true;
                }

                if (random == 2) { //Immortalità
                    isImmortalityOn = true;
                    oldSpeed = speed;
                    speed.x=9.f;
                    speedClk.restart();
                    robot.setRobotPos(robot.getRobotPos().x + robot.getRobotBounds().width, robot.getRobotPos().y);
                    robot.rotateRobot(90.f);
                }
                score += 3;
                notify();
            }
            coins.erase(coins.begin() + k);
        }
    }
}

void Game::handleTxt() {
    scoreTxt.setFont(font1);
    scoreTxt.setString("Score: ");
    scoreTxt.setPosition(10,3);
    scoreTxt.setCharacterSize(25);
    scoreTxt.setFillColor(sf::Color::Black);

    numScore.setFont(font1);
    numScore.setPosition(100,3);
    numScore.setCharacterSize(25);
    numScore.setString(std::to_string(score));
    numScore.setFillColor(sf::Color::Black);


    coinTxt.setFont(font1);
    coinTxt.setString("Coins: ");
    coinTxt.setPosition(10,30);
    coinTxt.setCharacterSize(25);
    coinTxt.setFillColor(sf::Color::Black);

    numCoins.setFont(font1);
    numCoins.setString(std::to_string(robot.getNumCoins()));
    numCoins.setPosition(100, 30);
    numCoins.setCharacterSize(25);
    numCoins.setFillColor(sf::Color::Black);

    doubleCoin.setFont(font1);
    doubleCoin.setString("x2");
    doubleCoin.setPosition(140,30);
    doubleCoin.setCharacterSize(25);
    doubleCoin.setFillColor(sf::Color::Black);

    scoreB.setFont(fontb);
    scoreB.setString("0");
    scoreB.setFillColor(sf::Color::Black);
    scoreB.setCharacterSize(100);

    coinB.setFont(fontb);
    coinB.setString("e");
    coinB.setFillColor(sf::Color::Black);
    coinB.setCharacterSize(100);

    liveTxt.setFont(font1);
    liveTxt.setString(std::to_string(robot.getLives()));
    liveTxt.setPosition(10, 60);
    liveTxt.setFillColor(sf::Color::Black);
    liveTxt.setCharacterSize(100);

}


// funzioni randomiche
int Game::randomPosY() {
    return (rand() % maxY);
}

int Game::randomCreation() {
    return (rand() % 3);
}

int Game::randomPU() {
    return (rand() % 3);
}


//funzioni getter
const sf::Vector2f &Game::getSpeed() const {
    return speed;
}

int Game::getMaxY() const {
    return maxY;
}

bool Game::getisShieldOn() const {
    return isShieldOn;
}

bool Game::getisImmortalityOn() const {
    return isImmortalityOn;
}

bool Game::getisDoubleCoinOn() const {
    return isDoubleCoinOn;
}

int Game::getScore() const {
    return score;
}

int Game::getLives() const {
    return robot.getLives();
}




//funzioni observer
void Game::setScore(unsigned int score) {
    Game::score = score;
    notify();
}

void Game::setLives(unsigned int lives) {
    Game::robot.setLives(lives);
    notify();
}

void Game::notify() {
    for (auto i = std::begin(observers); i != std::end(observers); i++)
        (*i)->update();
}

void Game::unsubscribe(Observer *o) {
    observers.remove(o);
}

void Game::subscribe(Observer *o) {
    observers.push_back(o);
}



