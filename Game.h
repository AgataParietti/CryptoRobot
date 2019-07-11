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
    void updateGame();
    void renderGame();
    Map *getmap() { return &map; };

    void createObject();

private:
    Map map;
    Player robot;
    BlockCreator blockCreator;
    CoinCreator coinCreator;
    RocketCreator rocketCreator;

    float blockX;
    float coinX;
    float rocketY;

    sf::Texture robotTexture1;
    sf::Texture robotTexture2;

    std::vector<std::unique_ptr<Block>> blocks;
    std::vector<std::unique_ptr<Coin>> coins;
    std::vector<std::unique_ptr<Rocket>> rockets;
};

#endif //CRYPTOROBOT_GAME_H
