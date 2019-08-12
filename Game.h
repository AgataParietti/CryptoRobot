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

     Map *getMap() { return &map;}


private:
     Map map;
     Player robot;
     Factory factory;

     sf::Sprite background;

     sf::Texture backgroundTexture;
     sf::Texture robotTexture1;
     sf::Texture robotTexture2;

    std::vector<std::unique_ptr<Block>> blocks;
    std::vector<std::unique_ptr<Coin>> coins;
    std::vector<std::unique_ptr<Rocket>> rockets;

};
#endif //CRYPTOROBOT_GAME_H
