//
// Created by Agata Parietti on 2019-07-11.
//

#ifndef CRYPTOROBOT_GAME_H
#define CRYPTOROBOT_GAME_H

#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Player.h"
#include "Factory.h"
#include "PowerUp.h"

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

    int randomPosY();
    int randomCreation();
    int randomPU();

    Map *getMap() { return &map;}

    void setIsShieldOn(bool isShieldOn);
    void setSpeed(const sf::Vector2f &speed);
    void setOldSpeed(const sf::Vector2f &oldSpeed);

private:
     Map map;
     Player robot;
     Factory factory;
     //PowerUp powerUp;

     int blockX;
     int maxY;
     int countCreation;
     int n;

     float creationRate;

     bool isCreated;
     bool isCoinCreated;
     bool isShieldOn;
     bool powerUpOn;

     sf::Sprite background;

     sf::Texture backgroundTexture;
     sf::Texture robotTexture0;
     sf::Texture robotTexture1;
     sf::Texture robotTexture2;

    std::vector<std::unique_ptr<Block>> blocks;
    std::vector<std::unique_ptr<Coin>> coins;
    std::vector<std::unique_ptr<Rocket>> rockets;

    sf::Vector2f speed;
    sf::Vector2f oldSpeed;

    sf::Clock objectClk;
    sf::Clock controlPU;

    double jump = 1.8;
    double g = 0.7;
    int toll = 1;
    const float ground = 63.0f;
    const float top = 63.0f;


};
#endif //CRYPTOROBOT_GAME_H
