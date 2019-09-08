//
// Created by Agata Parietti on 2019-07-11.
//

#ifndef CRYPTOROBOT_GAME_H
#define CRYPTOROBOT_GAME_H

#include <list>
#include <string>
#include <fstream>

#include "Subject.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Map.h"
#include "Player.h"
#include "Factory.h"

class Game: public Subject {
public:
    Game();
    ~Game();

    void update();
    void render();

    Map *getMap() { return &map;}

    //funzioni randomiche
    int randomPosY();
    int randomCreation();
    int randomPU();

    //funzioni getter
    const sf::Vector2f &getSpeed() const;
    int getMaxY() const;
    int getBlocksSize() { return static_cast<int>(blocks.size()); };
    int getCoinsSize() { return static_cast<int>(coins.size()); };
    int getRocketsSize() { return static_cast<int>(rockets.size()); };
    bool getisShieldOn() const;
    bool getisImmortalityOn() const;
    bool getisDoubleCoinOn() const;
    int getScore() const;
    int getLives() const;

    //funzioni observer
    void setScore(unsigned int score);
    void setLives(unsigned int lives);
    void notify() override;
    void unsubscribe(Observer *o) override;
    void subscribe(Observer *o) override;


private:

    //metodi privati
    void createObj();
    void moveObject();
    void deleteObject();
    void moveRobot();
    void collision();
    void handleTxt();

    //attributi privati
    std::ofstream file;
    std::ofstream bestScoreFileWrite;
    std::ifstream bestScoreFileRead;
    std::list<Observer*> observers;

    Map map;
    Player robot;
    Factory factory;

    int blockX;
    int maxY;
    int countCreation;
    int n;
    int txtCount;

    unsigned int score;
    unsigned int bestScore;

    float creationRate;
    float toll = 0.2;

    bool isCreated;
    bool isCoinCreated;
    bool isShieldOn;
    bool isImmortalityOn;
    bool isDoubleCoinOn;
    bool isCollided;

    sf::Sprite gameOver;
    sf::Sprite livesSprite;
    sf::Sprite layer1;
    sf::Sprite layer2;
    sf::Sprite layer3;
    sf::Sprite layer4;

    sf::Texture robotTexture1;
    sf::Texture robotTexture2;
    sf::Texture robotTextureS1;
    sf::Texture robotTextureS2;
    sf::Texture gameOverTexture;
    sf::Texture livesTexture;
    sf::Texture layer1Texture;
    sf::Texture layer2Texture;
    sf::Texture layer3Texture;
    sf::Texture layer4Texture;

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
    sf::Clock collisionClk;
    sf::Clock shieldClk;

    sf::Text scoreTxt;
    sf::Text numScore;
    sf::Text coinTxt;
    sf::Text numCoins;
    sf::Text doubleCoin;
    sf::Text coinB;
    sf::Text scoreB;
    sf::Text liveTxt;
    sf::Text bestScoreTxt;
    sf::Text bestScoreB;
    sf::Text bestScoreNum;

    sf::Font font1;
    sf::Font fontb;

    sf::Music gameMusic;

    sf::Sound gameOverSound;
    sf::Sound collisionSound;
    sf::Sound coinSound;
    sf::Sound powerUpSound;

    sf::SoundBuffer gameOverBuffer;
    sf::SoundBuffer collisionBuffer;
    sf::SoundBuffer coinBuffer;
    sf::SoundBuffer powerUpBuffer;

    double jump = 2.3f;
    double g = 1;

    const float ground = 63.0f;
    const float top = 68.0f;
    const float speedLimit = 9.f;
    const unsigned int speedMul =  5;
    const float creationLimit = 0.4;
    const float creationPlus = 0.05;
    const float speedPlus = 0.09;
    const float gPlus = 0.03;
    const float gLimit = 3.5;
    const float jumpLimit = 5.5;
    const float jumpPlus = 0.08;

};
#endif //CRYPTOROBOT_GAME_H
