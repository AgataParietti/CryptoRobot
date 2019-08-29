//
// Created by Agata Parietti on 2019-07-11.
//

#ifndef CRYPTOROBOT_GAME_H
#define CRYPTOROBOT_GAME_H

#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Player.h"
#include "Factory.h"

class Game {
public:
    Game();
    ~Game();

    void update();
    void render();

    void createObj();
    void moveObject();
    void deleteObject();
    void moveRobot();
    void collision();
    void handleTxt();

    int randomPosY();
    int randomCreation();
    int randomPU();

    Map *getMap() { return &map;}


private:
     Map map;
     Player robot;
     Factory factory;

     int blockX;
     int maxY;
     int countCreation;
     int n;
     int score;

     float creationRate;

     bool isCreated;
     bool isCoinCreated;
     bool isShieldOn;
     bool isImmortalityOn;
     bool isDoubleCoinOn;

     sf::Sprite background;

     sf::Texture backgroundTexture;
     sf::Texture robotTexture1;
     sf::Texture robotTexture2;
     sf::Texture robotTextureS1;
     sf::Texture robotTextureS2;

    std::vector<std::unique_ptr<Block>> blocks;
    std::vector<std::unique_ptr<Coin>> coins;
    std::vector<std::unique_ptr<Rocket>> rockets;

    sf::Vector2f speed;
    sf::Vector2f oldSpeed;

    sf::Clock objectClk;
    sf::Clock controlPU;
    sf::Clock speedClk;
    sf::Clock doubleClk;
    sf::Clock scoreClk;

    sf::Text scoreTxt;
    sf::Text numScore;
    sf::Text coinTxt;
    sf::Text numCoins;
    sf::Text gameOverTxt;
    sf::Text doubleCoin;

    sf::Font font;

    double jump = 2.1f;
    double g = 0.9;
    float toll = 0.7;
    const float ground = 63.0f;
    const float top = 64.0f;
    const float speedLimit = 10.f;
    const unsigned int speedMul = 10;
    const float speedPlus = 0.1;

};
#endif //CRYPTOROBOT_GAME_H
