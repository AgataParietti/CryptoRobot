//
// Created by Agata Parietti on 2019-07-11.
//

#ifndef CRYPTOROBOT_GAME_H
#define CRYPTOROBOT_GAME_H

#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Player.h"
#include "BlockCreator.h"
#include "CoinCreator.h"
#include "RocketCreator.h"

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

    sf::Sprite background;
    sf::Texture backgroundTexture;

};
#endif //CRYPTOROBOT_GAME_H
