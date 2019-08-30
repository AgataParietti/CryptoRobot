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

    bool collision = false;

};

TEST_F(GameTest , testAssignment) {
    ASSERT_EQ(sf::Vector2f(0.7,0.8), game.getSpeed());
    ASSERT_TRUE(creationRate <= 1.2f);
    ASSERT_TRUE(game.randomCreation() >= 0 && game.randomCreation()<=2);
    ASSERT_TRUE(game.randomPosY() >= 0 && game.randomPosY() <= game.getMaxY());
    ASSERT_TRUE(game.randomPU() >= 0 && game.randomPU() <= 2);
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


TEST_F(GameTest, testCollisionNormalBlock) {
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
         else {
            ASSERT_FALSE(collision);
            ASSERT_TRUE(robot.getIsDead());
        }
    }
}

