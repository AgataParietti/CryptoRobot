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

    int randomPosY();
    int randomCreation();

     Map *getMap() { return &map;}


private:
     Map map;
     Player robot;
     Factory factory;

     int blockX;
     int maxY;
     int countCreation;

     float creationRate;

     bool isCreated;
     bool isCoinCreated;

     sf::Sprite background;

     sf::Texture backgroundTexture;
     sf::Texture robotTexture0;
     sf::Texture robotTexture1;
     sf::Texture robotTexture2;

    std::vector<std::unique_ptr<Block>> blocks;
    std::vector<std::unique_ptr<Coin>> coins;
    std::vector<std::unique_ptr<Rocket>> rockets;

    sf::Vector2f speed;

    sf::Clock objectClk;

    double jump = 1.8;
    double g = 0.7;
    const float ground = 63.0f;
    const float top = 63.0f;


};
#endif //CRYPTOROBOT_GAME_H
