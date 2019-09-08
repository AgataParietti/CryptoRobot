//
// Created by Agata Parietti on 2019-08-30.
//

#include "gtest/gtest.h"
#include "../Game.h"

class GameTest: public ::testing::Test {
protected:
    Game game;
    Map map;
    Player robot;
    Factory factory;
    Block block;
    Coin coin;
    Rocket rocket;

    float creationRate;

    std::vector<std::unique_ptr<Block>> blocks;
    std::vector<std::unique_ptr<Coin>> coins;
    std::vector<std::unique_ptr<Rocket>> rockets;

    bool collision = true;

};

TEST_F(GameTest , testAssignment) {
    ASSERT_EQ(sf::Vector2f(0.9,0.8), game.getSpeed());
    ASSERT_TRUE(creationRate < 1.9f);
    ASSERT_TRUE(game.randomCreation() >= 0 && game.randomCreation()<=2);
    ASSERT_TRUE(game.randomPosY() >= 0 && game.randomPosY() <= game.getMaxY());
    ASSERT_TRUE(game.randomPU() >= 0 && game.randomPU() <= 2);
    ASSERT_TRUE(game.getLives() == 3);
}

TEST_F(GameTest, testDeletingBlocks) {
    int blockSize = game.getBlocksSize();
    block.setPosition(-block.getGlobalBounds().width, block.getPosition().y);
    if (block.getPosition().x + block.getGlobalBounds().width < 0) {
        blocks.erase(blocks.begin() + 0);
        ASSERT_TRUE(blockSize > game.getBlocksSize());
    }

}

TEST_F(GameTest, testDeletingCoins) {
    int coinsSize = game.getCoinsSize();
    coin.setPosition(-coin.getGlobalBounds().width, coin.getPosition().y);
    if (coin.getPosition().x + coin.getGlobalBounds().width < 0) {
        coins.erase(coins.begin() + 0);
        ASSERT_TRUE(coinsSize > game.getCoinsSize());
    }

}

TEST_F(GameTest, testDeletingRockets) {
    int rocketsSize = game.getRocketsSize();
    rocket.setPosition(-rocket.getGlobalBounds().width, rocket.getPosition().y);
    if (rocket.getPosition().x + rocket.getGlobalBounds().width < 0) {
        rockets.erase(rockets.begin() + 0);
        ASSERT_TRUE(rocketsSize > game.getRocketsSize());
    }

}


TEST_F(GameTest, testCollisionStillBlock) {
    int numLives = game.getLives();
    std::unique_ptr<Block> block = factory.createBlock(BlockType::StillBlock);
    block->setPosition(sf::Vector2f(2*game.getMap()->getMapSize().x,game.randomPosY()));
    block->move(-game.getSpeed().x, 0);
    robot.setRobotPos(game.getMap()->getMapSize().x, -game.randomPosY());
    if (block->getGlobalBounds().intersects(robot.getRobotBounds())) {
        if (game.getisShieldOn()) {
            ASSERT_TRUE(game.getisShieldOn());
            ASSERT_FALSE(robot.getIsDead());
        }
        else if (game.getisImmortalityOn()) {
            ASSERT_TRUE(game.getisImmortalityOn());
            ASSERT_FALSE(robot.getIsDead());
        }
        else if (game.getLives() > 0) {
            ASSERT_FALSE(robot.getIsDead());
            ASSERT_EQ(numLives --, game.getLives());
        }
        else {
            ASSERT_TRUE(collision);
            ASSERT_TRUE(robot.getIsDead());
        }
    }
}


TEST_F(GameTest, testCollisionMovingBlock) {
    int numLives = game.getLives();
    std::unique_ptr<Block> block = factory.createBlock(BlockType::MovingBlock);
    block->setPosition(sf::Vector2f(2*game.getMap()->getMapSize().x,game.randomPosY()));
    block->move(-game.getSpeed().x, 0);
    robot.setRobotPos(game.getMap()->getMapSize().x, -game.randomPosY());
    if (block->getGlobalBounds().intersects(robot.getRobotBounds())) {
        if (game.getisShieldOn()) {
            ASSERT_TRUE(game.getisShieldOn());
            ASSERT_FALSE(robot.getIsDead());
        }
        else if (game.getisImmortalityOn()) {
            ASSERT_TRUE(game.getisImmortalityOn());
            ASSERT_FALSE(robot.getIsDead());
        }
        else if (game.getLives() > 0) {
            ASSERT_FALSE(robot.getIsDead());
            ASSERT_EQ(numLives --, game.getLives());
        }
        else {
            ASSERT_TRUE(collision);
            ASSERT_TRUE(robot.getIsDead());
        }
    }

}

TEST_F(GameTest, testCollisionRocket) {
    int numLives = game.getLives();
    std::unique_ptr<Rocket> rocket = factory.createRocket();
    rocket->setPosition(sf::Vector2f(2*game.getMap()->getMapSize().x, game.randomPosY()));
    rocket->move(-game.getSpeed().x*2.5, 0);
    robot.setRobotPos(game.getMap()->getMapSize().x, -game.randomPosY());
    if (rocket->getGlobalBounds().intersects(robot.getRobotBounds())) {
        if (game.getisShieldOn()) {
            ASSERT_TRUE(game.getisShieldOn());
            ASSERT_FALSE(robot.getIsDead());
        }
        else if (game.getisImmortalityOn()) {
            ASSERT_TRUE(game.getisImmortalityOn());
            ASSERT_FALSE(robot.getIsDead());
        }
        else if (game.getLives() > 0) {
            ASSERT_FALSE(robot.getIsDead());
            ASSERT_EQ(numLives --, game.getLives());
        }
        else {
            ASSERT_TRUE(collision);
            ASSERT_TRUE(robot.getIsDead());
        }
    }
}

TEST_F(GameTest, testCollisionNormalCoin) {
    int coinsSize = game.getCoinsSize();
    int testScore = game.getScore();
    int testNumCoin = robot.getNumCoins();
    std::unique_ptr<Coin> coin = factory.createCoin(CoinType::NormalCoin);
    coin->setPosition(sf::Vector2f(2*game.getMap()->getMapSize().x, game.randomPosY()));
    coin->move(-game.getSpeed().x, 0);
    robot.setRobotPos(game.getMap()->getMapSize().x, -game.randomPosY());
    if (coin->getGlobalBounds().intersects(robot.getRobotBounds())) {
        if(game.getisDoubleCoinOn()) {
            ASSERT_TRUE(game.getisDoubleCoinOn());
            ASSERT_TRUE(coinsSize > game.getCoinsSize());
            ASSERT_EQ(testScore + 2, game.getScore());
            ASSERT_EQ(testNumCoin + 2, robot.getNumCoins());
        }
        else {
            ASSERT_TRUE(collision);
            ASSERT_FALSE(game.getisDoubleCoinOn());
            ASSERT_TRUE(coinsSize > game.getCoinsSize());
            ASSERT_EQ(testScore ++, game.getScore());
            ASSERT_EQ(testNumCoin ++, robot.getNumCoins());
        }
    }
}

TEST_F(GameTest, testCollisionPUCoin) {
    int testScore = game.getScore();
    std::unique_ptr<Coin> coin = factory.createCoin(CoinType::PowerUpCoin);
    coin->setPosition(sf::Vector2f(2 * game.getMap()->getMapSize().x, game.randomPosY()));
    coin->move(-game.getSpeed().x, 0);
    robot.setRobotPos(game.getMap()->getMapSize().x, -game.randomPosY());
    if (coin->getGlobalBounds().intersects(robot.getRobotBounds())) {
        int testRandom = game.randomPU();
        if(testRandom == 0)
            ASSERT_TRUE(game.getisDoubleCoinOn());
        else if(testRandom == 2) {
            ASSERT_TRUE(game.getisImmortalityOn());
            ASSERT_EQ(game.getSpeed().x, 9.f);
        }
        else if(testScore == 1)
            ASSERT_TRUE(game.getisShieldOn());
        ASSERT_EQ(testScore + 3, game.getScore());
    }
}
